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
	m_Base = nullptr;
	SlotVec.clear();

	m_ProcessListCursor.UpArrow = nullptr;
	m_ProcessListCursor.DownArrow = nullptr;
	m_ProcessListCursor.Cursor = nullptr;
	m_ProcessListCursor.ScrollBase = nullptr;
	m_ProcessListCursor.ScrollBar = nullptr;
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

	CursorSetting();
}

void UI_ProcessList::RendererSetting()
{
	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Process_Base.png");


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
	m_ProcessListCursor.UpArrow = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.UpArrow->Transform.SetLocalPosition(float4(115.0f, 150.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.UpArrow->SetSprite("Process_A_ScrollArrow.png");

	m_ProcessListCursor.DownArrow = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.DownArrow->Transform.SetLocalPosition(float4(115.0f, -150.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.DownArrow->SetSprite("Process_B_ScrollArrow.png");

	m_ProcessListCursor.ScrollBase = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.ScrollBase->Transform.SetLocalPosition(float4(115.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.ScrollBase->SetSprite("Process_A_ScrollBase.png");

	m_ProcessListCursor.ScrollBar = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.ScrollBar->Transform.SetLocalPosition(float4(115.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment)));
	m_ProcessListCursor.ScrollBar->SetSprite("Process_A_ScrollBar.png");

	m_ProcessListCursor.Cursor = CreateComponent<GameEngineUIRenderer>();
	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	CursorPosition.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
	m_ProcessListCursor.Cursor->Transform.SetLocalPosition(float4(CursorPosition));
	m_ProcessListCursor.Cursor->SetSprite("Process_A_Cursor.png");
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

	for (size_t i = 0; i < SlotVec.size(); i++)
	{
		int SrcCount = UI_Inventory::MainInventory->ReturnItemCount(SlotVec[i]->SrcName);
		SlotVec[i]->SrcCount = SrcCount;
		SlotVec[i]->RenewRenderer();
	}

	// 리스트 커서
	ResetCursor();
	// 리스트 카운트
	RenewSlot();
}

void UI_ProcessList::Close()
{
	CloseAllSlot();

	Off();
}

// Close All Slot
void UI_ProcessList::CloseAllSlot()
{
	for (size_t i = 0; i < SlotVec.size(); i++)
	{
		SlotVec[i]->Off();
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

	if (GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(0);
		RenewSlot();
		return;
	}

	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(1);
		RenewSlot();
		return;
	}
}

// 0 : 위
// 1 : 아래
void UI_ProcessList::MoveCursor(int _Value)
{
	if (1 == _Value)
	{
		if (CurrentCursor + 1 != SlotVec.size())
		{
			++CurrentCursor;	
		}
	}
	else
	{
		if (CurrentCursor != 0)
		{
			--CurrentCursor;
		}
	}

	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	float NewYPositon = 0.0f;

	int SlotCount = static_cast<int>(SlotVec.size());

	if (SlotCount >= 1 && 0 == CurrentCursor)
	{
		CurCursorLine = 0;
	}
	else if (SlotCount >= 2 && 1 == CurrentCursor)
	{
		CurCursorLine = 1;
		NewYPositon = -PROCESS_SLOT_GAP;
	}
	else if (SlotCount >= 3 && 2 == CurrentCursor)
	{
		CurCursorLine = 2;
		NewYPositon = -PROCESS_SLOT_GAP * 2.0f;
	}
	else if (SlotCount >= 4 && 3 == CurrentCursor)
	{
		CurCursorLine = 3;
		NewYPositon = -PROCESS_SLOT_GAP * 3.0f;
	}
	else if (CurrentCursor == SlotCount - 2)
	{
		CurCursorLine = 3;
		NewYPositon = -PROCESS_SLOT_GAP * 3.0f;
	}
	else if (CurrentCursor == SlotCount - 1)
	{
		CurCursorLine = 4;
		NewYPositon = -PROCESS_SLOT_GAP * 4.0f;
	}
	else
	{
		CurCursorLine = 2;
		NewYPositon = -PROCESS_SLOT_GAP * 2.0f;
	}

	CursorPosition += float4(0.0f, NewYPositon);
	CursorPosition.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);

	m_ProcessListCursor.Cursor->Transform.SetLocalPosition(CursorPosition);
}


void UI_ProcessList::ResetCursor()
{
	CurrentCursor = 0;
	CurCursorLine = 0;

	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	CursorPosition.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);

	m_ProcessListCursor.Cursor->Transform.SetLocalPosition(CursorPosition);
}



// 슬롯을 갱신한다.
void UI_ProcessList::RenewSlot()
{
	// 모든 슬롯을 끄고
	CloseAllSlot();

	PROCESS_SLOT_GAP;

	int SlotCount = static_cast<int>(SlotVec.size());

	// 슬롯이 5개보다 작을경우 순차적으로 켠다.
	if (SlotCount <= PROCESS_MAX_SLOT)
	{
		for (size_t i = 0; i < SlotCount; i++)
		{
			float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
			SlotPosition.Y += -PROCESS_SLOT_GAP * static_cast<float>(i);
			SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
			SlotVec[i]->On();
		}
	}
	// 슬롯이 5개보다 많고
	else
	{
		// 슬롯의 라인이 2라인이면 0~4번까지 
		if (CurCursorLine <= 2)
		{
			for (size_t i = 0; i < PROCESS_MAX_SLOT; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y = PROCESS_SLOT_GAP * static_cast<float>(i);
				SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[i]->On();
			}
		}
		// 슬롯의 라인이 4라인이라면 (마지막-5) ~ 마지막까지
		else if (CurCursorLine >= 4)
		{
			int Line = 0;
			for (size_t i = SlotCount - PROCESS_MAX_SLOT; i < SlotCount; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y = PROCESS_SLOT_GAP * static_cast<float>(Line);
				SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[i]->On();
				++Line;
			}
		}
		// 중앙이라면 편차 2만큼 켠다
		else
		{
			int Line = 0;
			for (int i = CurrentCursor - CurCursorLine; i < CurrentCursor + CurCursorLine + 1; i++)
			{
				float4 SlotPosition = PROCESS_FIRST_SLOT_POSITION;
				SlotPosition.Y = PROCESS_SLOT_GAP * static_cast<float>(Line);
				SlotVec[i]->Transform.SetLocalPosition(SlotPosition);
				SlotVec[i]->On();
				++Line;
			}
		}
	}
}
