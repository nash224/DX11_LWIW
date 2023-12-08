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
	Base = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	Base->SetSprite("Holding_Base.png");
	Base->Off();

	GuageUI = _Actor->CreateComponent<GaugeRenderer>();
	GuageUI->SetMaterial("GaugeTexture2D");
	GuageUI->SetSprite("Holding_Gauge.png");
	GuageUI->GetGaugeInfo().CircleGuage = 1;
	GuageUI->Off();
}

void HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("렌더러를 세팅하지 않고 사용할수없습니다.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Base);
	const float GuageDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Bar);

	Base->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	GuageUI->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == GuageUI)
	{
		MsgBoxAssert("렌더러를 세팅하지 않고 사용할수없습니다.");
		return;
	}

	GuageUI->GetGaugeInfo().Gauge = _Gauge;
}


void HoldingGauge::On()
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Base->On();
	GuageUI->On();

	isOn = true;
}

void HoldingGauge::Off()
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Base->Off();
	GuageUI->Off();

	isOn = false;
}


bool HoldingGauge::IsOn() const
{
	return isOn;
}

void HoldingGauge::Release()
{
	Base = nullptr;
	GuageUI = nullptr;
}