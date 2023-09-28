#pragma once
#include "UI_Hub_Actor.h"

// Ό³Έν :
class UI_Hub_Riding : public UI_Hub_Actor
{
public:
	// constrcuter destructer
	UI_Hub_Riding();
	~UI_Hub_Riding();

	// delete Function
	UI_Hub_Riding(const UI_Hub_Riding& _Other) = delete;
	UI_Hub_Riding(UI_Hub_Riding&& _Other) noexcept = delete;
	UI_Hub_Riding& operator=(const UI_Hub_Riding& _Other) = delete;
	UI_Hub_Riding& operator=(UI_Hub_Riding&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

