#pragma once
#include "GaugeUIRenderer.h"

// Ό³Έν :
class HoldingGauge 
{
public:
	// constrcuter destructer
	HoldingGauge();
	~HoldingGauge();

	// delete Function
	HoldingGauge(const HoldingGauge& _Other) = delete;
	HoldingGauge(HoldingGauge&& _Other) noexcept = delete;
	HoldingGauge& operator=(const HoldingGauge& _Other) = delete;
	HoldingGauge& operator=(HoldingGauge&& _Other) noexcept = delete;

	void RendererSetting(GameEngineActor* _Actor);
	void Release();

	void SetPosition(const float4& _Position);
	void SetGauge(float _Gauge);
	void On();
	void Off();
	bool IsOn() const;

protected:


private:
	std::shared_ptr<GameEngineSpriteRenderer> Base;
	std::shared_ptr<GaugeRenderer> GuageUI;

	bool isOn = false;

};

