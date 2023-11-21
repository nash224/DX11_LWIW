#pragma once
#include "StaticEntity.h"
#include "ALightLerp.h"


// Ό³Έν :
class SilverStarFlower : public StaticEntity
{
private:
	enum class ESILVERBELLSTATE
	{
		Day,
		Light,
		Touch,
		UnLight,
	};


public:
	// constrcuter destructer
	SilverStarFlower();
	~SilverStarFlower();

	// delete Function
	SilverStarFlower(const SilverStarFlower& _Other) = delete;
	SilverStarFlower(SilverStarFlower&& _Other) noexcept = delete;
	SilverStarFlower& operator=(const SilverStarFlower& _Other) = delete;
	SilverStarFlower& operator=(SilverStarFlower&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void LightSetting();
	void StateSetting();

	//void DayStart(GameEngineState* _Parent);
	void TouchStart(GameEngineState* _Parent);
	void UnLightStart(GameEngineState* _Parent);

	void DayUpdate(float _Delta, GameEngineState* _Parent);
	void LightUpdate(float _Delta, GameEngineState* _Parent);
	void TouchUpdate(float _Delta, GameEngineState* _Parent);

	float CalculateDistanceToEllie();
	void UpdateFlowerLostLight(GameEngineState* _Parent);
	void CreatePollenSpawner();

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;

	GameEngineState State;

	ALightLerp UpperALight;
	ALightLerp LowerALight;

};

