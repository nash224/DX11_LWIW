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
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float StaminaDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge2);
	const float RecoverableGaugeDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1);
	const float IndicatorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator);

	const float4& FramePosition = float4(0.0f, 0.0f, FrameDepth);
	const float4& StaminaPosition = float4(0.0f, 0.0f, StaminaDepth);
	const float4& RecoverableGaugePosition = float4(0.0f, 0.0f, RecoverableGaugeDepth);
	const float4& IndicatorPosition = float4(0.0f, 0.0f, IndicatorDepth);


	UIStamina.FrameRenderer  = CreateComponent<GameEngineUIRenderer>();
	UIStamina.FrameRenderer ->Transform.SetLocalPosition(FramePosition);
	UIStamina.FrameRenderer ->SetSprite("HUD_Gauge_Frame.png");


	UIStamina.StaminaGaugeRenderer = CreateComponent<ContentsUIRenderer>();
	UIStamina.StaminaGaugeRenderer->Transform.SetLocalPosition(StaminaPosition);
	UIStamina.StaminaGaugeRenderer->SetMaterial("GaugeTexture2D");
	UIStamina.StaminaGaugeRenderer->GetGaugeInfo().LineGauge = 1;
	UIStamina.StaminaGaugeRenderer->SetSprite("HUD_Gauge_1.png");


	UIStamina.RecoverableGaugeRenderer = CreateComponent<GameEngineUIRenderer>();
	UIStamina.RecoverableGaugeRenderer->Transform.SetLocalPosition(RecoverableGaugePosition);
	UIStamina.RecoverableGaugeRenderer->SetSprite("HUD_Gauge_2.png");

	UIStamina.IndicatorRenderer = CreateComponent<GameEngineUIRenderer>();
	UIStamina.IndicatorRenderer->Transform.SetLocalPosition(IndicatorPosition);
	UIStamina.IndicatorRenderer->SetSprite("HUD_Gauge_Indicator.png");
}


void UI_Hub_Stamina::UpdateGauge()
{
	if (nullptr != Ellie::MainEllie)
	{
		if (Ellie::MainEllie->GetStamina() != RenderStamina)
		{
			RenderStamina = Ellie::MainEllie->GetStamina();

 			float StaminaGauge = RenderStamina / MAX_STAMINA;
			UIStamina.StaminaGaugeRenderer->GetGaugeInfo().Gauge = StaminaGauge;
		}
	}
}