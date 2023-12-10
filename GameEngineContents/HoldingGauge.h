#pragma once
#include "GaugeUIRenderer.h"

// Ό³Έν :
class HoldingGauge : public GameEngineObjectBase
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

	void Update();
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
	std::shared_ptr<GaugeUIRenderer> GuageUI;
	GameEngineObject* MyParent = nullptr;

	float4 Correction = float4::ZERO;

	bool isOn = false;

};

