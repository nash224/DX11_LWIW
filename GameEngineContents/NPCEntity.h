#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class NPCEntity : public InteractiveActor
{
public:
	// constrcuter destructer
	NPCEntity();
	~NPCEntity();

	// delete Function
	NPCEntity(const NPCEntity& _Other) = delete;
	NPCEntity(NPCEntity&& _Other) noexcept = delete;
	NPCEntity& operator=(const NPCEntity& _Other) = delete;
	NPCEntity& operator=(NPCEntity&& _Other) noexcept = delete;

	void InteractWithEllie();

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

protected:

};

