#include "PreCompile.h"
#include "UI_Inventory.h"

#include "UIManager.h"
#include "UI_DropManager.h"
#include "UI_Dispensation.h"

#include "ItemData.h"

// ������ �迭�� 1���� �迭�� �����մϴ�.
void Inventory::Init()
{
	int Amount = Max_XSlot * Max_YSlot;

	InventoryData.resize(Amount);
}


// �������� �����Ϳ� �ֽ��ϴ�. 
// �κ��丮�� ������ �̸��� �������� ������ �������� ���� ���ϰ�, �������� ������ �� ���Կ� �ֽ��ϴ�.
bool Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	int LockNumber = Max_XSlot * InventoryParent->UnlockSlotY;

	int Value = ReturnSlotNumber(_ItemName);

	bool isNotContainItem = (-1 == Value);
	if (isNotContainItem)
	{
		// ���ڸ��� ������ ���ڸ��� ã�Ƽ�
		for (int i = 0; i < LockNumber; i++)
		{
			if (true == InventoryData[i].SourceName.empty())
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = static_cast<int>(i);
				break;
			}

			bool IsNotEmptySlot = (i == LockNumber - 1);
			if (IsNotEmptySlot)
			{
				// �κ��丮�� �� á�ٴ� �ǹ̷� PopUp UI�� ��û�մϴ�.
				// PopUp UI
				return false;
			}
		}
	}
	else
	{
		InventoryData[Value].ItemCount += _Count;
	}

	InventoryParent->DisplayItem(static_cast<size_t>(Value), _ItemName, InventoryData[Value].ItemCount);

	return true;
}

// �������� ��������ŭ ���ϴ�.
void Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
	InventoryInfo* SlotInfo = Find(_ItemName);
	bool isNotEnoughItem = (SlotInfo->ItemCount < static_cast<int>(_Count));
	if (isNotEnoughItem)
	{
		MsgBoxAssert("����Ϸ��� �������� ������ �����ϴ�. ");
		return;
	}

	SlotInfo->ItemCount -= _Count;

	bool isZeroCount = (SlotInfo->ItemCount <= 0);
	if (isZeroCount)
	{
		ClearData(ReturnSlotNumber(_ItemName));
	}
	else
	{
		InventoryParent->DisplayItem(static_cast<size_t>(ReturnSlotNumber(_ItemName)), _ItemName, SlotInfo->ItemCount);
	}
}

// �󽽷��� �ִ��� �˻��մϴ�.
bool Inventory::CheckEmptySlot(std::string_view _ItemName)
{
	unsigned int UnlockSlotCount = UI_Inventory::UnlockSlotY * Max_YSlot;

	if (true == IsContain(_ItemName))
	{
		return true;
	}

	for (unsigned int i = 0; i < UnlockSlotCount; i++)
	{
		if (0 == InventoryData[i].ItemCount)
		{
			return true;
		}
	}

	return false;
}

// �����Ϳ� ������ �̸��� ���� �������� �ִ��� �˻��մϴ�.
bool Inventory::IsContain(std::string_view _ItemName)
{
	std::string ItemName = _ItemName.data();
	for (int y = 0; y < InventoryData.size(); y++)
	{
		if (ItemName == InventoryData[y].SourceName)
		{
			return true;
		}
	}

	return false;
}

// �ش� ���Կ� �������� �ִ��� Ȯ���մϴ�.
bool Inventory::IsContain(unsigned int _X, unsigned int _Y)
{
	int MaxSlot = Max_XSlot;
	unsigned int Value = _Y * MaxSlot + _X;

	bool isContain = (false == InventoryData[Value].SourceName.empty());
	if (isContain)
	{
		return true;
	}

	return false;
}

// �κ��丮�� ���� �̸��� ���� �������� ���Գѹ��� ��ȯ�մϴ�.
// ������ -1�� ��ȯ�˴ϴ�.
int Inventory::ReturnSlotNumber(std::string_view _ItemName)
{
	for (int i = 0; i < InventoryData.size(); i++)
	{
		if (_ItemName == InventoryData[i].SourceName)
		{
			return i;
		}
	}

	return -1;
}

InventoryInfo& Inventory::ReturnInventoryInfo(unsigned int _X, unsigned int _Y)
{
	unsigned int Value = _Y * Max_XSlot + _X;
	return InventoryData[Value];
}


InventoryInfo* Inventory::Find(std::string_view _ItemName)
{
	for (int i = 0; i < InventoryData.size(); i++)
	{
		if (_ItemName == InventoryData[i].SourceName)
		{
			return &InventoryData[i];
		}
	}

	return nullptr;
}



void Inventory::ClearData(const unsigned int _X, const unsigned int _Y)
{
	if (false == IsContain(_X, _Y))
	{
		MsgBoxAssert("�������� �ʴ� ������ ������� �߽��ϴ�.");
		return;
	}

	if (true == InventoryData.empty())
	{
		MsgBoxAssert("�����Ϳ� �ƹ��͵� ������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("�θ� �𸨴ϴ�. �����ϼ���");
		return;
	}

	int MaxSlot = Max_XSlot;

	int Value = _Y * MaxSlot + _X;

	InventoryData[Value].SourceName.clear();
	InventoryData[Value].ItemCount = 0;

	InventoryParent->EraseSlotImg(_X, _Y);
}


void Inventory::ClearData(const unsigned int _SlotNumber)
{
	InventoryData[_SlotNumber].SourceName.clear();
	InventoryData[_SlotNumber].ItemCount = 0;

	int MaxSlot = Max_XSlot;
	int XSlot = _SlotNumber % MaxSlot;
	int YSlot = _SlotNumber / MaxSlot;

	InventoryParent->EraseSlotImg(XSlot, YSlot);
}

// �κ��丮�� �����մϴ�.
void Inventory::RenewInventory()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("�θ� �������� �ʰ� �̹����� ��� �� �����ϴ�.");
		return;
	}

	for (int i = 0; i < InventoryData.size(); i++)
	{
		if (false == InventoryData[i].SourceName.empty())
		{
			InventoryParent->DisplayItem(i, InventoryData[i].SourceName, InventoryData[i].ItemCount);
		}
	}
}


std::unique_ptr<Inventory> UI_Inventory::Data = nullptr;
unsigned int UI_Inventory::UnlockSlotY = 0;
UI_Inventory::UI_Inventory()
{
	if (nullptr == GameEngineSound::FindSound("SFX_Getltem_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Getltem");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

UI_Inventory::~UI_Inventory()
{
}

void UI_Inventory::Start()
{
	if (nullptr == Data)
	{
		CreateData();
		UnlockSlotY = 2;
	}

	UI_ToggleActor::Start();
}

void UI_Inventory::Update(float _Delta)
{
	if (nullptr != Data && this != Data->InventoryParent)
	{
		OpenUpdate();
	}

	InventoryState.Update(_Delta);
}

void UI_Inventory::Release()
{
	Data = nullptr;

	DropManager = nullptr;
	InventoryBase = nullptr;
	CursorInfo.Cursor = nullptr;
	CursorInfo.CursorOutline = nullptr;
	CursorInfo.NameTooltip = nullptr;
	CursorInfo.ItemFont = nullptr;

	InventorySlotArray.clear();
}

#pragma region Setting
void UI_Inventory::Init()
{
	CreateBase();
	CreateSlotArray();
	CreateCursor();
	StateSetting();

	// ������ ȹ�� �˸�â �Ŵ����Դϴ�.
	CreateNoticeDropManager();

	ExternUISetting();

	LockSlot(UnlockSlotY);

	const float4 INVENTORY_POSITION = float4{ -288.0f , 28.0f };
	Transform.AddLocalPosition(INVENTORY_POSITION);


	std::vector<ButtonInfoParameter> Paras =
	{
		{ EBUTTONTYPE::Arrow_1, "Ŀ�� �̵�"},
		{ EBUTTONTYPE::S, "�ݱ�"},
	};
	InventoryGuide.SetGuideInfo(this, Paras);

	OpenUpdate();
}

void UI_Inventory::CreateBase()
{
	const float4& BasePosition = { 0.0f , 0.0f , DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base) };

	InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Base);
	InventoryBase->SetSprite("Inventory_Base.png");
	InventoryBase->Transform.AddLocalPosition(BasePosition);
}

void UI_Inventory::CreateSlotArray()
{
	const std::shared_ptr<GameEngineTexture>& Texture = GameEngineTexture::Find("Inventory_Empty_Slot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	GridScale = Texture->GetScale();

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);
	const float4& ItemCountCorrection = float4(18.0f, -12.0f);
	const float fontSize = 8.0f;

	InventorySlotArray.resize(Max_YSlot);
	for (unsigned int y = 0; y < static_cast<unsigned int>(InventorySlotArray.size()); y++)
	{
		InventorySlotArray[y].resize(Max_XSlot);
		for (unsigned int x = 0; x < Max_XSlot; x++)
		{
			const float4& IndexPos = CalculateIndexToPos(x, y);

			std::shared_ptr<GameEngineUIRenderer> Empty = CreateComponent<GameEngineUIRenderer>();
			Empty->SetSprite("Inventory_Empty_Slot.png");
			Empty->Transform.SetLocalPosition(float4(IndexPos.X, IndexPos.Y, FrameDepth));
			InventorySlotArray[y][x].SlotEmpty = Empty;

			std::shared_ptr<GameEngineUIRenderer> Slot = CreateComponent<GameEngineUIRenderer>();
			Slot->Transform.SetLocalPosition(float4(IndexPos.X, IndexPos.Y, IconDepth));
			Slot->Off();
			InventorySlotArray[y][x].Slot = Slot;

			const float4& ItemCountPos = float4(IndexPos.X + ItemCountCorrection.X, IndexPos.Y + ItemCountCorrection.Y, FontDepth);

			std::shared_ptr<GameEngineUIRenderer> ItemCount = CreateComponent<GameEngineUIRenderer>();
			ItemCount->Transform.SetLocalPosition(ItemCountPos);
			ItemCount->SetText(GlobalValue::Font_Sandoll, "", fontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_RIGHT);
			ItemCount->Off();

			InventorySlotArray[y][x].ItemCount = ItemCount;
		}
	}
}


void UI_Inventory::CreateCursor()
{
	if (nullptr == GameEngineSprite::Find("Inventory_Cursor.png"))
	{
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
	}

	static constexpr float CursorInter = 0.4f;

	std::shared_ptr<GameEngineUIRenderer> CurSor = CreateComponent<GameEngineUIRenderer>();
	CurSor->CreateAnimation("Cursor", "Inventory_Cursor.png", CursorInter);
	CurSor->ChangeAnimation("Cursor");
	CurSor->AutoSpriteSizeOn();
	CursorInfo.Cursor = CurSor;

	std::shared_ptr<GameEngineUIRenderer> CurSorOutLine = CreateComponent<GameEngineUIRenderer>();
	CurSorOutLine->SetSprite("Inventory_CursorOutline.png");
	CursorInfo.CursorOutline = CurSorOutLine;

	std::shared_ptr<GameEngineUIRenderer> NameTooltip = CreateComponent<GameEngineUIRenderer>();
	NameTooltip->SetSprite("Inventory_NameTooltip.png");
	NameTooltip->GetImageTransform().SetLocalScale(float4(96.0f, 28.0f));
	NameTooltip->Off();
	CursorInfo.NameTooltip = NameTooltip;


	const float FontSize = 14.0f;

	std::shared_ptr<GameEngineUIRenderer> ItemFont = CreateComponent<GameEngineUIRenderer>();
	ItemFont->SetText(GlobalValue::Font_Sandoll, "", FontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	ItemFont->Off();
	CursorInfo.ItemFont = ItemFont;


	CursorThis(0, 0);
}


void UI_Inventory::CreateNoticeDropManager()
{
	DropManager = GetLevel()->CreateActor<UI_DropManager>(EUPDATEORDER::UIMagnaer);
	DropManager->Init();
}

// ������ �迭�� �ѹ��� �����˴ϴ�.
// �������� �ѹ��� ����˴ϴ�.
void UI_Inventory::CreateData()
{
#ifdef _DEBUG
	static bool InitCheck = false;
	if (true == InitCheck)
	{
		MsgBoxAssert("�����͸� 2�� �����Ϸ� �߽��ϴ�.");
		return;
	}

	InitCheck = true;

#endif // DEBUG


	Data = std::make_unique<Inventory>();
	Data->InventoryParent = this;
	Data->Init();
}

void UI_Inventory::ExternUISetting()
{
	SelectItem.resize(3);

	for (unsigned int i = 0; i < static_cast<unsigned int>(SelectItem.size()); i++)
	{
		SelectItem[i].Cursor = CreateComponent<GameEngineUIRenderer>();
		SelectItem[i].Cursor->SetSprite("Inventory_SelectCursor.png");
		SelectItem[i].Cursor->Off();
	}
}

#pragma endregion


void UI_Inventory::LockSlot(const unsigned int _Y)
{
	for (unsigned int y = _Y; y < InventorySlotArray.size(); y++)
	{
		for (unsigned int x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			Slot->SetSprite("Inventory_SlotLock.png");
			Slot->On();
		}
	}
}

void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count/* = 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�������� �ʴ� �����Ϳ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	if (false == Data->CheckEmptySlot(_ItemName))
	{
		// UI Dont Empty Slot Alert!!
		OutputDebugStringA("�󽽷��� �����ϴ�.");
		return;
	}


	if (Data->PushItem(_ItemName, _Count))
	{
		if (nullptr != UI_DropManager::DropManager)
		{
			UI_DropManager::DropManager->NoticeItemDrop(_ItemName);
		}
	}
}

void UI_Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	Data->PopItem(_ItemName, _Count);
}

bool UI_Inventory::IsEmptySlot(std::string_view _ItemName)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return false;
	}

	return Data->CheckEmptySlot(_ItemName);
}

bool UI_Inventory::IsItem(std::string_view _ItemName, unsigned int _ItemCount /*= 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return false;
	}

	InventoryInfo* FindItem = Data->Find(_ItemName);
	if (nullptr == FindItem)
	{
		return false;
	}

	if (FindItem->ItemCount >= _ItemCount)
	{
		return true;
	}

	return false;
}

void UI_Inventory::UnlockSlot(const unsigned int _Count /*= 1*/)
{
	unsigned int PrevUnlockSlotY = UnlockSlotY;

	UnlockSlotY += _Count;

	bool IsMaxSlot = (UnlockSlotY > Max_YSlot);
	if (IsMaxSlot)
	{
		UnlockSlotY = Max_YSlot;
	}

	bool isNotChangeSlot = (PrevUnlockSlotY == UnlockSlotY);
	if (isNotChangeSlot)
	{
		return;
	}

	const std::shared_ptr<UI_Inventory>& InventoryPtr = PlayLevel::GetCurLevel()->GetUIManagerPtr()->GetInventoryPtr();

	for (unsigned int y = PrevUnlockSlotY; y < UnlockSlotY; y++)
	{
		for (unsigned int x = 0; x < InventoryPtr->InventorySlotArray[y].size(); x++)
		{
			const std::shared_ptr<GameEngineUIRenderer>& Slot = InventoryPtr->InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("�������� �ʴ� ���Կ� �����Ϸ� �߽��ϴ�.");
				return;
			}

			Slot->Off();
		}
	}
}

int UI_Inventory::ReturnItemCount(std::string_view _ItemName)
{
	InventoryInfo* SlotInfo = Data->Find(_ItemName);

	if (nullptr == SlotInfo)
	{
		return 0;
	}

	return SlotInfo->ItemCount;
}


void UI_Inventory::UsingOtherComponent(EINVENTORYMODE _Mode)
{
	InventoryState.ChangeState(_Mode);
}

void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʴµ� �������� �θ� �ٲٷ��� �߽��ϴ�.");
		return;
	}

	Data->InventoryParent = this;
}

void UI_Inventory::DisplayItem(const size_t _SlotNumber, std::string_view _FileName, unsigned int _Count)
{
	size_t Number = _SlotNumber;
	size_t SlotX = Number % Max_XSlot;
	size_t SlotY = Number / Max_XSlot;

	const InventorySlotInfo& SlotInfo = InventorySlotArray[SlotY][SlotX];
	std::weak_ptr<GameEngineUIRenderer> Slot = SlotInfo.Slot;
	if (Slot.expired())
	{
		MsgBoxAssert("�������� �ʾҰų� �������� �ʴ� �����Դϴ�.");
		return;
	}

	Slot.lock()->SetSprite(_FileName.data() + std::string(".png"));
	Slot.lock()->On();

	std::weak_ptr<GameEngineUIRenderer> CountFont = SlotInfo.ItemCount;
	if (true == CountFont.expired())
	{
		MsgBoxAssert("�������� �ʾҰų� �������� �ʴ� �����Դϴ�.");
		return;
	}

	CountFont.lock()->ChangeText(std::to_string(_Count));
	CountFont.lock()->On();
}

void UI_Inventory::RenewInventory()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�������� �ʴ� �����Ϳ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	Data->RenewInventory();
}


// �ڽĿ��� ���ְ� ���� �ൿ�� �����մϴ�.
void UI_Inventory::OpenInternal()
{
	OpenUpdate();
	SFXFunction::PlaySFX("SFX_Open_01.wav");
}

void UI_Inventory::CloseInternal()
{
	if (EINVENTORYMODE::Dispensation == InventoryMode)
	{
		UnSelectAll();
	}

	InventoryMode = EINVENTORYMODE::None;

	InventoryState.ChangeState(EINVENTORYMODE::None);
}

float4 UI_Inventory::CalculateIndexToPos(int _x, int _y)
{
	static constexpr float GridSpacing = 12.0f;

	if (false == IsFirstPosCalculated)
	{
		float4 HGridScale = GridScale.Half();
		FirstGridPosition.X = -((GridSpacing / 2.0f) + HGridScale.X) * ((static_cast<float>(Max_XSlot / 2) - 0.5f) * 2.0f);
		FirstGridPosition.Y = ((GridSpacing / 2.0f) + HGridScale.Y) * ((static_cast<float>(Max_YSlot / 2) - 0.5f) * 2.0f);

		IsFirstPosCalculated = true;
	}

	float4 TargetDistance = { static_cast<float>(_x) * (GridSpacing + GridScale.X) , -static_cast<float>(_y) * (GridSpacing + GridScale.Y) };
	float4 ReturnValue = FirstGridPosition + TargetDistance;
	return ReturnValue;
}


void UI_Inventory::CursorThis(const unsigned int _X, const unsigned int _Y)
{
	const float4& IndexPosition = CalculateIndexToPos(_X, _Y);


	const float CursorDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
	const float OutLineDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::CursorOutLine);

	if (nullptr == CursorInfo.Cursor
		|| nullptr == CursorInfo.CursorOutline
		|| nullptr == CursorInfo.NameTooltip)
	{
		MsgBoxAssert("Ŀ���� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	CursorInfo.Cursor->Transform.SetLocalPosition(float4(IndexPosition.X, IndexPosition.Y, CursorDepth));
	CursorInfo.CursorOutline->Transform.SetLocalPosition(float4(IndexPosition.X, IndexPosition.Y, OutLineDepth));

	if (true == Data->IsContain(_X, _Y))
	{
		const float TooltipDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
		const float ItemFontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

		const float FontYCorrection = 6.0f;

		CursorInfo.NameTooltip->Transform.SetLocalPosition(float4(IndexPosition.X, IndexPosition.Y + NameTagPosition.Y, TooltipDepth));
		CursorInfo.NameTooltip->On();


		const InventoryInfo& ItemInfo = Data->ReturnInventoryInfo(_X, _Y);
		std::string KRItemName = ReturnItemKRName(ItemInfo.SourceName);

		CursorInfo.ItemFont->Transform.SetLocalPosition(float4(IndexPosition.X, IndexPosition.Y + NameTagPosition.Y + FontYCorrection, ItemFontDepth));
		CursorInfo.ItemFont->ChangeText(KRItemName);
		CursorInfo.ItemFont->On();
	}
	else
	{
		CursorInfo.NameTooltip->Off();
		CursorInfo.ItemFont->Off();
	}

	CurrentSlotX = _X;
	CurrentSlotY = _Y;
}

void UI_Inventory::ClearSlot(const unsigned int _X, const unsigned int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	Data->ClearData(_X, _Y);
}

void UI_Inventory::EraseSlotImg(unsigned int _X, unsigned int _Y)
{
	const InventorySlotInfo& SlotData = InventorySlotArray[_Y][_X];

	if (nullptr == SlotData.Slot || nullptr == SlotData.ItemCount)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	SlotData.Slot->SetSprite("Inventory_None.png");
	SlotData.ItemCount->Off();
	CursorThis(_X, _Y);
}

void UI_Inventory::ClearAllSlotImg()
{
	for (unsigned int y = 0; y < UnlockSlotY; y++)
	{
		for (unsigned int x = 0; x < Max_XSlot; x++)
		{
			EraseSlotImg(x, y);
		}
	}
}

void UI_Inventory::OpenUpdate()
{
	ChangeDataParent();
	ClearAllSlotImg();
	RenewInventory();
	CurrentSlotX = 0;
	CurrentSlotY = 0;
	CursorThis(CurrentSlotX, CurrentSlotY);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// ������ �Է��� �����մϴ�.
void UI_Inventory::DectedCloseInventory()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('S', this))
		{
			Close();
			return;
		}
	}
}

bool UI_Inventory::UpdateCursor()
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		MoveCursor(-1, 0);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		MoveCursor(1, 0);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(0, -1);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(0, 1);
		return true;
	}

	return false;
}

void UI_Inventory::MoveCursor(const int _X, const int _Y)
{
	SFXFunction::PlaySFX("SFX_InventoryMove_01.wav");

	CurrentSlotX += _X;
	CurrentSlotY += _Y;

	bool isOverLeft = (-1 == CurrentSlotX);
	bool isOverRight = (Max_XSlot == CurrentSlotX);
	bool isOverUp = (-1 == CurrentSlotY);
	bool isOverDown = (UnlockSlotY == CurrentSlotY);


	if (isOverLeft)
	{
		CurrentSlotX = Max_XSlot - 1;
	}

	if (isOverRight)
	{
		CurrentSlotX = 0;
	}

	if (isOverUp)
	{
		CurrentSlotY = UnlockSlotY - 1;
	}

	if (isOverDown)
	{
		CurrentSlotY = 0;
	}

	CursorThis(CurrentSlotX, CurrentSlotY);
}

std::string UI_Inventory::ReturnItemKRName(std::string_view _ItemName)
{
	std::weak_ptr<ItemData> itemData = ItemData::Find(_ItemName);
	if (itemData.expired())
	{
		MsgBoxAssert("�������� �����Ϳ� �������� �ʽ��ϴ�.");
		return std::string();
	}

	return itemData.lock()->KoreanName;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


bool UI_Inventory::UpdateDispensationSelect()
{
	if (true == GameEngineInput::IsDown('Z', UI_Dispensation::MainDispensation))
	{
		// ��ĭ Ŭ���ϸ� ����
		if (false == Data->IsContain(CurrentSlotX, CurrentSlotY))
		{
			return false;
		}


		int SelectNumber = ReturnSelectNumber(CurrentSlotX, CurrentSlotY);
		bool isUnSelect = (-1 == SelectNumber);

		if (isUnSelect)
		{
			DispensationSelectThis();
		}
		else
		{
			DispensationUnSelectThis(SelectNumber);
		}

		return true;
	}

	return false;
}


int UI_Inventory::ReturnSelectNumber(int _XSlot, int _YSlot)
{
	InventoryInfo& InventoryData = Data->ReturnInventoryInfo(CurrentSlotX, CurrentSlotY);
	for (int i = 0; i < SelectItem.size(); i++)
	{
		if (SelectItem[i].ItemName == InventoryData.SourceName)
		{
			return i;
		}
	}

	return -1;
}

void UI_Inventory::DispensationSelectThis()
{
	int EmptySlotNumber = ReturnEmptySelectSlot();

	bool isEmptySlot = (-1 == EmptySlotNumber);
	if (isEmptySlot)
	{
		return;
	}

	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	InventoryInfo& InventoryData = Data->ReturnInventoryInfo(CurrentSlotX, CurrentSlotY);
	std::weak_ptr<ItemData> Item = ItemData::Find(InventoryData.SourceName);
	if (true == Item.expired())
	{
		MsgBoxAssert("��ϵ��� ���� �������� �����Ϸ� �߽��ϴ�.");
		return;
	}

	if (EITEM_TYPE::Ingredient != Item.lock()->ItemType)
	{
		return;
	}
	
	bool isIteminSelectedSlot = (false == InventoryData.SourceName.empty());
	if (isIteminSelectedSlot)
	{
		if (nullptr == UI_Dispensation::MainDispensation)
		{
			MsgBoxAssert("���� ���� �������� �𸨴ϴ�.");
			return;
		}

		if (false == UI_Dispensation::MainDispensation->SelectThis(InventoryData.SourceName, InventoryData.ItemCount))
		{
			MsgBoxAssert("���� �������� ���� ������ ���µ� �߰��Ϸ��߽��ϴ�.");
			return;
		}


		SelectItem[EmptySlotNumber].ItemName = InventoryData.SourceName;
		SelectItem[EmptySlotNumber].SelectCount = CurrentSlotX * CurrentSlotY;

		float4 CursorPosition = CalculateIndexToPos(CurrentSlotX, CurrentSlotY);
		CursorPosition.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
		SelectItem[EmptySlotNumber].Cursor->Transform.SetLocalPosition(CursorPosition);
		SelectItem[EmptySlotNumber].Cursor->On();
	}
}

int UI_Inventory::ReturnEmptySelectSlot()
{
	for (int i = 0; i < SelectItem.size(); i++)
	{
		if (true == SelectItem[i].ItemName.empty())
		{
			return i;
		}
	}

	return -1;
}

void UI_Inventory::DispensationUnSelectThis(int _SlotNumber)
{
	if (nullptr == UI_Dispensation::MainDispensation)
	{
		MsgBoxAssert("���� ���� �������� �𸨴ϴ�.");
		return;
	}

	UI_Dispensation::MainDispensation->UnSelectThis(SelectItem[_SlotNumber].ItemName);

	SelectItem[_SlotNumber].ItemName.clear();
	SelectItem[_SlotNumber].Cursor->Off();
	SelectItem[_SlotNumber].SelectCount = -1;
}

void UI_Inventory::UnSelectAll()
{
	for (int i = 0; i < SelectItem.size(); i++)
	{
		if (false == SelectItem[i].ItemName.empty())
		{
			DispensationUnSelectThis(i);
		}
	}
}


void UI_Inventory::StateSetting()
{
	CreateStateParameter NormalPara;
	NormalPara.Start = std::bind(&UI_Inventory::StartInventory, this, std::placeholders::_1);
	NormalPara.Stay = std::bind(&UI_Inventory::UpdateInventory, this, std::placeholders::_1, std::placeholders::_2);
	NormalPara.End = std::bind(&UI_Inventory::EndInventory, this, std::placeholders::_1);
	InventoryState.CreateState(EINVENTORYMODE::Normal, NormalPara);

	CreateStateParameter DispensationPara;
	DispensationPara.Start = [&](GameEngineState* _Parent) {IsJustOpen = true, InventoryMode = EINVENTORYMODE::Dispensation; };
	DispensationPara.Stay = std::bind(&UI_Inventory::UpdateDispensation, this, std::placeholders::_1, std::placeholders::_2);
	InventoryState.CreateState(EINVENTORYMODE::Dispensation, DispensationPara);
}

void UI_Inventory::StartInventory(GameEngineState* _Parent)
{
	GameEngineInput::IsOnlyInputObject(this);
	InventoryMode = EINVENTORYMODE::None;
	InventoryGuide.On();
}

void UI_Inventory::UpdateInventory(float _Delta, GameEngineState* _Parent)
{
	UI_ToggleActor::Update(_Delta);

	DectedCloseInventory();
	UpdateCursor();

	OpenCheck = false;
}

void UI_Inventory::EndInventory(GameEngineState* _Parent)
{
	GameEngineInput::IsObjectAllInputOn();
	InventoryGuide.Off();
}


void UI_Inventory::UpdateDispensation(float _Delta, GameEngineState* _Parent)
{
	if (true == IsJustOpen)
	{
		IsJustOpen = false;
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT, UI_Dispensation::MainDispensation))
	{
		MoveCursor(-1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, UI_Dispensation::MainDispensation))
	{
		MoveCursor(1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_UP, UI_Dispensation::MainDispensation))
	{
		MoveCursor(0, -1);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, UI_Dispensation::MainDispensation))
	{
		MoveCursor(0, 1);
		return;
	}


	if (true == UpdateDispensationSelect())
	{
		return;
	}
}
