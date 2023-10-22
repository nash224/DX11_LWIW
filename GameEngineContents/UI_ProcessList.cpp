#include "PreCompile.h"
#include "UI_ProcessList.h"

#include "UI_ProcessListUnit.h"
#include "UIManager.h"
#include "UI_Inventory.h"

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

	CreateProcessSlot("Mongsiri_Water");

	CursorSetting();
}

void UI_ProcessList::RendererSetting()
{
	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Process_Base.png");


	Off();
}


void UI_ProcessList::CreateProcessSlot(std::string_view _ProcessName)
{
	if (nullptr == IngredientData::Find(_ProcessName))
	{
		MsgBoxAssert("가공하는 재료의 정보가 존재하지 않습니다.");
		return;
	}

	std::shared_ptr<UI_ProcessListUnit> Unit = GetLevel()->CreateActor<UI_ProcessListUnit>(EUPDATEORDER::UIComponent);
	Unit->Init(_ProcessName, 2);
	SlotVec.push_back(Unit);
}

void UI_ProcessList::CursorSetting()
{
	m_ProcessListCursor.UpArrow = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.UpArrow->Transform.SetLocalPosition(float4(115.0f, 150.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.UpArrow->SetSprite("Process_A_ScrollArrow.png");

	m_ProcessListCursor.DownArrow = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.DownArrow->Transform.SetLocalPosition(float4(115.0f, -150.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.DownArrow->SetSprite("Process_B_ScrollArrow.png");

	m_ProcessListCursor.ScrollBase = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.ScrollBase->Transform.SetLocalPosition(float4(115.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_ProcessListCursor.ScrollBase->SetSprite("Process_A_ScrollBase.png");

	m_ProcessListCursor.ScrollBar = CreateComponent<GameEngineUIRenderer>();
	m_ProcessListCursor.ScrollBar->Transform.SetLocalPosition(float4(115.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	m_ProcessListCursor.ScrollBar->SetSprite("Process_A_ScrollBar.png");

	m_ProcessListCursor.Cursor = CreateComponent<GameEngineUIRenderer>();
	float4 CursorPosition = PROCESS_FIRST_SLOT_POSITION;
	CursorPosition.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor);
	m_ProcessListCursor.Cursor->Transform.SetLocalPosition(float4(CursorPosition));
	m_ProcessListCursor.Cursor->SetSprite("Process_A_Cursor.png");
}


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
		int ItemCount = UI_Inventory::MainInventory->ReturnItemCount(SlotVec[i]->ItemName);
		
	}
	// 리스트 카운트
	// 리스트 커서
}

void UI_ProcessList::Close()
{
	Off();
}



void UI_ProcessList::UpdateInput()
{
	if (GameEngineInput::IsDown('Z', this))
	{
		// Select
		return;
	}

	if (GameEngineInput::IsDown('X', this))
	{
		Close();
		return;
	}

	if (GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(0);
		return;
	}

	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(1);
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

	}
	else if (SlotCount >= 2 && 1 == CurrentCursor)
	{
		NewYPositon = -PROCESS_SLOT_GAP;
	}
	else if (SlotCount >= 3 && 2 == CurrentCursor)
	{
		NewYPositon = -PROCESS_SLOT_GAP * 2.0f;
	}
	else if (SlotCount >= 4 && 3 == CurrentCursor)
	{
		NewYPositon = -PROCESS_SLOT_GAP * 3.0f;
	}
	else if (CurrentCursor == SlotCount - 2)
	{
		NewYPositon = -PROCESS_SLOT_GAP * 4.0f;
	}
	else if (CurrentCursor == SlotCount - 1)
	{
		NewYPositon = -PROCESS_SLOT_GAP * 3.0f;
	}
	else
	{
		NewYPositon = -PROCESS_SLOT_GAP * 2.0f;
	}

	CursorPosition += float4(0.0f, NewYPositon);
	CursorPosition.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor);

	m_ProcessListCursor.Cursor->Transform.SetLocalPosition(CursorPosition);
}
