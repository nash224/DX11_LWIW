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

	void Init(std::string_view _ItemName);
	void SetStack(const int _Value);

	void ActorRelease();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateItemRenderer(std::string_view _ItemName);
	void CreateItemCollision();

private:
	void UpdateItemInteraction();

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_ItemRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> m_ItemCollision = nullptr;

	std::string ItemName = "";
	int m_Stack = 0;

};

