#pragma once
#include "UI_ToggleActor.h"



struct InventoryInfo
{
public:
	std::string SourceName = "";
	unsigned int ItemCount = 0;

};


// 인벤토리 데이터를 관리하는 클래스입니다.
// UI_Inventory에도 데이터를 관리하는 InventoryData를 전역으로 생성해서 관리할 수 있지만,
// 생각하는 형태가 위화감이 느껴져서 역할을 나눴습니다.
// 예를 들어, 가방은 하나이고 레벨마다 인벤토리를 하나씩 가지고 있는 느낌이 들어서, 레벨마다 가방을 돌려쓰는 구조로 만들었습니다.
class Inventory
{
	friend class UI_Inventory;
public:
	std::vector<InventoryInfo> InventoryData;

private:
	void Init();

private:
	void PushItem(std::string_view _ItemName, unsigned int _Count);
	void ClearData(const unsigned int _X, const unsigned int _Y);
	int IsContain(std::string_view _ItemName);
	int IsContain(unsigned int _X, unsigned int _Y);

	void RenewInventory();

private:
	UI_Inventory* InventoryParent = nullptr;

};



struct InventorySlotComposition
{
public:
	std::shared_ptr<GameEngineUIRenderer> SlotEmpty = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Slot = nullptr;
};

struct InventoryCursorComposition
{
public:
	std::shared_ptr<GameEngineUIRenderer> CursorOutline = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NameTooltip = nullptr;

};



// 설명 :
class UI_Inventory : public UI_ToggleActor
{
	friend class Inventory;

public:
	static UI_Inventory* MainInventory;

private:
	static std::shared_ptr<Inventory> Data;
	static unsigned int UnlockSlotY;

public:
	// constrcuter destructer
	UI_Inventory();
	~UI_Inventory();

	// delete Function
	UI_Inventory(const UI_Inventory& _Other) = delete;
	UI_Inventory(UI_Inventory&& _Other) noexcept = delete;
	UI_Inventory& operator=(const UI_Inventory& _Other) = delete;
	UI_Inventory& operator=(UI_Inventory&& _Other) noexcept = delete;

	void Init();

	static void PushItem(std::string_view _ItemName, unsigned int _Count = 1);
	void UnlockSlot(const unsigned int _Count = 1);


	void UsingOtherComponent(bool _Value);
	int ReturnItemCount(std::string_view _ItemName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	// 생성
	void CreateBase();
	void CreateSlotArray();
	void CreateCursor();
	void CreateNoticeDropManager();

	void CreateData();

	void LockSlot(const unsigned int _Y);

	// 데이터
	void ChangeDataParent();
	void DisplayItem(const size_t _SlotNumber, std::string_view _FileName);
	void RenewInventory();

	// Open, Close
	void OpenChild() override;
	void CloseChild() override;

	float4 CalculateIndexToPos(const size_t _x, const size_t _y);
	void SelectSlot(const unsigned int _X, const unsigned int _Y);

	void ClearSlot(const unsigned int _X, const unsigned int _Y);
	void EraseSlotImg(const int _X, const int _Y);
	void ClearAllSlotImg();

	void OnLevelStart();

private:
	void UpdateInventory(float _Delta);
	void DectedCloseInventory();
	void UpdateCursor();
	void MoveCursor(const int _X, const int _Y);


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_InventoryBase = nullptr;
	std::vector<std::vector<InventorySlotComposition>> InventorySlotArray;

	std::shared_ptr<class UI_DropManager> m_DropManager = nullptr;
	InventoryCursorComposition m_CursorComposition;

	// 슬롯
	int m_CurrentSlotX = 0;
	int m_CurrentSlotY = 0;
	const unsigned int MaxSlotX = 4;
	const unsigned int MaxSlotY = 6;

	// 그리드 
	float4 m_GridScale = float4::ZERO;
	float4 FirstGridPosition = float4::ZERO;
	const float CONST_GridSpacing = 12.0f;
	bool IsFirstPosCalculated = false;

	// 커서
	const float CursorInter = 0.4f;
	const float4 NameTagPositionBaseOnSlotCenter = { 0.0f, 40.0f };

	// 다른 컴포넌트와 사용하고 있을 때
	bool IsOtherComponent = false;
};

