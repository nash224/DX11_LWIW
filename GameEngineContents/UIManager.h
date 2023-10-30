#pragma once

#include "UI_Inventory.h"

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
public:
	static UIManager* MainUIManager;
	static bool UI_Using;

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

	void OpenInventory(EINVENTORYMODE _Mode);
	void CloseInventory();

	void UseUIComponent();
	void DoneUIComponent();


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
	std::shared_ptr<class UI_Hub> m_Hub = nullptr;									// 허브
	std::shared_ptr<class UI_Inventory> m_Inventory = nullptr;						// 인벤토리
	std::shared_ptr<class UI_Dictionary> m_Dictionary = nullptr;					// 사전
	std::shared_ptr<class UI_InterativeMark> m_InteractiveMark = nullptr;			// 마크기능
	std::shared_ptr<class UI_Conversation> m_ConversationUI = nullptr;


private:
	EUI_TYPE m_State = EUI_TYPE::None;

	bool m_SwitchOpenHub = false;								// 허브를 자동으로 킬 수 있습니다.
	bool m_IsHubPreServe = false;								// 현재 컴포넌트가 작동중이지만 허브를 유지할 수 있는 변수입니다.
	bool m_IsActiveComponent = false;							// 허브를 닫지 않고 컴포넌트를 열지 결정합니다.
	bool IsOtherComponentUsed = false;

	
private:
	// this is Ellie Related Function
	void SetEllieControl(bool _Value);
};

