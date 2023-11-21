#include "PreCompile.h"
#include "UI_ProcessList.h"

#include "UIManager.h"
#include "UI_Inventory.h"

#include "UI_ProcessManager.h"
#include "UI_ProcessListUnit.h"

#include "IngredientData.h"

UI_ProcessList::UI_ProcessList() 
{
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
}

void UI_ProcessList::LevelEnd(class GameEngineLevel* _NextLevel) 
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void UI_ProcessList::Init()
{
	RendererSetting();

	CreateProcessSlot("WitchFlower_Water");
	CreateProcessSlot("Mongsiri_Water");
	CreateProcessSlot("FlowerBird_Water");
	CreateProcessSlot("MapleHerb_Water");
	CreateProcessSlot("SilverStarFlower_Water");
	CreateProcessSlot("BushBug_Water");

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
	CursorInfo.ScrollBase->Transform.SetLocalPosition(float4(115.0f, 0.0f, FrameDepth));
	CursorInfo.ScrollBase->SetSprite("Process_A_ScrollBase.png");

	CursorInfo.ScrollBar = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.ScrollBar->Transform.SetLocalPosition(float4(115.0f, 0.0f, AttachmentDepth));
	CursorInfo.ScrollBar->SetSprite("Process_A_ScrollBar.png");

	CursorInfo.Cursor = CreateComponent<GameEngineUIRenderer>();
	CursorInfo.Cursor->SetSprite("Process_A_Cursor.png");
}


/////////////////////////////////////////////////////////////////////////////////////

// Open Process WIndow Panel
void UI_ProcessList::Open()
{
	On();

	if (nullptr == UI_Inventory::MainInventory)
	{
		MsgBoxAssert("인벤토리가 존재하지 않는데 참조하려 했습니다.");
		return;
	}

	for (std::shared_ptr<UI_ProcessListUnit>& UnitList : SlotVec)
	{
		int SrcCount = UI_Inventory::MainInventory->ReturnItemCount(UnitList->SrcName);
		UnitList->SrcCount = SrcCount;
		UnitList->RenewRenderer();
	}

	ResetCursor();
	RenewSlot();
}

void UI_ProcessList::Close()
{
	CloseAllSlot();
	Off();
}


void UI_ProcessList::CloseAllSlot()
{
	for (const std::shared_ptr<UI_ProcessListUnit> ListUnit : SlotVec)
	{
		ListUnit->Off();
	}
}



/////////////////////////////////////////////////////////////////////////////////////

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
		return;
	}

	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(static_cast<int>(EMOVECURSOR::Down));
		RenewSlot();
		return;
	}
}

void UI_ProcessList::MoveCursor(int _Value)
{
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
	float CursorYPositon = -PROCESS_SLOT_GAP * static_cast<float>(CurCursorLine);
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

			const int StartLine = CurrentCursor - CurCursorLine;
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
			const int StartNumber = SlotCount - PROCESS_MAX_SLOT;
			for (int i = 0; i < PROCESS_MAX_SLOT; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);

				const int OutPutSlotNumber = StartNumber + i;
				SlotVec[OutPutSlotNumber]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[OutPutSlotNumber]->On();
			}
		}
	}
}
