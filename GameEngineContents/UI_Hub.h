#pragma once
#include "UI_ToggleActor.h"


// ���� :
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
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void OpenInternal() override;
	void CloseInternal() override;


	void Reset();

private:
	std::shared_ptr<class UI_Hub_Tool> m_Tool = nullptr;
	std::shared_ptr<class UI_Hub_Stamina> m_Stamina = nullptr;
	std::shared_ptr<class UI_Hub_QuickSlot> m_QuickSlot = nullptr;
	std::shared_ptr<class UI_Hub_Broom> m_Broom = nullptr;
	std::shared_ptr<class UI_Hub_Calender> m_Calender = nullptr;
};

