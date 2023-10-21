#pragma once
#include "UI_ToggleActor.h"

class DispensationSlotInfo
{
public:
	std::shared_ptr<GameEngineUIRenderer> ItemImg = nullptr;
	std::string ItemName = "";

	int Number = 0;
};

// Ό³Έν :
class UI_Dispensation : public UI_ToggleActor
{
public:
	// constrcuter destructer
	UI_Dispensation();
	~UI_Dispensation();

	// delete Function
	UI_Dispensation(const UI_Dispensation& _Other) = delete;
	UI_Dispensation(UI_Dispensation&& _Other) noexcept = delete;
	UI_Dispensation& operator=(const UI_Dispensation& _Other) = delete;
	UI_Dispensation& operator=(UI_Dispensation&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();

	void Open();
	void Close();

	void Clear();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateKey();

private:
	std::shared_ptr<GameEngineUIRenderer> m_Base = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Empty_Slot = nullptr;
	std::shared_ptr<GameEngineUIRenderer> fire_icon_1 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> fire_icon_2 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fire_Gauge = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fire_Gauge_Pin = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_None = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_CounterClockwise = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Direction_Clockwise = nullptr;

	std::vector<DispensationSlotInfo> m_DispensationSlotInfo;

};

