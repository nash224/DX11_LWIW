#pragma once
#include "Dust.h"

// Ό³Έν :
class Dust_Pot : public Dust
{
public:
	// constrcuter destructer
	Dust_Pot();
	~Dust_Pot();

	// delete Function
	Dust_Pot(const Dust_Pot& _Other) = delete;
	Dust_Pot(Dust_Pot&& _Other) noexcept = delete;
	Dust_Pot& operator=(const Dust_Pot& _Other) = delete;
	Dust_Pot& operator=(Dust_Pot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void SetTopic();


	void StartEvent();
	void QuestAccept();


};

