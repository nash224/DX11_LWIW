#pragma once
#include "UI_Ellie_Actor.h"

// Ό³Έν :
class UI_Ellie_Riding : public UI_Ellie_Actor
{
public:
	// constrcuter destructer
	UI_Ellie_Riding();
	~UI_Ellie_Riding();

	// delete Function
	UI_Ellie_Riding(const UI_Ellie_Riding& _Other) = delete;
	UI_Ellie_Riding(UI_Ellie_Riding&& _Other) noexcept = delete;
	UI_Ellie_Riding& operator=(const UI_Ellie_Riding& _Other) = delete;
	UI_Ellie_Riding& operator=(UI_Ellie_Riding&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

