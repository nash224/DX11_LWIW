#pragma once
#include "UI_ToggleActor.h"






// Ό³Έν :
class UI_ProcessManager : public UI_ToggleActor
{
public:
	// constrcuter destructer
	UI_ProcessManager();
	~UI_ProcessManager();

	// delete Function
	UI_ProcessManager(const UI_ProcessManager& _Other) = delete;
	UI_ProcessManager(UI_ProcessManager&& _Other) noexcept = delete;
	UI_ProcessManager& operator=(const UI_ProcessManager& _Other) = delete;
	UI_ProcessManager& operator=(UI_ProcessManager&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();
	void OtherProcessSetting();

	void Open();
	void GetItemListToInventoryData();
	void Close();
	 
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class UI_ProcessList> ProcessListWindow;
	std::shared_ptr<class UI_Process> ProcessWindow;

};




class UI_Process : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_Process() {}
	~UI_Process() {}

	// delete Function
	UI_Process(const UI_Process& _Other) = delete;
	UI_Process(UI_Process&& _Other) noexcept = delete;
	UI_Process& operator=(const UI_Process& _Other) = delete;
	UI_Process& operator=(UI_Process&& _Other) noexcept = delete;

	void Init();


public:
	std::shared_ptr<GameEngineUIRenderer> m_Base = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> m_Empty_Slot = nullptr;

};