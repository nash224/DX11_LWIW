#include "PreCompile.h"
#include "UI_Hub_Stamina.h"


int UI_Hub_Stamina::CurrentStamina = -1;
int UI_Hub_Stamina::RecoverableStamina = -1;
UI_Hub_Stamina::UI_Hub_Stamina() 
{
}

UI_Hub_Stamina::~UI_Hub_Stamina() 
{
}


void UI_Hub_Stamina::Start()
{

}

void UI_Hub_Stamina::Update(float _Delta)
{

}

void UI_Hub_Stamina::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_Hub_Stamina::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_Stamina::Init()
{
	m_GaugeComposition.Frame = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::HUB_Frame);
	m_GaugeComposition.Frame->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::HUB_Frame)});
	m_GaugeComposition.Frame->SetSprite("HUD_Gauge_Frame.png");


	m_GaugeComposition.StaminaGauge = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::HUB_Gauge2);
	m_GaugeComposition.StaminaGauge->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::HUB_Gauge2) });
	m_GaugeComposition.StaminaGauge->SetSprite("HUD_Gauge_1.png");


	m_GaugeComposition.RecoverableGauge = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::HUB_Gauge1);
	m_GaugeComposition.RecoverableGauge->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1) });
	m_GaugeComposition.RecoverableGauge->SetSprite("HUD_Gauge_2.png");

	m_GaugeComposition.Indicator = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI_AlphaBlend);
	m_GaugeComposition.Indicator->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::HUB_Indicator) });
	m_GaugeComposition.Indicator->SetSprite("HUD_Gauge_Indicator.png");

	Transform.AddLocalPosition({ -369.0f , -232.0f });


	if (CurrentStamina < 0)
	{
		CurrentStamina = MaxStamina;
		RecoverableStamina = MaxStamina;
	}

	Off();
}

void UI_Hub_Stamina::AddGauge(int _Value)
{
	CurrentStamina = _Value;
}
