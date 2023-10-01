#pragma once

enum class EUI_TYPE
{
	None,
	Play,
	Inventory,
	Dictionary,
	MainBoard,
};


// Ό³Έν :
class UIManager : public GameEngineActor
{
	static GameEngineActor* g_MainUIManager;
public:
	// constrcuter destructer
	UIManager();
	~UIManager();

	// delete Function
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

	void Init();


	void OpenInventory();
	void OpenDictionary();
	void OpenMainBoard();

	void Reset();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void CheckForOpenUIComponent();
	void UpdateUIComponentOpenInput();


private:
	std::shared_ptr<class UI_Hub> m_Hub = nullptr;
	std::shared_ptr<class UI_Inventory> m_Inventory = nullptr;
	std::shared_ptr<class UI_Dictionary> m_Dictionary = nullptr;
	std::shared_ptr<class UI_InterativeMark> m_InteractiveMark = nullptr;


private:
	EUI_TYPE m_State = EUI_TYPE::None;

	bool m_SwitchOpenHub = false;
	bool m_IsHubPreServe = false;
	bool m_IsActiveComponent = false;
};

