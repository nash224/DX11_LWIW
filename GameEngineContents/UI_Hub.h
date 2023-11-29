#pragma once
#include "UI_ToggleActor.h"


// Ό³Έν :
class UI_Hub : public UI_ToggleActor
{
public:
	// constrcuter destructer
	UI_Hub();
	~UI_Hub();

	// delete Function
	UI_Hub(const UI_Hub& _Other) = delete;
	UI_Hub(UI_Hub&& _Other) noexcept = delete;
	UI_Hub& operator=(const UI_Hub& _Other) = delete;
	UI_Hub& operator=(UI_Hub&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void OpenInternal() override;
	void CloseInternal() override;


	void Reset();

private:
	std::shared_ptr<class UI_Hub_Tool> UITool = nullptr;
	std::shared_ptr<class UI_Hub_Stamina> UIStamina = nullptr;
	std::shared_ptr<class UI_Hub_QuickSlot> UIQuickSlot = nullptr;
	std::shared_ptr<class UI_Hub_Broom> UIBroom = nullptr;
	std::shared_ptr<class UI_Hub_Calender> UICalender = nullptr;
	std::shared_ptr<class UI_Hub_MainBoard> UIMainBoard = nullptr;
};

