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

	Guage = _Actor->CreateComponent<ContentsSpriteRenderer>();
	Guage->SetMaterial("GaugeTexture2D");
	Guage->SetSprite("Holding_Gauge.png");
	Guage->GetGaugeInfo().CircleGuage = 1;
	Guage->Off();
}

void HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == Base || nullptr == Guage)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Base);
	const float GuageDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Bar);

	Base->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	Guage->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == Guage)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	Guage->GetGaugeInfo().Gauge = _Gauge;
}


void HoldingGauge::On()
{
	if (nullptr == Base || nullptr == Guage)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->On();
	Guage->On();

	isOn = true;
}

void HoldingGauge::Off()
{
	if (nullptr == Base || nullptr == Guage)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->Off();
	Guage->Off();

	isOn = false;
}


bool HoldingGauge::IsOn() const
{
	return isOn;
}

void HoldingGauge::Release()
{
	Base = nullptr;
	Guage = nullptr;
}