#pragma once
#include "ALightLerp.h"

// Ό³Έν :
class WitchHouse : public GameEngineActor
{
public:
	// constrcuter destructer
	WitchHouse();
	~WitchHouse();

	// delete Function
	WitchHouse(const WitchHouse& _Other) = delete;
	WitchHouse(WitchHouse&& _Other) noexcept = delete;
	WitchHouse& operator=(const WitchHouse& _Other) = delete;
	WitchHouse& operator=(WitchHouse&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateHouseDebug();

private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> HouseRenderers;
	ALightLerp WindowALight;
	ALightLerp WindowRayALight;

	bool IsRendererDebug = false;
};

