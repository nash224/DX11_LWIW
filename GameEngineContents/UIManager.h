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


// ���� :
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
	std::shared_ptr<class UI_Hub> m_Hub = nullptr;									// ���
	std::shared_ptr<class UI_Inventory> m_Inventory = nullptr;						// �κ��丮
	std::shared_ptr<class UI_Dictionary> m_Dictionary = nullptr;					// ����
	std::shared_ptr<class UI_InterativeMark> m_InteractiveMark = nullptr;			// ��ũ���
	std::shared_ptr<class UI_Conversation> m_ConversationUI = nullptr;


private:
	EUI_TYPE m_State = EUI_TYPE::None;

	bool m_SwitchOpenHub = false;								// ��긦 �ڵ����� ų �� �ֽ��ϴ�.
	bool m_IsHubPreServe = false;								// ���� ������Ʈ�� �۵��������� ��긦 ������ �� �ִ� �����Դϴ�.
	bool m_IsActiveComponent = false;							// ��긦 ���� �ʰ� ������Ʈ�� ���� �����մϴ�.
	bool IsOtherComponentUsed = false;

	
private:
	// this is Ellie Related Function
	void SetEllieControl(bool _Value);
};

