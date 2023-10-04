#pragma once

enum class EUI_TYPE
{
	None,
	Play,
	Inventory,
	Dictionary,
	MainBoard,
};


// 설명 :
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


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void Reset();

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

	bool m_SwitchOpenHub = false;								// 허브를 열 수 있습니다.
	bool m_IsHubPreServe = false;								// 현재 컴포넌트가 작동중인지 추적하는 변수입니다.
	bool m_IsActiveComponent = false;							// 허브를 닫지 않고 컴포넌트를 열지 결정합니다.

	
private:
	// this is Ellie Related Function
	void SetEllieControl(bool _Value);
};

