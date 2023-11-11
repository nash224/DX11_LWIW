#pragma once
#include "Dust.h"

// Ό³Έν :
class Dust_Bag : public Dust
{
public:
	// constrcuter destructer
	Dust_Bag();
	~Dust_Bag();

	// delete Function
	Dust_Bag(const Dust_Bag& _Other) = delete;
	Dust_Bag(Dust_Bag&& _Other) noexcept = delete;
	Dust_Bag& operator=(const Dust_Bag& _Other) = delete;
	Dust_Bag& operator=(Dust_Bag&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void SetTopic();


};

