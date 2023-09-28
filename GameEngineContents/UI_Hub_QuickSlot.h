#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_QuickSlot : public UI_Hub_Actor
{
public:
	// constrcuter destructer
	UI_Hub_QuickSlot();
	~UI_Hub_QuickSlot();

	// delete Function
	UI_Hub_QuickSlot(const UI_Hub_QuickSlot& _Other) = delete;
	UI_Hub_QuickSlot(UI_Hub_QuickSlot&& _Other) noexcept = delete;
	UI_Hub_QuickSlot& operator=(const UI_Hub_QuickSlot& _Other) = delete;
	UI_Hub_QuickSlot& operator=(UI_Hub_QuickSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

