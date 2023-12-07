#pragma once
#include "ALightActor.h"

// Ό³Έν :
class WitchHouseLamp : public ALightActor
{
private:
	enum class EWH_LAMPSATE
	{
		Day,
		Change,
		Night,
	};

public:
	// constrcuter destructer
	WitchHouseLamp();
	~WitchHouseLamp();

	// delete Function
	WitchHouseLamp(const WitchHouseLamp& _Other) = delete;
	WitchHouseLamp(WitchHouseLamp&& _Other) noexcept = delete;
	WitchHouseLamp& operator=(const WitchHouseLamp& _Other) = delete;
	WitchHouseLamp& operator=(WitchHouseLamp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void StartDay(GameEngineState* _Parent);
	void StartNight(GameEngineState* _Parent);


	void UpdateDay(float _Delta, GameEngineState* _Parent);
	void UpdateChange(float _Delta, GameEngineState* _Parent);

private:
	GameEngineState State;

	float NightStartTime = 0.0f;

};

