#include "PreCompile.h"
#include "TestCircleGauge.h"

TestCircleGauge::TestCircleGauge() 
{
}

TestCircleGauge::~TestCircleGauge() 
{
}


void TestCircleGauge::Start()
{
	TestRenderer = CreateComponent<GaugeUIRenderer>();
	TestRenderer->SetMaterial("GaugeTexture2D");
	TestRenderer->SetSprite("Quest_Notice_Complete.png");
	TestRenderer->AutoSpriteSizeOn();
	TestRenderer->SetAutoScaleRatio(4.0f);
	TestRenderer->GetGaugeInfo().CircleGuage = 1;
}

void TestCircleGauge::Update(float _Delta)
{
	GaugeUpdate(_Delta);
}

void TestCircleGauge::Release()
{
	TestRenderer = nullptr;
}

void TestCircleGauge::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void TestCircleGauge::SetTime(float _Time)
{
	GaugeTime = _Time;
}

void TestCircleGauge::GaugeUpdate(float _Delta)
{
	Gauge += _Delta / GaugeTime * Reverse;
	TestRenderer->GetGaugeInfo().Gauge = Gauge;

	if (Reverse > 0.0f && Gauge > 1.0f)
	{
		Reverse = -1.0f;
	}
	if (Reverse < 0.0f && Gauge < 0.0f)
	{
		Reverse = 1.0f;
	}
}