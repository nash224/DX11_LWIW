#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class LootedItem : public StaticEntity
{
public:
	// constrcuter destructer
	LootedItem();
	~LootedItem();

	// delete Function
	LootedItem(const LootedItem& _Other) = delete;
	LootedItem(LootedItem&& _Other) noexcept = delete;
	LootedItem& operator=(const LootedItem& _Other) = delete;
	LootedItem& operator=(LootedItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

