#include "PreCompile.h"
#include "UI_Hub_Stamina.h"

#include "Ellie.h"


UI_Hub_Stamina::UI_Hub_Stamina() 
{
}

UI_Hub_Stamina::~UI_Hub_Stamina() 
{
}


void UI_Hub_Stamina::Start()
{
	Transform.AddLocalPosition({ -369.0f , -232.0f });
	RendererSetting();
	RenewRender();
	Off();
}

void UI_Hub_Stamina::Update(float _Delta)
{
	RenewRender();
}

void UI_Hub_Stamina::RendererSetting()
{
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float StaminaDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge2);
	const float RecoverableGaugeDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1);
	const float IndicatorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Indicator);


	UIStamina.Frame  = CreateComponent<GameEngineUIRenderer>();
	UIStamina.Frame ->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	UIStamina.Frame ->SetSprite("HUD_Gauge_Frame.png");


	UIStamina.StaminaGauge = CreateComponent<ContentsUIRenderer>();
	UIStamina.StaminaGauge->Transform.SetLocalPosition(float4(0.0f, 0.0f, StaminaDepth));
	UIStamina.StaminaGauge->SetMaterial("GaugeTexture2D");
	UIStamina.StaminaGauge->GetGaugeInfo().LineGauge = 1;
	UIStamina.StaminaGauge->SetSprite("HUD_Gauge_1.png");

	UIStamina.RecoverableGauge = CreateComponent<GameEngineUIRenderer>();
	UIStamina.RecoverableGauge->Transform.SetLocalPosition(float4(0.0f, 0.0f, RecoverableGaugeDepth));
	UIStamina.RecoverableGauge->SetSprite("HUD_Gauge_2.png");

	UIStamina.Indicator = CreateComponent<GameEngineUIRenderer>();
	UIStamina.Indicator->Transform.SetLocalPosition(float4(0.0f, 0.0f, IndicatorDepth));
	UIStamina.Indicator->SetSprite("HUD_Gauge_Indicator.png");
}


void UI_Hub_Stamina::RenewRender()
{
	const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetCurLevel()->GetPlayerPtr();
	if (nullptr != PlayerPtr)
	{
		if (PlayerPtr->GetStamina() != RenderStamina)
		{
			RenderStamina = PlayerPtr->GetStamina();

 			float StaminaRatio = RenderStamina / MAX_STAMINA;
			UIStamina.StaminaGauge->GetGaugeInfo().Gauge = StaminaRatio;
		}
	}
}