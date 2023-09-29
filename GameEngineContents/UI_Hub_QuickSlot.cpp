#include "PreCompile.h"
#include "UI_Hub_QuickSlot.h"


int UI_Hub_QuickSlot::ItemSelection = -1;
std::list<std::string> UI_Hub_QuickSlot::QuickSlotItemList;
UI_Hub_QuickSlot::UI_Hub_QuickSlot() 
{
}

UI_Hub_QuickSlot::~UI_Hub_QuickSlot() 
{
}


void UI_Hub_QuickSlot::Start()
{

}

void UI_Hub_QuickSlot::Update(float _Delta)
{

}

void UI_Hub_QuickSlot::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Hub_QuickSlot::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_QuickSlot::Init()
{
	m_Slot = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Frame);
	m_Slot->SetSprite("HUD_Potion_Slot.png");

	m_ArrowLeft = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::UIArrow);
	m_ArrowLeft->SetSprite("HUD_Arrow_Left.png");
	m_ArrowLeft->Transform.AddLocalPosition({ -CONST_ArrowDistanceToLocalZERO , 0.0f });

	m_ArrowRight = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::UIArrow);
	m_ArrowRight->SetSprite("HUD_Arrow_Left.png");
	m_ArrowRight->LeftFlip();
	m_ArrowRight->Transform.AddLocalPosition({ CONST_ArrowDistanceToLocalZERO , 0.0f });

	m_Item = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Icon);
	m_Item->Off();

	Off();

	Transform.AddLocalPosition({ 410.0f , -209.0f });
}

void UI_Hub_QuickSlot::RegisterForQuickSlot(std::string_view _ItemName)
{

}