#include "PreCompile.h"
#include "BedUI.h"

#include "Ellie.h"

BedUI::BedUI() 
{
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

void BedUI::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BedUI::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BedUI::Init()
{
	RendererSetting();
	StateSetting();
}

void BedUI::RendererSetting()
{
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Base);
	const float TooltipDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Frame);
	const float CursorDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Cursor);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Window_Font);

	const float4& BasePosition = float4(0.0f, 0.0f, BaseDepth);
	const float4& CursorPosition = float4(0.0f, 0.0f, CursorDepth);
	const float4& HeadFontPosition = float4(0.0f, 45.0f, FontDepth);


	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(BasePosition);
	BaseRenderer->SetSprite("BedUI_Base.png");

	HedFontRenderer = CreateComponent<GameEngineUIRenderer>();
	HedFontRenderer->Transform.SetLocalPosition(HeadFontPosition);
	HedFontRenderer->SetText(GlobalValue::Font_Sandoll, "내일 9:00시 기상하게 됩니다.\n주무시겠습니까?", 17.0f, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);

	CursorInfo.CursorRenderer = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.CursorRenderer->Transform.SetLocalPosition(CursorPosition);
	CursorInfo.CursorRenderer->SetSprite("BedUI_TooltipCursor.png");

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("BedUI_TooltipSlot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert(std::string("BedUI_TooltipSlot.png") + "가 로드되어있지 않습니다.");
		return;
	}

	TooltipScale = Texture->GetScale();
	const float Tooltip_HalfSize = TooltipScale.hX();

	SlotInfo.resize(2);
	for (int i = 0; i < static_cast<int>(SlotInfo.size()); i++)
	{
		float XPos = Tooltip_HalfSize + Tooltip_Gap * 0.5f;
		const float YPos = -28.0f;
		if (0 == i)
		{
			XPos *= -1.0f;
		}

		const float4& TooltipPosition = float4(XPos, YPos, TooltipDepth);

		SlotInfo[i].TooltipRenderer = CreateComponent<GameEngineUIRenderer>();
		SlotInfo[i].TooltipRenderer->Transform.SetLocalPosition(TooltipPosition);
		SlotInfo[i].TooltipRenderer->SetSprite("BedUI_TooltipSlot.png");


		const float4& SlotFontPosition = float4(XPos, YPos + 6.0f, FontDepth);

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
		SlotInfo[i].FontRenderer->Transform.SetLocalPosition(SlotFontPosition);
		SlotInfo[i].FontRenderer->SetText(GlobalValue::Font_Sandoll, Answer, 14.0f, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	}
}

void BedUI::StateSetting()
{
	CreateStateParameter OffState;
	State.CreateState(EBEDUISTATE::Off, OffState);


	//	Off
	//	PopUp
	//	Select
	//	Disappear
}

void BedUI::Open()
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OffControl();
	}

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