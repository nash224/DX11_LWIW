#pragma once
#include "Ellie.h"

// Ό³Έν :
class TestPlayer : public Ellie
{
public:
	// constrcuter destructer
	TestPlayer();
	~TestPlayer();

	// delete Function
	TestPlayer(const TestPlayer& _Other) = delete;
	TestPlayer(TestPlayer&& _Other) noexcept = delete;
	TestPlayer& operator=(const TestPlayer& _Other) = delete;
	TestPlayer& operator=(TestPlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

