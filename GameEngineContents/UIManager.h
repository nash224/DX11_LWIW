#pragma once
#include "UI_Inventory.h"

// 설명 :
class UIManager : public GameEngineActor
{
public:
	std::shared_ptr<class UI_Hub> HubPtr = nullptr;									// 허브
	std::shared_ptr<class UI_Inventory> InventoryPtr = nullptr;						// 인벤토리
	std::shared_ptr<class UI_Dictionary> DictionaryPtr = nullptr;					// 사전
	std::shared_ptr<class UI_InterativeMark> InteractiveMarkPtr = nullptr;			// 마크기능
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
	bool SwitchOpenHub = false; // 허브를 자동으로 킬 수 있습니다.
	bool HubPreServeCheck = false; // 현재 컴포넌트가 작동중이지만 허브를 유지할 수 있는 변수입니다.
	bool IsActiveComponent = false; // 허브를 닫지 않고 컴포넌트를 열지 결정합니다.
	
private:
	// this is Ellie Related Function
	void SetEllieControl(bool _Value);
};

