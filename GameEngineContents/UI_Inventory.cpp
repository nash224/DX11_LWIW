#include "PreCompile.h"
#include "UI_Inventory.h"


#include "UI_DropManager.h"

// ������ �迭�� 1���� �迭�� �����մϴ�.
void Inventory::Init()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("�θ� �������� �ʾҽ��ϴ�.");
		return;
	}

	size_t Amount = InventoryParent->MaxSlotX * InventoryParent->MaxSlotY;

	InventoryData.resize(Amount);
}


// �������� �����Ϳ� �ֽ��ϴ�. 
// �κ��丮�� ������ �̸��� �������� ������ �������� ���� ���ϰ�, �������� ������ �� ���Կ� �ֽ��ϴ�.
void Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	size_t LockNumber = InventoryParent->MaxSlotX * InventoryParent->UnlockSlotY;

	int Value = IsContain(_ItemName);
	// �����Ϳ� ������
	if (-1 == Value)
	{
		// ���ڸ��� ã�Ƽ�
		for (size_t i = 0; i < LockNumber; i++)
		{
			// �ֽ��ϴ�.
			if ("" == InventoryData[i].SourceName)
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = static_cast<int>(i);
				break;
			}

			// �κ��丮�� �� á�ٴ� �ǹ̷� PopUp�� ��û�մϴ�.
			if (i == LockNumber - 1)
			{
				// PopUp
				return;
			}
		}
	}
	else
	{
		// ������
		InventoryData[Value].ItemCount += _Count;
	}

	InventoryParent->DisplayItem(static_cast<size_t>(Value), _ItemName);
}


// �����Ϳ� ������ �̸��� ���� �������� �ִ��� �˻��մϴ�.
int Inventory::IsContain(std::string_view _ItemName)
{
	std::string ItemName = _ItemName.data();
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		if (ItemName == InventoryData[y].SourceName)
		{
			return InventoryData[y].ItemCount;
		}
	}

	return 0;
}

int Inventory::IsContain(unsigned int _X, unsigned int _Y)
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("�κ��丮 �θ� �������� �ʾҽ��ϴ�.");
		return 0;
	}

	int MaxSlot = InventoryParent->MaxSlotX;
	unsigned int Value  = _Y * MaxSlot + _X;
	if ("" != InventoryData[Value].SourceName)
	{
		return InventoryData[Value].ItemCount;
	}

	return 0;
}



void Inventory::ClearData(const unsigned int _X, const unsigned int _Y)
{
	if (0 == IsContain(_X, _Y))
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

	int MaxSlot = InventoryParent->MaxSlotX;

	int Value = _Y * MaxSlot + _X;

	InventoryData[Value].SourceName = "";
	InventoryData[Value].ItemCount = 0;

	InventoryParent->EraseSlotImg(_X, _Y);
}

// �κ��丮�� �����մϴ�.
void Inventory::RenewInventory()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("�θ� �������� �ʰ� �̹����� ��� �� �����ϴ�.");
		return;
	}

	for (size_t i = 0; i < InventoryData.size(); i++)
	{
		std::string_view FileName = InventoryData[i].SourceName;
		if ("" != FileName)
		{
			InventoryParent->DisplayItem(i, FileName);
		}
	}
}



std::shared_ptr<Inventory> UI_Inventory::Data = nullptr;
UI_Inventory* UI_Inventory::MainInventory = nullptr;
unsigned int UI_Inventory::UnlockSlotY = 0;
UI_Inventory::UI_Inventory() 
{
}

UI_Inventory::~UI_Inventory() 
{
}


void UI_Inventory::Start()
{
	UI_ToggleActor::Start();
}

void UI_Inventory::Update(float _Delta)
{
	if (this != MainInventory)
	{
		OnLevelStart();
	}

	UI_ToggleActor::Update(_Delta);

	UpdateInventory(_Delta);
}

void UI_Inventory::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Inventory::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// �κ��丮 �迭�� ������ �迭�� �����մϴ�.
// ��, ������ �迭�� �ѹ��� �����˴ϴ�.
void UI_Inventory::Init()
{
	if (nullptr == Data)
	{
		CreateData();

		UnlockSlotY = 2;
	}


	// ���� �迭 �����
	CreateBase();
	CreateSlotArray();
	CreateCursor();

	// ������ ȹ�� �˸�â �Ŵ����Դϴ�.
	CreateNoticeDropManager();

	LockSlot(UnlockSlotY);
	Transform.AddLocalPosition({ -288.0f , 28.0f });

	// �θ� ���� ��, �׸��ϴ�.
	OnLevelStart();
}

// Base Create
void UI_Inventory::CreateBase()
{
	m_InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Base);
	if (nullptr == m_InventoryBase)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_InventoryBase->SetSprite("Inventory_Base.png");
	float4 BasePosition = { 0.0f , 0.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base) };
	m_InventoryBase->Transform.AddLocalPosition(BasePosition);
}

// ���� 2���� �迭�� �����մϴ�.
void UI_Inventory::CreateSlotArray()
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Inventory_Empty_Slot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_GridScale = Texture->GetScale();

	InventorySlotArray.resize(MaxSlotY);
	for (size_t y = 0; y < InventorySlotArray.size(); y++)
	{
		InventorySlotArray[y].resize(MaxSlotX);
		for (size_t x = 0; x < MaxSlotX; x++)
		{
			float4 Pos = CalculateIndexToPos(x, y);

			std::shared_ptr<GameEngineUIRenderer> Empty = CreateComponent<GameEngineUIRenderer>();
			Empty->SetSprite("Inventory_Empty_Slot.png");
			Pos.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment);
			Empty->Transform.SetLocalPosition(Pos);


			InventorySlotArray[y][x].SlotEmpty = Empty;

			std::shared_ptr<GameEngineUIRenderer> Slot = CreateComponent<GameEngineUIRenderer>();
			Pos.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Icon);
			Slot->Transform.SetLocalPosition(Pos);
			Slot->Off();

			InventorySlotArray[y][x].Slot = Slot;
		}
	}
}

void UI_Inventory::CreateCursor()
{
	if (nullptr == GameEngineSprite::Find("Inventory_Cursor.png"))
	{
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
	}

	std::shared_ptr<GameEngineUIRenderer> CurSor = CreateComponent<GameEngineUIRenderer>();
	CurSor->CreateAnimation("Cursor", "Inventory_Cursor.png", CursorInter);
	CurSor->ChangeAnimation("Cursor");
	CurSor->AutoSpriteSizeOn();
	m_CursorComposition.Cursor = CurSor;

	std::shared_ptr<GameEngineUIRenderer> CurSorOutLine = CreateComponent<GameEngineUIRenderer>();
	CurSorOutLine->SetSprite("Inventory_CursorOutline.png");
	m_CursorComposition.CursorOutline = CurSorOutLine;

	std::shared_ptr<GameEngineUIRenderer> NameTooltip = CreateComponent<GameEngineUIRenderer>();
	NameTooltip->SetSprite("Inventory_NameTooltip.png");
	NameTooltip->Off();
	m_CursorComposition.NameTooltip = NameTooltip;
	

	SelectSlot(0, 0);
}


void UI_Inventory::CreateNoticeDropManager()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_DropManager = CurLevel->CreateActor<UI_DropManager>(EUPDATEORDER::UIMagnaer);
	if (nullptr == m_DropManager)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_DropManager->Init();
}

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


	Data = std::make_shared<Inventory>();
	if (nullptr == Data)
	{
		MsgBoxAssert("�����͸� �������� ���߽��ϴ�.");
		return;
	}

	Data->InventoryParent = this;

	Data->Init();
}

// UnlockSlot�� �־��ָ� ������� ���ϴ� ���Կ� �����ġ �̹����� �����˴ϴ�.
void UI_Inventory::LockSlot(const unsigned int _Y)
{
	for (size_t y = _Y; y < InventorySlotArray.size(); y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("�������� �ʴ� ������ �����Ϸ��� �߽��ϴ�.");
				return;
			}

			Slot->SetSprite("Inventory_SlotLock.png");
			Slot->On();
		}
	}
}



// �������� �־�޶�� UI�� ���� Data�� ��û�մϴ�.
void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count/* = 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�������� �ʴ� �����Ϳ� �����Ϸ� �߽��ϴ�.");
		return;
	}


	std::string ItemName = _ItemName.data();
	ItemName += ".png";
	Data->PushItem(ItemName, _Count);


	// �˸� �ý����̱� ������ ��Ʈ���� �ʽ��ϴ�.
	if (nullptr != MainInventory->m_DropManager)
	{
		MainInventory->m_DropManager->NoticeItemDrop(_ItemName);
	}
}

// ���� �� �������
void UI_Inventory::UnlockSlot(const unsigned int _Count /*= 1*/)
{
	unsigned int PrevUnlockSlotY = UnlockSlotY;

	UnlockSlotY += _Count;

	if (UnlockSlotY > MaxSlotY)
	{
		UnlockSlotY = MaxSlotY;
	}

	if (PrevUnlockSlotY == UnlockSlotY)
	{
		return;
	}

	for (size_t y = PrevUnlockSlotY; y < UnlockSlotY; y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("�������� �ʴ� ���Կ� �����Ϸ� �߽��ϴ�.");
				return;
			}

			Slot->Off();
		}
	}
}


void UI_Inventory::UsingOtherComponent(bool _Value)
{
	IsOtherComponent = _Value;
}



// ���� �θ�� �����صθ� ���������� ������ �ɼ��������� ������ �ٲ� �θ� �ٲߴϴ�. 
void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʴµ� �������� �θ� �ٲٷ��� �߽��ϴ�.");
		return;
	}

	Data->InventoryParent = this;
}

// �������� ���ϴ�.
void UI_Inventory::DisplayItem(const size_t _SlotNumber, std::string_view _FileName)
{
	size_t Number = _SlotNumber;
	size_t SlotX = Number % MaxSlotX;
	size_t SlotY = Number / MaxSlotX;

	std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[SlotY][SlotX].Slot;
	if (nullptr == Slot)
	{
		MsgBoxAssert("�������� �ʾҰų� �������� �ʴ� �����Դϴ�.");
		return;
	}

	Slot->SetSprite(_FileName);
	Slot->On();
}

// �κ��丮�� �����϶�� ��û�޽��ϴ�.
void UI_Inventory::RenewInventory()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�������� �ʴ� �����Ϳ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	Data->RenewInventory();
}


/////////////////////////////////////////////////////////////////////////////////////

// �ڽĿ��� ���ְ� ���� �ൿ�� �����մϴ�.
void UI_Inventory::OpenChild()
{
	SelectSlot(0, 0);
}

void UI_Inventory::CloseChild()
{
	
}


// ��ǥ�� ��ġ�� ������ݴϴ�.
float4 UI_Inventory::CalculateIndexToPos(const size_t _x, const size_t _y)
{
	if (false == IsFirstPosCalculated)
	{
		float4 HGridScale = m_GridScale.Half();
		FirstGridPosition.X = -((CONST_GridSpacing / 2.0f) + HGridScale.X) * ((static_cast<float>(MaxSlotX / 2) - 0.5f) * 2.0f);
		FirstGridPosition.Y = ((CONST_GridSpacing / 2.0f) + HGridScale.Y) * ((static_cast<float>(MaxSlotY / 2) - 0.5f) * 2.0f);

		IsFirstPosCalculated = true;
	}

	float4 TargetDistance = { static_cast<float>(_x) * (CONST_GridSpacing + m_GridScale.X) , -static_cast<float>(_y) * (CONST_GridSpacing + m_GridScale.Y) };
	float4 ReturnValue = FirstGridPosition + TargetDistance;
	return ReturnValue;
}


void UI_Inventory::SelectSlot(const unsigned int _X, const unsigned int _Y)
{
	if (nullptr == m_CursorComposition.Cursor)
	{
		MsgBoxAssert("Ŀ���� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	float4 CursorPosition = CalculateIndexToPos(_X, _Y);
	CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor) };
	

	m_CursorComposition.Cursor->Transform.SetLocalPosition(CursorPosition);
	

	if (nullptr == m_CursorComposition.CursorOutline)
	{
		MsgBoxAssert("Ŀ���� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::CursorOutLine) };
	m_CursorComposition.CursorOutline->Transform.SetLocalPosition(CalculateIndexToPos(_X, _Y));

	if (nullptr == m_CursorComposition.NameTooltip)
	{
		MsgBoxAssert("Ŀ���� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
		return;
	}
	 
	// �����Ͱ� ������
	if (0 != Data->IsContain(_X, _Y))
	{
		CursorPosition = CalculateIndexToPos(_X, _Y) + NameTagPositionBaseOnSlotCenter;
		CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor) };
		m_CursorComposition.NameTooltip->Transform.SetLocalPosition(CursorPosition);
		m_CursorComposition.NameTooltip->On();
	}
	else
	{
		m_CursorComposition.NameTooltip->Off();
	}


	m_CurrentSlotX = _X;
	m_CurrentSlotY = _Y;
}

void UI_Inventory::ClearSlot(const unsigned int _X, const unsigned int _Y)
{
	if (this != Data->InventoryParent)
	{
		MsgBoxAssert("������ �θ� �ƴմϴ�. Ȯ���ؼ���");
		return;
	}

	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	Data->ClearData(_X, _Y);
}

void UI_Inventory::EraseSlotImg(const int _X, const int _Y)
{
	if (nullptr == InventorySlotArray[_Y][_X].Slot)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	InventorySlotArray[_Y][_X].Slot->SetSprite("Inventory_None.png");
	SelectSlot(_X, _Y);
}

void UI_Inventory::ClearAllSlotImg()
{
	for (size_t y = 0; y < UnlockSlotY; y++)
	{
		for (size_t x = 0; x < MaxSlotX; x++)
		{
			EraseSlotImg(static_cast<int>(x), static_cast<int>(y));
		}
	}
}

void UI_Inventory::OnLevelStart()
{
	// ������ �ٲ𶧸��� �������ݴϴ�.
	ChangeDataParent();
	ClearAllSlotImg();
	RenewInventory();
	MainInventory = this;
	m_CurrentSlotX = 0;
	m_CurrentSlotY = 0;
	SelectSlot(m_CurrentSlotX, m_CurrentSlotY);

	Close();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::UpdateInventory(float _Delta)
{
	DectedCloseInventory();
	UpdateCursor();

	// �ӽ��ڵ�
	if (true == GameEngineInput::IsPress(VK_CONTROL, this))
	{
		if (true == GameEngineInput::IsDown('4', this))
		{
			PushItem("SilverStarFlower_Collect.png");
			PushItem("MapleHerb_Collect.png");
			PushItem("UncurseCandy.png");
			PushItem("PumpkinTerrier_Powder.png");
			PushItem("MapleHerb_Water.png");
		}
		if (true == GameEngineInput::IsDown('5', this))
		{
			PushItem("Mongsiri_Collect.png");
		}
		if (true == GameEngineInput::IsDown('6', this))
		{
			PushItem("Mongsiri_EncyclopediaIcon.png");
		}
		if (true == GameEngineInput::IsDown('7', this))
		{
			PushItem("MoonButterfly_Water.png");
			PushItem("NutritionPotion_RecipePotionIcon.png");
		}
		if (true == GameEngineInput::IsDown('8', this))
		{
			PushItem("WitchFlower_Water.png");
			PushItem("WitchFlower_Collect.png");
			PushItem("SilverStarFlower_Collect.png");
		}
		if (true == GameEngineInput::IsDown('9', this))
		{
			UnlockSlot();
		}
		if (true == GameEngineInput::IsDown('3', this))
		{
			ClearSlot(m_CurrentSlotX, m_CurrentSlotY);
		}
	}

	OpenCheck = false;
}

void UI_Inventory::DectedCloseInventory()
{
	if (false == OpenCheck && false == IsOtherComponent)
	{
		if (true == GameEngineInput::IsDown('S', this))
		{
			Close();
			return;
		}
	}
}

void UI_Inventory::UpdateCursor()
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		MoveCursor(-1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		MoveCursor(1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(0, -1);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(0, 1);
		return;
	}
}

void UI_Inventory::MoveCursor(const int _X, const int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	m_CurrentSlotX += _X;
	m_CurrentSlotY += _Y;

	if (-1 == m_CurrentSlotX)
	{
		m_CurrentSlotX = MaxSlotX - 1;
	}
	if (MaxSlotX == m_CurrentSlotX)
	{
		m_CurrentSlotX = 0;
	}

	if (-1 == m_CurrentSlotY)
	{
		m_CurrentSlotY = UnlockSlotY - 1;
	}
	if (UnlockSlotY == m_CurrentSlotY)
	{
		m_CurrentSlotY = 0;
	}

	SelectSlot(m_CurrentSlotX, m_CurrentSlotY);
}