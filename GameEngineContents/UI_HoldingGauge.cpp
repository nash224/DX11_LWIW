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

	GaugeUI = _Actor->CreateComponent<GaugeUIRenderer>();
	GaugeUI->AutoSpriteSizeOn();
	GaugeUI->SetAutoScaleRatio(0.5f);
	GaugeUI->SetMaterial("GaugeTexture2D");
	GaugeUI->SetSprite("Button_PressHold.png");
	GaugeUI->GetGaugeInfo().CircleGuage = 1;
	GaugeUI->Off();
}

void UI_HoldingGauge::Release()
{
	Base = nullptr;
	GaugeUI = nullptr;
}

void UI_HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == Base || nullptr == GaugeUI)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	const float BaseDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float GuageDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	Base->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	GaugeUI->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void UI_HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == GaugeUI)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	GaugeUI->GetGaugeInfo().Gauge = _Gauge;
}

void UI_HoldingGauge::On()
{
	if (nullptr == Base || nullptr == GaugeUI)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->On();
	GaugeUI->On();

	isOn = true;
}

void UI_HoldingGauge::Off()
{
	if (nullptr == Base || nullptr == GaugeUI)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Base->Off();
	GaugeUI->Off();

	isOn = false;
}


bool UI_HoldingGauge::IsOn() const
{
	return isOn;
}
