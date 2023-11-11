#pragma once
#include "Dust.h"

// Ό³Έν :
class Dust_HandBook : public Dust
{
public:
	// constrcuter destructer
	Dust_HandBook();
	~Dust_HandBook();

	// delete Function
	Dust_HandBook(const Dust_HandBook& _Other) = delete;
	Dust_HandBook(Dust_HandBook&& _Other) noexcept = delete;
	Dust_HandBook& operator=(const Dust_HandBook& _Other) = delete;
	Dust_HandBook& operator=(Dust_HandBook&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void SetTopic();


};

