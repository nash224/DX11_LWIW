#pragma once
#include "InteractiveActor.h"

// Ό³Έν :
class StaticEntity : public InteractiveActor
{
public:
	// constrcuter destructer
	StaticEntity();
	~StaticEntity();

	// delete Function
	StaticEntity(const StaticEntity& _Other) = delete;
	StaticEntity(StaticEntity&& _Other) noexcept = delete;
	StaticEntity& operator=(const StaticEntity& _Other) = delete;
	StaticEntity& operator=(StaticEntity&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

