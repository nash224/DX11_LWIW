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

void HoldingGauge::Update()
{
	if (false == IsUpdate())
	{
		return;
	}

	if (nullptr == MyParent)
	{
		MsgBoxAssert("�θ� �������� �ʰ� ����� ����Ϸ� �߽��ϴ�.");
		return;
	}

	const float4 CameraPos = PlayLevel::GetCurLevel()->GetMainCamera()->Transform.GetLocalPosition();
	float4 Pos = MyParent->Transform.GetLocalPosition();
	float4 Vector = Pos - CameraPos;

	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::PlayUI_Base);
	const float GaugeDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::PlayUI_Guage);

	Vector += Correction;

	Base->Transform.SetWorldPosition(float4(Vector.X, Vector.Y, BaseDepth));
	GuageUI->Transform.SetWorldPosition(float4(Vector.X, Vector.Y, GaugeDepth));
}


void HoldingGauge::RendererSetting(GameEngineActor* _Actor)
{
	Base = _Actor->CreateComponent<GameEngineUIRenderer>();
	Base->SetSprite("Holding_Base.png");

	GuageUI = _Actor->CreateComponent<GaugeUIRenderer>();
	GuageUI->SetMaterial("GaugeTexture2D");
	GuageUI->SetSprite("Holding_Gauge.png");
	GuageUI->GetGaugeInfo().CircleGuage = 1;

	MyParent = _Actor;

	Off();
}

void HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	Correction = _Position;

	const float BaseDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Base);
	const float GuageDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Gauge_Bar);

	Base->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	GuageUI->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == GuageUI)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	GuageUI->GetGaugeInfo().Gauge = _Gauge;
}


void HoldingGauge::On()
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->On();
	GuageUI->On();

	GameEngineObjectBase::On();

	isOn = true;
}

void HoldingGauge::Off()
{
	if (nullptr == Base || nullptr == GuageUI)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->Off();
	GuageUI->Off();

	GameEngineObjectBase::Off();

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
	MyParent = nullptr;
}