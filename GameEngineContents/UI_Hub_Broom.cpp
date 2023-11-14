#include "PreCompile.h"
#include "UI_Hub_Broom.h"

#include "Ellie.h"

float UI_Hub_Broom::RenderingAccFuel = 0.0f;
UI_Hub_Broom::UI_Hub_Broom() 
{
}

UI_Hub_Broom::~UI_Hub_Broom() 
{
}


void UI_Hub_Broom::Update(float _Delta)
{
	UpdateGauge();
}

void UI_Hub_Broom::Release()
{
	FrameRenderer = nullptr;
	GaugeRenderer = nullptr;
	IconRenderer = nullptr;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_Broom::Init()
{
	Transform.AddLocalPosition(float4(-419.0f, -156.0f ));

	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float GaugeDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1);
	const float IconDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);

	const float4& FramePosition = float4(0.0f, 0.0f, FrameDepth);
	const float4& GaugePosition = float4(-1.0f, 0.0f, GaugeDepth);
	const float4& IconPosition = float4(0.0f, 32.0f, IconDepth);

	FrameRenderer = CreateComponent<GameEngineUIRenderer>();
	FrameRenderer->Transform.SetLocalPosition(FramePosition);
	FrameRenderer->SetSprite("HUD_Broom_Gauge_Frame.png");

	GaugeRenderer = CreateComponent<ContentsUIRenderer>();
	GaugeRenderer->Transform.AddLocalPosition(GaugePosition);
	GaugeRenderer->SetMaterial("LineGaugeTexture2D");
	GaugeRenderer->SetSprite("HUD_Broom_Gauge_1.png");
	
	IconRenderer = CreateComponent<GameEngineUIRenderer>();
	IconRenderer->Transform.AddLocalPosition(IconPosition);
	IconRenderer->SetSprite("Tool_BroomA.png");
	IconRenderer->LeftFlip();

	UpdateGauge();

	Off();
}

void UI_Hub_Broom::UpdateGauge()
{
	if (nullptr != Ellie::MainEllie)
	{
		if (Ellie::MainEllie->GetBroomFuel() != RenderingAccFuel)
		{
			RenderingAccFuel = Ellie::MainEllie->GetBroomFuel();

			float FuelGauge = RenderingAccFuel / MAX_FUEL;
			GaugeRenderer->GetGaugeInfo().Gauge = FuelGauge;
		}
	}
}
