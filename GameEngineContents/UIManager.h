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
class UI_Inventory;
class UI_Dictionary;
class UI_Ellie;
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
	std::shared_ptr<UI_Inventory> m_Inventory = nullptr;
	std::shared_ptr<UI_Inventory> m_MainActorUI = nullptr;
	std::shared_ptr<UI_Dictionary> m_Dictionary = nullptr;


private:
	EUI_TYPE m_State = EUI_TYPE::None;

	bool ActiveComponentChcek = false;
};

