#pragma once

// Ό³Έν :
class UI_ProcessManager : public GameEngineActor
{
	friend class UI_ProcessList;
	friend class UI_ProcessB;

public:
	static UI_ProcessManager* ProcessManager;

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
	void Close();

	void JuicyDone();

	 
protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void OpenProcessWindow(std::string_view ProductName, int _ScrCount);
	void OpenListWindow();
	std::string GetOpenSoundFileName();

	void CreateJuicyItem();

private:
	std::shared_ptr<class UI_ProcessList> ProcessListWindow;
	std::shared_ptr<class UI_ProcessB> ProcessWindow;

	std::string CreatedProductName;
	bool IsJuicying = false;

};


