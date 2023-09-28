#include "PreCompile.h"
#include "UI_Ellie_Tool.h"


ETOOLTYPE UI_Ellie_Tool::m_CurrentTool = ETOOLTYPE::Max;
UI_Ellie_Tool::UI_Ellie_Tool() 
{
}

UI_Ellie_Tool::~UI_Ellie_Tool() 
{
}


void UI_Ellie_Tool::Start()
{

}

void UI_Ellie_Tool::Update(float _Delta)
{

}

void UI_Ellie_Tool::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Ellie_Tool::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Ellie_Tool::Init()
{
	m_CurrentTool = ETOOLTYPE::Gloves;

	m_Tool = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Icon);
	m_Tool->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	m_LeftArrow = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Icon);
	m_LeftArrow->SetSprite("Tool_Icon.png", static_cast<int>(m_CurrentTool));

	Transform.AddLocalPosition({ -418.0f , -196.0f });
}