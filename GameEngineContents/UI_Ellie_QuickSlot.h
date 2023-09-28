#pragma once
#include "UI_Ellie_Actor.h"

// Ό³Έν :
class UI_Ellie_QuickSlot : public UI_Ellie_Actor
{
public:
	// constrcuter destructer
	UI_Ellie_QuickSlot();
	~UI_Ellie_QuickSlot();

	// delete Function
	UI_Ellie_QuickSlot(const UI_Ellie_QuickSlot& _Other) = delete;
	UI_Ellie_QuickSlot(UI_Ellie_QuickSlot&& _Other) noexcept = delete;
	UI_Ellie_QuickSlot& operator=(const UI_Ellie_QuickSlot& _Other) = delete;
	UI_Ellie_QuickSlot& operator=(UI_Ellie_QuickSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

