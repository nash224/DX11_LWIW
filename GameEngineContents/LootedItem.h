#pragma once
#include "InteractiveActor.h"

// Ό³Έν :
class LootedItem : public InteractiveActor
{
	friend class BackDrop_PlayLevel;

private:
	class BackDrop_PlayLevel* BackManager = nullptr;

public:
	// constrcuter destructer
	LootedItem();
	~LootedItem();

	// delete Function
	LootedItem(const LootedItem& _Other) = delete;
	LootedItem(LootedItem&& _Other) noexcept = delete;
	LootedItem& operator=(const LootedItem& _Other) = delete;
	LootedItem& operator=(LootedItem&& _Other) noexcept = delete;

	void SetStack(const int _Value);
	void SetFallingTargetPosition(const float _YPosition);


	void Init(std::string_view _ItemName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void CreateItemRenderer(std::string_view _ItemName);



private:
	void UpdateFallingItem(float _Delta);
	void UpdateItemInteraction();

private:
	std::string ItemName;
	int Stack = 0;

	const float ItemInterativeRange = 10.0f;


private:
	bool IsFalling = false;
	float FallingYDistance = 0.0f;
	const float FallingSpeed = 200.0f;

};

