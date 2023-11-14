#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class LowerLift : public StaticEntity
{
public:
	// constrcuter destructer
	LowerLift();
	~LowerLift();

	// delete Function
	LowerLift(const LowerLift& _Other) = delete;
	LowerLift(LowerLift&& _Other) noexcept = delete;
	LowerLift& operator=(const LowerLift& _Other) = delete;
	LowerLift& operator=(LowerLift&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateLift(float _Delta);



};

