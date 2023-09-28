#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_Calendar : public UI_Hub_Actor
{
public:
	// constrcuter destructer
	UI_Hub_Calendar();
	~UI_Hub_Calendar();

	// delete Function
	UI_Hub_Calendar(const UI_Hub_Calendar& _Other) = delete;
	UI_Hub_Calendar(UI_Hub_Calendar&& _Other) noexcept = delete;
	UI_Hub_Calendar& operator=(const UI_Hub_Calendar& _Other) = delete;
	UI_Hub_Calendar& operator=(UI_Hub_Calendar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

