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
	BaseRenderer = _Actor->CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->AutoSpriteSizeOn();
	BaseRenderer->SetAutoScaleRatio(0.5f);
	BaseRenderer->SetSprite("Button_PressHold_Outline.png");
	BaseRenderer->Off();

	GaugeRenderer = _Actor->CreateComponent<ContentsUIRenderer>();
	GaugeRenderer->AutoSpriteSizeOn();
	GaugeRenderer->SetAutoScaleRatio(0.5f);
	GaugeRenderer->SetMaterial("GaugeTexture2D");
	GaugeRenderer->SetSprite("Button_PressHold.png");
	GaugeRenderer->GetGaugeInfo().CircleGuage = 1;
	GaugeRenderer->Off();
}

void UI_HoldingGauge::Release()
{
	BaseRenderer = nullptr;
	GaugeRenderer = nullptr;
}

void UI_HoldingGauge::SetPosition(const float4& _Position)
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float GuageDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	BaseRenderer->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, BaseDepth));
	GaugeRenderer->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, GuageDepth));
}

void UI_HoldingGauge::SetGauge(float _Gauge)
{
	if (nullptr == GaugeRenderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����Ҽ������ϴ�.");
		return;
	}

	GaugeRenderer->GetGaugeInfo().Gauge = _Gauge;
}

void UI_HoldingGauge::On()
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	BaseRenderer->On();
	GaugeRenderer->On();

	isOn = true;
}

void UI_HoldingGauge::Off()
{
	if (nullptr == BaseRenderer || nullptr == GaugeRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	BaseRenderer->Off();
	GaugeRenderer->Off();

	isOn = false;
}


bool UI_HoldingGauge::IsOn() const
{
	return isOn;
}
