#include "PreCompile.h"
#include "UI_Hub_Broom.h"

#include "Ellie.h"

#include "ContentsEvent.h"


UI_Hub_Broom::UI_Hub_Broom() 
{
}

UI_Hub_Broom::~UI_Hub_Broom() 
{
}


void UI_Hub_Broom::Update(float _Delta)
{
	State.Update(_Delta);
}

void UI_Hub_Broom::Release()
{
	FrameRenderer = nullptr;
	GaugeUI = nullptr;
	IconRenderer = nullptr;
}

void UI_Hub_Broom::Init()
{
	Transform.AddLocalPosition(float4(-419.0f, -156.0f ));

	RendererSetting();
	StateSetting();

	Off();
}

void UI_Hub_Broom::RendererSetting()
{
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);
	const float GaugeDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Gauge1);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::HUB_Frame);

	FrameRenderer = CreateComponent<GameEngineUIRenderer>();
	FrameRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	FrameRenderer->SetSprite("HUD_Broom_Gauge_Frame.png");

	GaugeUI = CreateComponent<GaugeUIRenderer>();
	GaugeUI->Transform.AddLocalPosition(float4(-1.0f, 0.0f, GaugeDepth));
	GaugeUI->SetMaterial("GaugeTexture2D");
	GaugeUI->GetGaugeInfo().LineGauge = 1;
	GaugeUI->SetSprite("HUD_Broom_Gauge_1.png");

	IconRenderer = CreateComponent<GameEngineUIRenderer>();
	IconRenderer->Transform.AddLocalPosition(float4(0.0f, 32.0f, IconDepth));
	IconRenderer->SetSprite("Tool_BroomA.png");
	IconRenderer->LeftFlip();
}

void UI_Hub_Broom::StateSetting()
{
	CreateStateParameter HasNotBroomState;
	HasNotBroomState.Start = std::bind(&UI_Hub_Broom::StartHasNotBroom, this, std::placeholders::_1);
	HasNotBroomState.Stay = std::bind(&UI_Hub_Broom::UpdateHasNotBroom, this, std::placeholders::_1, std::placeholders::_2);
	HasNotBroomState.End = std::bind(&UI_Hub_Broom::EndHasNotBroom, this, std::placeholders::_1);
	State.CreateState(EUIBROOMSTATE::HasNotBroom, HasNotBroomState);

	CreateStateParameter GaugeState;
	GaugeState.Stay = std::bind(&UI_Hub_Broom::UpdateGauge, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EUIBROOMSTATE::UpdateFuel, GaugeState);

	if (true == ContentsEvent::HasWitchBroom)
	{
		State.ChangeState(EUIBROOMSTATE::UpdateFuel);
	}
	else
	{
		State.ChangeState(EUIBROOMSTATE::HasNotBroom);
	}
}


void UI_Hub_Broom::StartHasNotBroom(GameEngineState* _Parent)
{
	if (nullptr == FrameRenderer || nullptr == GaugeUI || nullptr == IconRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	FrameRenderer->Off();
	GaugeUI->Off();
	IconRenderer->Off();
}


void UI_Hub_Broom::UpdateHasNotBroom(float _Delta, GameEngineState* _Parent)
{
	if (true == ContentsEvent::HasWitchBroom)
	{
		State.ChangeState(EUIBROOMSTATE::UpdateFuel);
		return;
	}
}

void UI_Hub_Broom::UpdateGauge(float _Delta, GameEngineState* _Parent)
{
	const float CurFuel = PlayLevel::GetCurLevel()->GetPlayerPtr()->GetBroomFuel();

	if (CurFuel != RenderingAccFuel)
	{
		RenderingAccFuel = CurFuel;

		const float FuelGaugeRatio = RenderingAccFuel / MAX_FUEL;
		GaugeUI->GetGaugeInfo().Gauge = FuelGaugeRatio;
	}
}


void UI_Hub_Broom::EndHasNotBroom(GameEngineState* _Parent)
{
	if (nullptr == FrameRenderer || nullptr == GaugeUI || nullptr == IconRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	FrameRenderer->On();
	GaugeUI->On();
	IconRenderer->On();
}