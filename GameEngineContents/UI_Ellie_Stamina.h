#pragma once
#include "UI_Ellie_Actor.h"

// Ό³Έν :
class UI_Ellie_Stamina : public UI_Ellie_Actor
{
public:
	// constrcuter destructer
	UI_Ellie_Stamina();
	~UI_Ellie_Stamina();

	// delete Function
	UI_Ellie_Stamina(const UI_Ellie_Stamina& _Other) = delete;
	UI_Ellie_Stamina(UI_Ellie_Stamina&& _Other) noexcept = delete;
	UI_Ellie_Stamina& operator=(const UI_Ellie_Stamina& _Other) = delete;
	UI_Ellie_Stamina& operator=(UI_Ellie_Stamina&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

