#include "PreCompile.h"
#include "UI_ProcessList.h"

#include "UIManager.h"
#include "UI_Inventory.h"

#include "UI_ProcessManager.h"
#include "UI_ProcessListUnit.h"

#include "IngredientData.h"


#define PROCESS_FIRST_SLOT_POSITION { -4.0f, 134.0f }

static constexpr int PROCESS_MAX_SLOT = 5;
static constexpr float PROCESS_SLOT_GAP = 64.0f;
static constexpr float Scroll_Start_Y_Pos = 136.0f;

UI_ProcessList::UI_ProcessList() 
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Sound\\UI\\Common");
	SFXFunction::LoadSoundFile(Dir.GetAllFile());
}

UI_ProcessList::~UI_ProcessList() 
{
}



void UI_ProcessList::Start() 
{
	GameEngineInput::AddInputObject(this);
}

void UI_ProcessList::Update(float _Delta) 
{
	UpdateInput();
}

void UI_ProcessList::Release() 
{
	BaseRenderer = nullptr;
	SlotVec.clear();

	CursorInfo.UpArrow = nullptr;
	CursorInfo.DownArrow = nullptr;
	CursorInfo.Cursor = nullptr;
	CursorInfo.ScrollBase = nullptr;
	CursorInfo.ScrollBar = nullptr;
	ProcessManagerPtr = nullptr;

	UIGuide.Release();
}

void UI_ProcessList::LevelEnd(class GameEngineLevel* _NextLevel) 
{
	Death();
}


void UI_ProcessList::Init()
{
	RendererSetting();

	CreateProcessSlot("WitchFlower_Water");
	CreateProcessSlot("Mongsiri_Water");
	CreateProcessSlot("FlowerBird_Water");
	CreateProcessSlot("MapleHerb_Water");
	CreateProcessSlot("SilverStarFlower_Water");
	CreateProcessSlot("BushBug_Water");


	std::vector<ButtonInfoParameter> Paras =
	{
		{ EBUTTONTYPE::X, "닫기"},
		{ EBUTTONTYPE::Z, "재료 선택"},
	};
	UIGuide.SetGuideInfo(this, Paras);
	UIGuide.Off();

	CursorSetting();
}

void UI_ProcessList::RendererSetting()
{
	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base)));
	BaseRenderer->SetSprite("Process_Base.png");

	Off();
}

// Request for Creating Process Slot 
void UI_ProcessList::CreateProcessSlot(std::string_view _ProcessName)
{
	if (nullptr == IngredientData::Find(_ProcessName))
	{
		MsgBoxAssert("가공하는 재료의 정보가 존재하지 않습니다.");
		return;
	}

	std::shared_ptr<UI_ProcessListUnit> Unit = GetLevel()->CreateActor<UI_ProcessListUnit>(EUPDATEORDER::UIComponent);
	Unit->Init(_ProcessName);
	SlotVec.push_back(Unit);
}

// Renderer Initial 
void UI_ProcessList::CursorSetting()
{
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float AttachmentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);

	CursorInfo.UpArrow = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.UpArrow->Transform.SetLocalPosition(float4(115.0f, 150.0f, FrameDepth));
	CursorInfo.UpArrow->SetSprite("Process_A_ScrollArrow.png");

	CursorInfo.DownArrow = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.DownArrow->Transform.SetLocalPosition(float4(115.0f, -150.0f, FrameDepth));
	CursorInfo.DownArrow->SetSprite("Process_B_ScrollArrow.png");

	CursorInfo.ScrollBase = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.ScrollBase->SetPivotType(PivotType::Top);
	CursorInfo.ScrollBase->Transform.SetLocalPosition(float4(115.0f, Scroll_Start_Y_Pos, FrameDepth));
	CursorInfo.ScrollBase->SetSprite("Process_A_ScrollBase.png");

	CursorInfo.ScrollBar = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.ScrollBar->SetPivotType(PivotType::Bottom);
	CursorInfo.ScrollBar->Transform.SetLocalPosition(float4(115.0f, Scroll_Start_Y_Pos, AttachmentDepth));
	CursorInfo.ScrollBar->SetSprite("Process_A_ScrollBar.png");
	

	CursorInfo.Cursor = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.Cursor->SetSprite("Process_A_Cursor.png");


	const std::shared_ptr<GameEngineTexture>& ScrollBTexture = CursorInfo.ScrollBar->GetSprite()->GetSpriteData(0).Texture;
	if (nullptr == ScrollBTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려했습니다.");
		return;
	}
	const float4 ScrollScale = ScrollBTexture->GetScale();
	CursorInfo.ScrollBarTotalYSize = ScrollScale.Y;

	const float SizeRatio = PROCESS_MAX_SLOT / static_cast<float>(SlotVec.size());
	CursorInfo.ScrollBarYSize = SizeRatio * CursorInfo.ScrollBarTotalYSize;

	CursorInfo.ScrollBar->GetImageTransform().SetLocalScale(float4(ScrollScale.X, CursorInfo.ScrollBarYSize));
}


// Open Process WIndow Panel
void UI_ProcessList::Open()
{
	On();
	UIGuide.On();

	for (std::shared_ptr<UI_ProcessListUnit>& UnitList : SlotVec)
	{
		int SrcCount = UI_Inventory::ReturnItemCount(UnitList->SrcName);
		UnitList->SrcCount = SrcCount;
		UnitList->RenewRenderer();
	}

	ResetCursor();
	RenewSlot();
}

void UI_ProcessList::Close()
{
	UIGuide.Off();
	CloseAllSlot();
	Off();
}


void UI_ProcessList::CloseAllSlot()
{
	for (const std::shared_ptr<UI_ProcessListUnit>& ListUnit : SlotVec)
	{
		ListUnit->Off();
	}
}



void UI_ProcessList::UpdateInput()
{
	if (GameEngineInput::IsDown('Z', this))
	{
		if (nullptr == ProcessManagerPtr)
		{
			MsgBoxAssert("매니저가 존재하지 않습니다.");
			return;
		}

		ProcessManagerPtr->OpenProcessWindow(SlotVec[CurrentCursor]->ItemName, SlotVec[CurrentCursor]->SrcCount);
		return;
	}

	if (GameEngineInput::IsDown('X', this))
	{
		if (nullptr == ProcessManagerPtr)
		{
			MsgBoxAssert("매니저가 존재하지 않습니다.");
			return;
		}
		ProcessManagerPtr->Close();
		return;
	}

	enum class EMOVECURSOR
	{
		Up = 0,
		Down = 1,
		None
	};

	if (GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(static_cast<int>(EMOVECURSOR::Up));
		RenewSlot();
		RenewCursor();
		return;
	}

	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(static_cast<int>(EMOVECURSOR::Down));
		RenewSlot();
		RenewCursor();
		return;
	}
}

void UI_ProcessList::MoveCursor(int _Value)
{
	SFXFunction::PlaySFX("SFX_InventoryMove_01.wav");

	int MoveLine = 0;
	if (1 == _Value)
	{
		MoveLine += 1;
	}

	if (0 == _Value)
	{
		MoveLine -= 1;
	}

	const bool isUp = (1 == _Value);
	if (isUp)
	{
		bool isNotMaxLine = (CurrentCursor + 1 < static_cast<int>(SlotVec.size()));
		if (isNotMaxLine)
		{
			++CurrentCursor;	
		}
		else
		{
			return;
		}
	}

	const bool isDown = (0 == _Value);
	if (isDown)
	{
		const bool isNotZero = (CurrentCursor != 0);
		if (isNotZero)
		{
			--CurrentCursor;
		}
		else
		{
			return;
		}
	}

	int MaxSlotCount = static_cast<int>(SlotVec.size());

	if (MaxSlotCount <= PROCESS_MAX_SLOT)
	{
		CurCursorLine = CurrentCursor;
	}
	else
	{
		CurCursorLine += MoveLine;
		if (CurrentCursor + 1 == MaxSlotCount)
		{
			CurCursorLine = PROCESS_MAX_SLOT - 1;
		}
		else if (0 == CurrentCursor)
		{
			CurCursorLine = 0;
		}
		else if (0 == CurCursorLine)
		{
			CurCursorLine = 1;
		}
		else if (PROCESS_MAX_SLOT - 1 == CurCursorLine)
		{
			CurCursorLine = PROCESS_MAX_SLOT - 2;
		}
	}

	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	const float CursorYPositon = -PROCESS_SLOT_GAP * static_cast<float>(CurCursorLine);
	CursorPosition += float4(0.0f, CursorYPositon);
	CursorPosition.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);

	CursorInfo.Cursor->Transform.SetLocalPosition(CursorPosition);
}


void UI_ProcessList::ResetCursor()
{
	CurrentCursor = 0;
	CurCursorLine = 0;

	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	CursorPosition.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);

	CursorInfo.Cursor->Transform.SetLocalPosition(CursorPosition);
}


void UI_ProcessList::RenewSlot()
{
	CloseAllSlot();

	const int SlotCount = static_cast<int>(SlotVec.size());

	bool isSlotbelow5 = (SlotCount <= PROCESS_MAX_SLOT);
	if (isSlotbelow5)
	{
		for (int i = 0; i < SlotCount; i++)
		{
			float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
			SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);
			SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
			SlotVec[i]->On();
		}
	}
	else
	{
		if (CurCursorLine == 0)
		{
			StartLine = 0;
			for (int i = 0; i < PROCESS_MAX_SLOT; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);
				SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[i]->On();
			} 
		}
		else if (1 <= CurCursorLine && CurCursorLine <= 3)
		{
			StartLine = CurrentCursor - CurCursorLine;
			for (int i = 0; i < PROCESS_MAX_SLOT; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);

				const int OutPutSlot = StartLine + i;
				SlotVec[OutPutSlot]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[OutPutSlot]->On();
			}
		}
		else
		{
			StartLine = SlotCount - PROCESS_MAX_SLOT;
			for (int i = 0; i < PROCESS_MAX_SLOT; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);

				const int OutPutSlotNumber = StartLine + i;
				SlotVec[OutPutSlotNumber]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[OutPutSlotNumber]->On();
			}
		}
	}
}

// 스크롤 바 이론
// 스크롤바가 움직이는 조건
// 렌더 슬롯 라인이 바뀔때
// 스크롤바 영역 : Total Scroll Scale
// 스크롤바 사이즈 : ScrollYScale = Total Scroll Scale * float(SlotSize / Max_Slot)
// 남은 스크롤바 사이즈 : RemainYSize = Total Size - ScrollYScale;
// 적용할 거리 : SetPosition = (RemainYSize / StartLine)

void UI_ProcessList::RenewCursor()
{
	const int SlotCnt = static_cast<int>(SlotVec.size());
	if (SlotCnt <= PROCESS_MAX_SLOT)
	{
		return;
	}

	const float RemainYSize = CursorInfo.ScrollBarTotalYSize - CursorInfo.ScrollBarYSize;
	float YPosition = 0.0f;
	if (StartLine != 0)
	{
		YPosition = -RemainYSize / static_cast<float>(StartLine);
	}
	SetScrollBarMovePosition(YPosition);
}

void UI_ProcessList::SetScrollBarMovePosition(float _YPos)
{
	if (nullptr == CursorInfo.ScrollBar)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}
	
	const float AttachmentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	CursorInfo.ScrollBar->Transform.SetLocalPosition(float4(115.0f, Scroll_Start_Y_Pos + _YPos, AttachmentDepth));
}