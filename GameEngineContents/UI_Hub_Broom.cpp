#include "PreCompile.h"
#include "UI_Hub_Broom.h"


float UI_Hub_Broom::BroomFuelTank = 0.0f;
UI_Hub_Broom::UI_Hub_Broom() 
{
}

UI_Hub_Broom::~UI_Hub_Broom() 
{
}


void UI_Hub_Broom::Start()
{

}

void UI_Hub_Broom::Update(float _Delta)
{

}

void UI_Hub_Broom::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Hub_Broom::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Broom::Init()
{
	m_Frame = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Frame);
	m_Frame->SetSprite("HUD_Broom_Gauge_Frame.png");

	m_Gauge = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Gauge1);
	m_Gauge->SetSprite("HUD_Broom_Gauge_1.png");
	m_Gauge->SetPivotType(PivotType::Left);
	m_Gauge->Transform.AddLocalPosition({ -26.0f , 0.0f });
	
	m_Icon = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::HUB_Frame);
	m_Icon->SetSprite("Tool_BroomA.png");
	m_Icon->LeftFlip();
	m_Icon->Transform.AddLocalPosition({ 0.0f , 32.0f });

	Transform.AddLocalPosition({ -419.0f , -156.0f });

	Off();
}

void UI_Hub_Broom::AddBroomGauge(const float _Value)
{
	BroomFuelTank = _Value;
}