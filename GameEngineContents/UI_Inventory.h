#pragma once
#include "UI_ToggleActor.h"

#define Max_XSlot  4
#define Max_YSlot  6

#define INVENTORY_POSITION { -288.0f , 28.0f }

constexpr float GridSpacing = 12.0f;
constexpr float CursorInter = 0.4f;



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
	void PopItem(std::string_view _ItemName, unsigned int _Count);

	void ClearData(const unsigned int _X, const unsigned int _Y);
	void ClearData(const unsigned int _SlotNumber);

	bool CheckEmptySlot(std::string_view _ItemName);
	bool IsContain(std::string_view _ItemName);
	bool IsContain(unsigned int _X, unsigned int _Y);
	int ReturnSlotNumber(std::string_view _ItemName);
	InventoryInfo& ReturnInventoryInfo(unsigned int _X, unsigned int _Y);

	InventoryInfo* Find(std::string_view _ItemName);

	void RenewInventory();

private:
	UI_Inventory* InventoryParent = nullptr;

};


enum class EINVENTORYMODE
{
	Normal,
	Dispensation,
	None,
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




struct SelectItemInfo
{
public:
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
	std::string ItemName = "";

	int SelectCount = -1;
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

	// 생성
	void Init();

	static void PushItem(std::string_view _ItemName, unsigned int _Count = 1);
	void PopItem(std::string_view _ItemName, unsigned int _Count);

	bool IsEmptySlot(std::string_view _ItemName);

	void UnlockSlot(const unsigned int _Count = 1);


	void UsingOtherComponent(EINVENTORYMODE _Mode);
	int ReturnItemCount(std::string_view _ItemName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	// 생성 : 인벤토리
	void CreateBase();
	void CreateSlotArray();
	void CreateCursor();
	void StateSetting();

	// 생성 : UI Drop
	void CreateNoticeDropManager();

	// 생성 : 데이터
	void CreateData();

	void ExternUISetting();


	void LockSlot(const unsigned int _Y);

	// 데이터
	void ChangeDataParent();
	void DisplayItem(const size_t _SlotNumber, std::string_view _FileName);
	void RenewInventory();

	// Open, Close
	void OpenChild() override;
	void CloseChild() override;

	float4 CalculateIndexToPos(const size_t _x, const size_t _y);
	void CursorThis(const unsigned int _X, const unsigned int _Y);

	// 슬롯 클리어
	void ClearSlot(const unsigned int _X, const unsigned int _Y);
	void EraseSlotImg(const int _X, const int _Y);
	void ClearAllSlotImg();

	// 레벨 초기화
	void OnLevelStart();



private:
	void UpdateInventory(float _Delta, GameEngineState* _Parent);
	void DectedCloseInventory();
	bool UpdateCursor();
	void MoveCursor(const int _X, const int _Y);


private:
	std::vector<std::vector<InventorySlotComposition>> InventorySlotArray;
	std::shared_ptr<class UI_DropManager> m_DropManager = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_InventoryBase = nullptr;

	InventoryCursorComposition m_CursorComposition;

	GameEngineState m_InventoryState;
	EINVENTORYMODE m_Mode = EINVENTORYMODE::None;

	float4 m_GridScale = float4::ZERO;
	float4 FirstGridPosition = float4::ZERO;

	int m_CurrentSlotX = 0;
	int m_CurrentSlotY = 0;

	bool IsFirstPosCalculated = false;

	const float4 NameTagPosition = { 0.0f, 40.0f };




private:
	// 외부
	void UpdateDispensation(float _Delta, GameEngineState* _Parent);
	bool UpdateDispensationSelect();
	void DispensationSelectThis();
	void DispensationUnSelectThis(int _SlotNumber);

	int ReturnSelectNumber(int _XSlot, int _YSlot);
	int ReturnEmptySelectSlot();
	void UnSelectAll();

private:
	std::vector<SelectItemInfo> SelectItem;
	bool IsJustOpen = false;

};
