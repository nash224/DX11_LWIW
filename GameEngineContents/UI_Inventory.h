#pragma once
#include "UI_ToggleActor.h"



struct InventoryInfo
{
public:
	std::string SourceName = "";
	unsigned int ItemCount = 0;

};


// �κ��丮 �����͸� �����ϴ� Ŭ�����Դϴ�.
// UI_Inventory���� �����͸� �����ϴ� InventoryData�� �������� �����ؼ� ������ �� ������,
// �����ϴ� ���°� ��ȭ���� �������� ������ �������ϴ�.
// ���� ���, ������ �ϳ��̰� �������� �κ��丮�� �ϳ��� ������ �ִ� ������ ��, �������� ������ �������� ������ ��������ϴ�.
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



// ���� :
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
	// ����
	void CreateBase();
	void CreateSlotArray();
	void CreateCursor();
	void CreateNoticeDropManager();

	void CreateData();

	void LockSlot(const unsigned int _Y);

	// ������
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

	// ����
	int m_CurrentSlotX = 0;
	int m_CurrentSlotY = 0;
	const unsigned int MaxSlotX = 4;
	const unsigned int MaxSlotY = 6;

	// �׸��� 
	float4 m_GridScale = float4::ZERO;
	float4 FirstGridPosition = float4::ZERO;
	const float CONST_GridSpacing = 12.0f;
	bool IsFirstPosCalculated = false;

	// Ŀ��
	const float CursorInter = 0.4f;
	const float4 NameTagPositionBaseOnSlotCenter = { 0.0f, 40.0f };

	// �ٸ� ������Ʈ�� ����ϰ� ���� ��
	bool IsOtherComponent = false;
};

