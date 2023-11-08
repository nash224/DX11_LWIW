#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

// Ό³Έν :
class SkyLightEffect : public Effect
{
public:
	// constrcuter destructer
	SkyLightEffect();
	~SkyLightEffect();

	// delete Function
	SkyLightEffect(const SkyLightEffect& _Other) = delete;
	SkyLightEffect(SkyLightEffect&& _Other) noexcept = delete;
	SkyLightEffect& operator=(const SkyLightEffect& _Other) = delete;
	SkyLightEffect& operator=(SkyLightEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;


};