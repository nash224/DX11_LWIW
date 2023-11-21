#include "PreCompile.h"
#include "HoldingGauge.h"

HoldingGauge::HoldingGauge() 
{
	if (nullptr == GameEngineSprite::Find("Holding_Base.png"))
	{
		GameEngineSprite::CreateSingle("Holding_Base.png");
		GameEngineSprite::CreateSingle("Holding_Gauge.png");
	}
}

HoldingGauge::~HoldingGauge() 
{
}


void HoldingGauge::RendererSetting(GameEngineActor* _Actor)
{
	BaseRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	BaseRenderer->SetSprite("Holding_Base.png");
	BaseRenderer->Off();

	GaugeRenderer = _Actor->CreateComponent<ContentsSpriteRenderer>();
	GaugeRenderer->SetMaterial("GaugeTexture2D");
	GaugeRenderer->SetSprite("Holding_Gauge.png");
	GaugeRenderer->GetGaugeInfo().CircleGuage = 1;
	GaugeRenderer->Off();
}

void HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("렌더러를 세팅하지 않고 사용할수없습니다.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Base);
	const float GuageDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Bar);

	BaseRenderer->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	GaugeRenderer->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == GaugeRenderer)
	{
		MsgBoxAssert("렌더러를 세팅하지 않고 사용할수없습니다.");
		return;
	}

	GaugeRenderer->GetGaugeInfo().Gauge = _Gauge;
}


void HoldingGauge::On()
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BaseRenderer->On();
	GaugeRenderer->On();

	isOn = true;
}

void HoldingGauge::Off()
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BaseRenderer->Off();
	GaugeRenderer->Off();

	isOn = false;
}


bool HoldingGauge::IsOn() const
{
	return isOn;
}

void HoldingGauge::Release()
{
	BaseRenderer = nullptr;
	GaugeRenderer = nullptr;
}