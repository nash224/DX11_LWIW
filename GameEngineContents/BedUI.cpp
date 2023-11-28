#include "PreCompile.h"
#include "BedUI.h"

#include "Ellie.h"
#include "FadeObject.h"


static constexpr float HeadFont_Size = 17.0f;
static constexpr float SlotFont_Size = 14.0f;
static constexpr float SlotYPos = -28.0f;

static constexpr int Max_Slot_Count = 2;

BedUI::BedUI() 
{
	GameEngineInput::AddInputObject(this);
}

BedUI::~BedUI() 
{
}

void BedUI::Update(float _Delta)
{
	State.Update(_Delta);
}

void BedUI::Release()
{
	BaseRenderer = nullptr;
	HedFontRenderer = nullptr;
	CursorInfo.CursorRenderer = nullptr;
	SlotInfo.clear();
}

void BedUI::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void BedUI::Init()
{
	RendererSetting();
	StateSetting();

	Off();
}

void BedUI::RendererSetting()
{
	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Base);
	const float TooltipDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Frame);
	const float CursorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Cursor);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Font);

	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
	BaseRenderer->SetSprite("BedUI_Base.png");

	HedFontRenderer = CreateComponent<GameEngineUIRenderer>();
	HedFontRenderer->Transform.SetLocalPosition(float4(0.0f, 40.0f, CursorDepth));
	HedFontRenderer->SetText(GlobalValue::Font_Sandoll, "내일 9:00시 기상하게 됩니다.\n주무시겠습니까?", HeadFont_Size, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);

	CursorInfo.CursorRenderer = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.CursorRenderer->Transform.SetLocalPosition(float4(0.0f, 45.0f, FontDepth));
	CursorInfo.CursorRenderer->SetSprite("BedUI_TooltipCursor.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BedUI_TooltipSlot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert(std::string("BedUI_TooltipSlot.png") + "가 로드되어있지 않습니다.");
		return;
	}

	TooltipScale = Texture->GetScale();
	const float Tooltip_HalfSize = TooltipScale.hX();

	SlotInfo.resize(Max_Slot_Count);
	for (int i = 0; i < static_cast<int>(SlotInfo.size()); i++)
	{
		float XPos = Tooltip_HalfSize + Tooltip_Gap * 0.5f;
		const float YPos = SlotYPos;
		if (0 == i)
		{
			XPos *= -1.0f;
		}

		SlotInfo[i].TooltipRenderer = CreateComponent<GameEngineUIRenderer>();
		SlotInfo[i].TooltipRenderer->Transform.SetLocalPosition(float4(XPos, YPos, TooltipDepth));
		SlotInfo[i].TooltipRenderer->SetSprite("BedUI_TooltipSlot.png");

		std::string Answer;
		if (0 == i)
		{
			Answer = "예";
		}
		else
		{
			Answer = "아니오";
		}

		SlotInfo[i].FontRenderer = CreateComponent<GameEngineUIRenderer>();
		SlotInfo[i].FontRenderer->Transform.SetLocalPosition(float4(XPos, YPos + 6.0f, FontDepth));
		SlotInfo[i].FontRenderer->SetText(GlobalValue::Font_Sandoll, Answer, SlotFont_Size, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void BedUI::StateSetting()
{
	CreateStateParameter PopUpState;
	PopUpState.Start = std::bind(&BedUI::StartPopUp, this, std::placeholders::_1);
	PopUpState.Stay = std::bind(&BedUI::UpdatePopUp, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBEDUISTATE::PopUp, PopUpState);

	CreateStateParameter SelectState;
	SelectState.Stay = std::bind(&BedUI::UpdateSelect, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBEDUISTATE::Select, SelectState);

	CreateStateParameter DisappearState;
	DisappearState.Stay = std::bind(&BedUI::UpdateDisappear, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EBEDUISTATE::Disappear, DisappearState);

	CreateStateParameter GoDreamState;
	GoDreamState.Start = std::bind(&BedUI::StartGoDream, this, std::placeholders::_1);
	State.CreateState(EBEDUISTATE::GoDream, GoDreamState);
}

void BedUI::StartPopUp(GameEngineState* _Parent)
{
	SetScale(0.0f);
}

void BedUI::StartGoDream(GameEngineState* _Parent)
{
	std::shared_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeOut("DreamLevel", 1.4f);
}


void BedUI::UpdatePopUp(float _Delta, GameEngineState* _Parent) 
{
	const float StateTime = _Parent->GetStateTime();

	float Size = 0.0f;
	if (StateTime < TransitionTime)
	{
		Size = ScaleUpRatio * (StateTime / TransitionTime);
	}
	if (StateTime > TransitionTime)
	{
		const float DecreaseScale = ScaleUpRatio - PopUpScaleRatio;
		const float DecreaseTime = (TransitionTime - StateTime);
		Size = ScaleUpRatio - DecreaseScale * DecreaseTime / PopUpScaleRatio;
	}
	
	SetScale(Size);

	if (StateTime > PopUp_Time)
	{
		SetScale(PopUpScaleRatio);
		State.ChangeState(EBEDUISTATE::Select);
		return;
	}
}

void BedUI::UpdateSelect(float _Delta, GameEngineState* _Parent) 
{
	UpdateCursor();
}

void BedUI::UpdateDisappear(float _Delta, GameEngineState* _Parent) 
{
	const float StateTime = _Parent->GetStateTime();


	float Size = 0.0f;
	const float ScaleUpTime = PopUp_Time - TransitionTime;
	const float ScaleUpSize = ScaleUpRatio - PopUpScaleRatio;
	if (StateTime < ScaleUpTime)
	{
		Size = PopUpScaleRatio + ScaleUpSize * (StateTime / ScaleUpTime);
	}
	if (StateTime > ScaleUpTime)
	{
		const float SizeDownTime = StateTime - ScaleUpTime;
		const float SizeDownTimeRatio = SizeDownTime / TransitionTime;
		Size = ScaleUpRatio - ScaleUpRatio * SizeDownTimeRatio;
	}

	SetScale(Size);

	if (StateTime > PopUp_Time)
	{
		SetScale(0.0f);

		if (true == isGoDream)
		{
			State.ChangeState(EBEDUISTATE::GoDream);
			Close();
			return;
		}
		else
		{
			Close();
			return;
		}
	}
}


void BedUI::Open()
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OffControl();
	}

	Reset();
	State.ChangeState(EBEDUISTATE::PopUp);

	On();
}

void BedUI::Close()
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OnControl();
	}

	Off();
}

void BedUI::Reset()
{
	SetCursorLocalPosition(true);
	isLeftCursor = true;
}

void BedUI::SetScale(float _Size)
{
	SetFontScale(_Size);

	const float4& Scale = float4(_Size, _Size, 1.0f);
	Transform.SetLocalScale(Scale);
}

void BedUI::SetFontScale(float _Size)
{
	const float HeadFontScale = HeadFont_Size * _Size;
	HedFontRenderer->ChangeFontScale(HeadFontScale);

	for (const BedUISlot& Slot : SlotInfo)
	{
		const float SlotFontScale = SlotFont_Size * _Size;

		if (nullptr == Slot.FontRenderer)
		{
			MsgBoxAssert("폰트 렌더러가 존재하지 않습니다.");
			return;
		}
		
		Slot.FontRenderer->ChangeFontScale(SlotFontScale);
	}
}

void BedUI::UpdateCursor()
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		if (true == isLeftCursor)
		{
			isGoDream = true;
			State.ChangeState(EBEDUISTATE::Disappear);
			return;
		}
		else
		{
			isGoDream = false;
			State.ChangeState(EBEDUISTATE::Disappear);
			return;
		}
	}

	if (true == GameEngineInput::IsDown('X', this))
	{
		isGoDream = false;
		State.ChangeState(EBEDUISTATE::Disappear);
		return;
	}

	enum class EMOVECURSOR
	{
		Left = 0,
		Right = 1,
	};

	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		MoveCursor(static_cast<int>(EMOVECURSOR::Left));
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		MoveCursor(static_cast<int>(EMOVECURSOR::Right));
		return;
	}
}

void BedUI::MoveCursor(int _Value)
{
	bool isLeft = (0 == _Value);
	if (isLeft)
	{
		if (false == isLeftCursor)
		{
			SetCursorLocalPosition(true);
			isLeftCursor = true;
		}
		else
		{
			return;
		}
	}

	bool isRight = (1 == _Value);
	if (isRight)
	{
		if (true == isLeftCursor)
		{
			SetCursorLocalPosition(false);
			isLeftCursor = false;
		}
		else
		{
			return;
		}
	}
}

void BedUI::SetCursorLocalPosition(bool _isLeft)
{
	const float CursorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Cursor);
	const float XPos = TooltipScale.hX() + Tooltip_Gap * 0.5f;

	float4 TooltipPosition;
	if (_isLeft)
	{
		TooltipPosition = float4(-XPos, SlotYPos, CursorDepth);
	}
	else
	{
		TooltipPosition = float4(XPos, SlotYPos, CursorDepth);
	}

	if (nullptr == CursorInfo.CursorRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	CursorInfo.CursorRenderer->Transform.SetLocalPosition(TooltipPosition);
}