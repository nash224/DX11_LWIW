#pragma once
#include "RendererActor.h"





// Ό³Έν :
class WitchHouseLight : public RendererActor
{
private:
	enum class EWLIGHTSTATE
	{
		Day,
		Change,
		Night,
		None,
	};

	enum class EWLIGHT_CHANGESTATE
	{
		Brighter,
		Darker,
		None,
	};

	enum class EWLIGHT_NIGHTSTATE
	{
		NightBrighter,
		NightDarker,
		None,
	};

public:
	// constrcuter destructer
	WitchHouseLight();
	~WitchHouseLight();

	// delete Function
	WitchHouseLight(const WitchHouseLight& _Other) = delete;
	WitchHouseLight(WitchHouseLight&& _Other) noexcept = delete;
	WitchHouseLight& operator=(const WitchHouseLight& _Other) = delete;
	WitchHouseLight& operator=(WitchHouseLight&& _Other) noexcept = delete;

	void Init(int Order = 0) override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void LerpLightColor(const float4& _From, const float4& _To, float _LerpTime);
	void LerpLightAlpha(float _From, float _To, float _LerpTime) const;

	// State::UPdate
	void StartDay(GameEngineState* _Parent);


	void UpdateDay(float _Delta, GameEngineState* _Parent);
	void UpdateChange(float _Delta, GameEngineState* _Parent);
	void UpdateNight(float _Delta, GameEngineState* _Parent);

	// ChangeState::Update
	void UpdateBrighter(float _Delta, GameEngineState* _Parent);
	void UpdateDarker(float _Delta, GameEngineState* _Parent);


	// NightState::Start
	void StartNightBrighter(GameEngineState* _Parent);
	void StartNightDarker(GameEngineState* _Parent);

	// NightState::Update
	void UpdateNightBrighter(float _Delta, GameEngineState* _Parent);
	void UpdateNightDarker(float _Delta, GameEngineState* _Parent);
	

private:
	GameEngineState State;
	GameEngineState ChangeLightState;
	GameEngineState NightState;

	float NightStartTime = 0.0f;
	
	float Alpha = 0.0f;

	float NightLerpTime = 0.0f;
	float NightWaitTime = 0.0f;

	bool NotUpdateColor = false;

};