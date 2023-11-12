#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_QuickSlot : public UI_Hub_Actor
{
public:
	static int ItemSelection;
	static std::list<std::string> QuickSlotItemList;

public:
	// constrcuter destructer
	UI_Hub_QuickSlot();
	~UI_Hub_QuickSlot();

	// delete Function
	UI_Hub_QuickSlot(const UI_Hub_QuickSlot& _Other) = delete;
	UI_Hub_QuickSlot(UI_Hub_QuickSlot&& _Other) noexcept = delete;
	UI_Hub_QuickSlot& operator=(const UI_Hub_QuickSlot& _Other) = delete;
	UI_Hub_QuickSlot& operator=(UI_Hub_QuickSlot&& _Other) noexcept = delete;

	void Init();

	static void RegisterForQuickSlot(std::string_view _ItemName);

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	std::shared_ptr<GameEngineUIRenderer> m_Slot = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_ArrowLeft = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_ArrowRight = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Item = nullptr;

	float CONST_ArrowDistanceToLocalZERO = 25.0f;
};

