#pragma once
#include "Plant.h"

// Ό³Έν :
class WitchFlower : public Plant
{
public:
	// constrcuter destructer
	WitchFlower();
	~WitchFlower();

	// delete Function
	WitchFlower(const WitchFlower& _Other) = delete;
	WitchFlower(WitchFlower&& _Other) noexcept = delete;
	WitchFlower& operator=(const WitchFlower& _Other) = delete;
	WitchFlower& operator=(WitchFlower&& _Other) noexcept = delete;

	
	void Init();
	void RendererSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RootInternal() override;


private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;

	const float RenderYCorrection = 34.0f;

};

