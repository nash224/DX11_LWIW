#pragma once
#include "RendererActor.h"

// Ό³Έν :
class Comet : public RendererActor
{
public:
	// constrcuter destructer
	Comet();
	~Comet();

	// delete Function
	Comet(const Comet& _Other) = delete;
	Comet(Comet&& _Other) noexcept = delete;
	Comet& operator=(const Comet& _Other) = delete;
	Comet& operator=(Comet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	float4 FallDirection = float4::ZERO;
	float FallTime = 1.0f;

};

