#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>


struct OutLineEffectInfo
{
	float4 OutLineColor = float4::ONE;
	float4 ScreenSize = float4::ZERO;
	float Thickness = 2.0f;
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
};

// Ό³Έν :
class OutLineEffect : public Effect
{
public:
	// constrcuter destructer
	OutLineEffect();
	~OutLineEffect();

	// delete Function
	OutLineEffect(const OutLineEffect& _Other) = delete;
	OutLineEffect(OutLineEffect&& _Other) noexcept = delete;
	OutLineEffect& operator=(const OutLineEffect& _Other) = delete;
	OutLineEffect& operator=(OutLineEffect&& _Other) noexcept = delete;

	inline void SetOutLineColor(const float4& _Color = float4::WHITE)
	{
		OutLineInfo.OutLineColor = _Color;
	}

	inline void SetOutLineThickness(float _Thickness = 1.0f)
	{
		OutLineInfo.Thickness = _Thickness;
	}

	void DefaultSetting();

protected:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

private:
	OutLineEffectInfo OutLineInfo;

};