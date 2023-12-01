#pragma once
#include "UI_ToggleActor.h"
#include "UI_ButtonGuide.h"

static constexpr unsigned int Max_XSlot = 4;
static constexpr unsigned int Max_YSlot = 6;



struct InventoryInfo
{
public:
	std::string SourceName;
	unsigned int ItemCount = 0;

};

// 인벤토리 데이터를 관리하는 클래스입니다.
class Inventory
{
	friend class UI_Inventory;
public:
	std::vector<InventoryInfo> InventoryData;

private:
	void Init();

private:
	bool PushItem(std::string_view _ItemName, unsigned int _Count);
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


struct SelectItemInfo
{
public:
	std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
	std::string ItemName;

	int SelectCount = -1;
};


// 설명 :
class UI_Inventory : public UI_ToggleActor
{
	friend class Inventory;

private:
	static std::unique_ptr<Inventory> Data;
	static unsigned int UnlockSlotY;

private:
	struct InventoryCursorInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> CursorOutline = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Cursor = nullptr;
		std::shared_ptr<GameEngineUIRenderer> NameTooltip = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ItemFont = nullptr;

	};

	struct InventorySlotInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> SlotEmpty = nullptr;
		std::shared_ptr<GameEngineUIRenderer> Slot = nullptr;
		std::shared_ptr<GameEngineUIRenderer> ItemCount = nullptr;
	};

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
	static void PopItem(std::string_view _ItemName, unsigned int _Count);

	static bool IsEmptySlot(std::string_view _ItemName);
	static bool IsItem(std::string_view _ItemName, unsigned int _ItemCount = 1);

	static void UnlockSlot(const unsigned int _Count = 1);
	static int ReturnItemCount(std::string_view _ItemName);


	void UsingOtherComponent(EINVENTORYMODE _Mode);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

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

	void ChangeDataParent();
	void DisplayItem(const size_t _SlotNumber, std::string_view _FileName, unsigned int _Count);
	void RenewInventory();

	void OpenInternal() override;
	void CloseInternal() override;

	float4 CalculateIndexToPos(int _x, int _y);
	void CursorThis(const unsigned int _X, const unsigned int _Y);

	void ClearSlot(const unsigned int _X, const unsigned int _Y);
	void EraseSlotImg(unsigned int _X, unsigned int _Y);
	void ClearAllSlotImg();

	void OpenUpdate();



private:
	void StartInventory(GameEngineState* _Parent);
	void UpdateInventory(float _Delta, GameEngineState* _Parent);
	void EndInventory(GameEngineState* _Parent);

	void DectedCloseInventory();
	bool UpdateCursor();
	void MoveCursor(const int _X, const int _Y);

	std::string ReturnItemKRName(std::string_view _ItemName);


private:
	std::vector<std::vector<InventorySlotInfo>> InventorySlotArray;
	std::shared_ptr<class UI_DropManager> DropManager = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> InventoryBase = nullptr;

	InventoryCursorInfo CursorInfo;
	UI_ButtonGuide InventoryGuide;

	GameEngineState InventoryState;
	EINVENTORYMODE InventoryMode = EINVENTORYMODE::None;

	float4 GridScale = float4::ZERO;
	float4 FirstGridPosition = float4::ZERO;

	int CurrentSlotX = 0;
	int CurrentSlotY = 0;

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
