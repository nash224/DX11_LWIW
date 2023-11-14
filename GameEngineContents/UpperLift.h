#pragma once
#include "StaticEntity.h"

enum class EUPPERLIFTSTATE
{
	Dust,
	Lift,
	None,
};


// Ό³Έν :
class UpperLift : public StaticEntity
{
private:
	static EUPPERLIFTSTATE s_State;

public:
	// constrcuter destructer
	UpperLift();
	~UpperLift();

	// delete Function
	UpperLift(const UpperLift& _Other) = delete;
	UpperLift(UpperLift&& _Other) noexcept = delete;
	UpperLift& operator=(const UpperLift& _Other) = delete;
	UpperLift& operator=(UpperLift&& _Other) noexcept = delete;

	void Init();

	static void ActiveLift();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void StateSetting();

	void StartLift(GameEngineState* _Parent);

	void UpdateDust(float _Delta, GameEngineState* _Parent);
	void UpdateLift(float _Delta, GameEngineState* _Parent);

private:
	GameEngineState State;


};

