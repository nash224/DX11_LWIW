#include "PreCompile.h"
#include "UI_HoldingGauge.h"

UI_HoldingGauge::UI_HoldingGauge() 
{
	if (nullptr == GameEngineSprite::Find("Button_PressHold_Outline.png"))
	{
		GameEngineSprite::CreateSingle("Button_PressHold_Outline.png");
		GameEngineSprite::CreateSingle("Button_PressHold.png");
	}
}

UI_HoldingGauge::~UI_HoldingGauge() 
{

}


void UI_HoldingGauge::RendererSetting(GameEngineActor* _Actor)
{
	Base = _Actor->CreateComponent<GameEngineUIRenderer>();
	Base->AutoSpriteSizeOn();
	Base->SetAutoScaleRatio(0.5f);
	Base->SetSprite("Button_PressHold_Outline.png");
	Base->Off();

	Gauge = _Actor->CreateComponent<ContentsUIRenderer>();
	Gauge->AutoSpriteSizeOn();
	Gauge->SetAutoScaleRatio(0.5f);
	Gauge->SetMaterial("GaugeTexture2D");
	Gauge->SetSprite("Button_PressHold.png");
	Gauge->GetGaugeInfo().CircleGuage = 1;
	Gauge->Off();
}

void UI_HoldingGauge::Release()
{
	Base = nullptr;
	Gauge = nullptr;
}

void UI_HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == Base || nullptr == Gauge)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float GuageDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	Base->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	Gauge->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void UI_HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == Gauge)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	Gauge->GetGaugeInfo().Gauge = _Gauge;
}

void UI_HoldingGauge::On()
{
	if (nullptr == Base || nullptr == Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->On();
	Gauge->On();

	isOn = true;
}

void UI_HoldingGauge::Off()
{
	if (nullptr == Base || nullptr == Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->Off();
	Gauge->Off();

	isOn = false;
}


bool UI_HoldingGauge::IsOn() const
{
	return isOn;
}
