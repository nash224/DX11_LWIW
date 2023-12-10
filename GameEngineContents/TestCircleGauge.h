#pragma once
#include "GaugeUIRenderer.h"

// Ό³Έν :
class TestCircleGauge : public GameEngineActor
{
public:
	// constrcuter destructer
	TestCircleGauge();
	~TestCircleGauge();

	// delete Function
	TestCircleGauge(const TestCircleGauge& _Other) = delete;
	TestCircleGauge(TestCircleGauge&& _Other) noexcept = delete;
	TestCircleGauge& operator=(const TestCircleGauge& _Other) = delete;
	TestCircleGauge& operator=(TestCircleGauge&& _Other) noexcept = delete;

	void SetTime(float _Time);

	std::shared_ptr<GaugeUIRenderer> TestRenderer;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void GaugeUpdate(float _Delta);

private:
	float Gauge = 0.0f;
	float GaugeTime = 1.0f;
	float Reverse = 1.0f;

};

