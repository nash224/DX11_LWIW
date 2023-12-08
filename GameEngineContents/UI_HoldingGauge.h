#pragma once
#include "GaugeUIRenderer.h"

// Ό³Έν :
class UI_HoldingGauge 
{
public:
	// constrcuter destructer
	UI_HoldingGauge();
	~UI_HoldingGauge();

	// delete Function
	UI_HoldingGauge(const UI_HoldingGauge& _Other) = delete;
	UI_HoldingGauge(UI_HoldingGauge&& _Other) noexcept = delete;
	UI_HoldingGauge& operator=(const UI_HoldingGauge& _Other) = delete;
	UI_HoldingGauge& operator=(UI_HoldingGauge&& _Other) noexcept = delete;

	void RendererSetting(GameEngineActor* _Actor);
	void Release();

	void SetPosition(const float4& _Position);
	void SetGauge(float _Gauge);
	void On();
	void Off();
	bool IsOn() const;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> Base;
	std::shared_ptr<GaugeUIRenderer> GaugeUI;

	bool isOn = false;

};

