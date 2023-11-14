#pragma once
#include "Dust.h"

// Ό³Έν :
class Dust_Elevator : public Dust
{
public:
	// constrcuter destructer
	Dust_Elevator();
	~Dust_Elevator();

	// delete Function
	Dust_Elevator(const Dust_Elevator& _Other) = delete;
	Dust_Elevator(Dust_Elevator&& _Other) noexcept = delete;
	Dust_Elevator& operator=(const Dust_Elevator& _Other) = delete;
	Dust_Elevator& operator=(Dust_Elevator&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void SetTopic();
	void ActiveUpperLift();

};

