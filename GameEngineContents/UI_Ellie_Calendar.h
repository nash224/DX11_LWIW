#pragma once
#include "UI_Ellie_Actor.h"

// Ό³Έν :
class UI_Ellie_Calendar : public UI_Ellie_Actor
{
public:
	// constrcuter destructer
	UI_Ellie_Calendar();
	~UI_Ellie_Calendar();

	// delete Function
	UI_Ellie_Calendar(const UI_Ellie_Calendar& _Other) = delete;
	UI_Ellie_Calendar(UI_Ellie_Calendar&& _Other) noexcept = delete;
	UI_Ellie_Calendar& operator=(const UI_Ellie_Calendar& _Other) = delete;
	UI_Ellie_Calendar& operator=(UI_Ellie_Calendar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

