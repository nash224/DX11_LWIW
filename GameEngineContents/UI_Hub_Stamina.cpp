#include "PreCompile.h"
#include "UI_Hub_Stamina.h"

#include "Ellie.h"


float UI_Hub_Stamina::RenderStamina = -1;
float UI_Hub_Stamina::RecoverableStamina = -1;
UI_Hub_Stamina::UI_Hub_Stamina() 
{
	if (nullptr != Ellie::MainEllie)
	{
		RenderStamina = Ellie::MainEllie->GetStamina();
	}
}

UI_Hub_Stamina::~UI_Hub_Stamina() 
{
}


void UI_Hub_Stamina::Update(float _Delta)
{
	UpdateGauge();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Hub_Stamina::Init()
{
	Transform.AddLocalPosition({ -369.0f , -232.0f });

	RendererSetting();

	Off();
}

void UI_Hub_Stamina::RendererSetting()
{
	m_GaugeComposition.Frame = CreateComponent<GameEngineUIRenderer>();
	m_GaugeComposition.Frame->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame) });
	m_GaugeComposition.Frame->SetSprite("HUD_Gauge_Frame.png");


	m_GaugeComposition.StaminaGauge = CreateComponent<ContentsUIRenderer>();
	m_GaugeComposition.StaminaGauge->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge2) });
	m_GaugeComposition.StaminaGauge->SetMaterial("LineGaugeTexture2D");
	m_GaugeComposition.StaminaGauge->SetSprite("HUD_Gauge_1.png");


	m_GaugeComposition.RecoverableGauge = CreateComponent<GameEngineUIRenderer>();
	m_GaugeComposition.RecoverableGauge->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1) });
	m_GaugeComposition.RecoverableGauge->SetSprite("HUD_Gauge_2.png");

	m_GaugeComposition.Indicator = CreateComponent<GameEngineUIRenderer>();
	m_GaugeComposition.Indicator->Transform.SetLocalPosition({ 0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator) });
	m_GaugeComposition.Indicator->SetSprite("HUD_Gauge_Indicator.png");
}


void UI_Hub_Stamina::UpdateGauge()
{
	if (nullptr != Ellie::MainEllie)
	{
		if (Ellie::MainEllie->GetStamina() != RenderStamina)
		{
			RenderStamina = Ellie::MainEllie->GetStamina();

 			float StaminaGauge = RenderStamina / MAX_STAMINA;
			m_GaugeComposition.StaminaGauge->GetGaugeInfo().Gauge = StaminaGauge;
		}
	}
}