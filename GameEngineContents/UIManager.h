#pragma once
#include "UI_Inventory.h"

// ���� :
class UIManager : public GameEngineActor
{
public:
	std::shared_ptr<class UI_Hub> HubPtr = nullptr;									// ���
	std::shared_ptr<class UI_Inventory> InventoryPtr = nullptr;						// �κ��丮
	std::shared_ptr<class UI_Dictionary> DictionaryPtr = nullptr;					// ����
	std::shared_ptr<class UI_InterativeMark> InteractiveMarkPtr = nullptr;			// ��ũ���
	std::shared_ptr<class UI_Conversation> UIConversationPtr = nullptr;

private:
	enum class EUI_TYPE
	{
		None,
		Play,
		Inventory,
		Dictionary,
		MainBoard,
	};

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

	std::shared_ptr<class UI_Conversation> GetConversationPtr() const;
	std::shared_ptr<class UI_Inventory> GetInventoryPtr() const;
	std::shared_ptr<class UI_InterativeMark> GetMarkPtr() const;

	void UseUIComponent();
	void DoneUIComponent();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void Reset();

	void DectectOpenUIComponent();
	void InputUpdate();

private:
	bool SwitchOpenHub = false; // ��긦 �ڵ����� ų �� �ֽ��ϴ�.
	bool HubPreServeCheck = false; // ���� ������Ʈ�� �۵��������� ��긦 ������ �� �ִ� �����Դϴ�.
	bool IsActiveComponent = false; // ��긦 ���� �ʰ� ������Ʈ�� ���� �����մϴ�.
	
private:
	// this is Ellie Related Function
	void SetEllieControl(bool _Value);
};

