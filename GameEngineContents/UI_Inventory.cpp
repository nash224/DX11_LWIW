#include "PreCompile.h"
#include "UI_Inventory.h"


// 데이터 배열은 1차원 배열로 설정합니다.
void Inventory::Init()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("부모가 지정되지 않았습니다.");
		return;
	}

	size_t Amount = InventoryParent->MaxSlotX * InventoryParent->MaxSlotY;

	InventoryData.resize(Amount);
}


// 아이템을 데이터에 넣습니다. 
// 인벤토리에 동일한 이름의 아이템이 있으면 아이템의 수를 더하고, 아이템이 없으면 빈 슬롯에 넣습니다.
void Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	size_t LockNumber = InventoryParent->MaxSlotX * InventoryParent->UnlockSlotY;

	int Value = IsContain(_ItemName);
	// 데이터에 없으면
	if (-1 == Value)
	{
		// 빈자리를 찾아서
		for (size_t i = 0; i < LockNumber; i++)
		{
			// 넣습니다.
			if ("" == InventoryData[i].SourceName)
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = static_cast<int>(i);
				break;
			}

			// 인벤토리가 다 찼다는 의미로 PopUp을 요청합니다.
			if (i == LockNumber - 1)
			{
				// PopUp
				return;
			}
		}
	}
	else
	{
		// 있으면
		InventoryData[Value].ItemCount += _Count;
	}

	InventoryParent->DisplayItem(static_cast<size_t>(Value), _ItemName);
}


// 데이터에 동일한 이름을 가진 아이템이 있는지 검사합니다.
int Inventory::IsContain(std::string_view _ItemName)
{
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		if (_ItemName.data() == InventoryData[y].SourceName)
		{
			return static_cast<int>(y);
		}
	}

	return -1;
}

int Inventory::IsContain(unsigned int _X, unsigned int _Y)
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("인벤토리 부모를 정해주지 않았습니다.");
		return -1;
	}

	int MaxSlot = InventoryParent->MaxSlotX;
	unsigned int Value  = _Y * MaxSlot + _X;
	if ("" != InventoryData[Value].SourceName)
	{
		return 1;
	}

	return -1;
}



void Inventory::ClearData(const unsigned int _X, const unsigned int _Y)
{
	if (-1 == IsContain(_X, _Y))
	{
		MsgBoxAssert("존재하지 않는 슬롯을 지울려고 했습니다.");
		return;
	}

	if (true == InventoryData.empty())
	{
		MsgBoxAssert("데이터에 아무것도 들어있지 않습니다.");
		return;
	}

	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("부모를 모릅니다. 설정하세요");
		return;
	}

	int MaxSlot = InventoryParent->MaxSlotX;

	int Value = _Y * MaxSlot + _X;

	InventoryData[Value].SourceName = "";
	InventoryData[Value].ItemCount = 0;

	InventoryParent->EraseSlotImg(_X, _Y);
}

// 인벤토리를 갱신합니다.
void Inventory::RenewInventory()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("부모를 설정하지 않고 이미지를 띄울 수 없습니다.");
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
	UI_ToggleActor::Update(_Delta);

	UpdateInventory(_Delta);
}

void UI_Inventory::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);

	// 레벨이 바뀔때마다 갱신해줍니다.
	ChangeDataParent();
	RenewInventory();
	MainInventory = this;
	m_CurrentSlotX = 0;
	m_CurrentSlotY = 0;
}

void UI_Inventory::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 인벤토리 배열과 데이터 배열을 생성합니다.
// 단, 데이터 배열은 한번만 생성됩니다.
void UI_Inventory::Init()
{
	if (nullptr == Data)
	{
		CreateData();

		UnlockSlotY = 2;
	}


	// 렌더 배열 만들고
	CreateBase();
	CreateSlotArray();
	CreateCursor();
	LockSlot(UnlockSlotY);
	Transform.AddLocalPosition({ -288.0f , 28.0f });

	// 부모 설정 후, 그립니다.
	ChangeDataParent();
	RenewInventory();
	MainInventory = this;



	Off();
}

// Base Create
void UI_Inventory::CreateBase()
{
	m_InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Base);
	if (nullptr == m_InventoryBase)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_InventoryBase->SetSprite("Inventory_Base.png");
}

// 렌더 2차원 배열을 생성합니다.
void UI_Inventory::CreateSlotArray()
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Inventory_Empty_Slot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
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

			std::shared_ptr<GameEngineUIRenderer> Empty = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
			Empty->SetSprite("Inventory_Empty_Slot.png");
			Empty->Transform.SetLocalPosition(Pos);

			InventorySlotArray[y][x].SlotEmpty = Empty;

			std::shared_ptr<GameEngineUIRenderer> Slot = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Icon);
			Slot->Transform.SetLocalPosition(Pos);
			Slot->Off();

			InventorySlotArray[y][x].Slot = Slot;
		}
	}
}

void UI_Inventory::CreateCursor()
{
	std::shared_ptr<GameEngineUIRenderer> CurSor = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Cursor);
	CurSor->CreateAnimation("Cursor", "Inventory_Cursor.png", CursorInter);
	CurSor->ChangeAnimation("Cursor");
	CurSor->AutoSpriteSizeOn();
	m_CursorComposition.Cursor = CurSor;

	std::shared_ptr<GameEngineUIRenderer> CurSorOutLine = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::CursorOutLine);
	CurSorOutLine->SetSprite("Inventory_CursorOutline.png");
	m_CursorComposition.CursorOutline = CurSorOutLine;

	std::shared_ptr<GameEngineUIRenderer> NameTooltip = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Cursor);
	NameTooltip->SetSprite("Inventory_NameTooltip.png");
	NameTooltip->Off();
	m_CursorComposition.NameTooltip = NameTooltip;
	

	SelectSlot(0, 0);
}

// 전역으로 한번만 실행됩니다.
void UI_Inventory::CreateData()
{
#ifdef _DEBUG
	static bool InitCheck = false;
	if (true == InitCheck)
	{
		MsgBoxAssert("데이터를 2번 생성하려 했습니다.");
		return;
	}

	InitCheck = true;

#endif // DEBUG


	Data = std::make_shared<Inventory>();
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터를 생성하지 못했습니다.");
		return;
	}

	Data->InventoryParent = this;

	Data->Init();
}

// UnlockSlot을 넣어주면 사용하지 못하는 슬롯에 잠금장치 이미지가 생성됩니다.
void UI_Inventory::LockSlot(const unsigned int _Y)
{
	for (size_t y = _Y; y < InventorySlotArray.size(); y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("존재하지 않는 슬롯을 참조하려고 했습니다.");
				return;
			}

			Slot->SetSprite("Inventory_SlotLock.png");
			Slot->On();
		}
	}
}



// 아이템을 넣어달라고 UI를 통해 Data에 요청합니다.
void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count = 1)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터에 접근하려 했습니다.");
		return;
	}

	Data->PushItem(_ItemName, _Count);
}

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
				MsgBoxAssert("존재하지 않는 슬롯에 접근하려 했습니다.");
				return;
			}

			Slot->Off();
		}
	}
}



// 같은 부모로 설정해두면 이전레벨에 렌더링 될수있음으로 레벨이 바뀔때 부모를 바꿉니다. 
void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않는데 데이터의 부모를 바꾸려고 했습니다.");
		return;
	}

	Data->InventoryParent = this;
}

// 아이템을 띄웁니다.
void UI_Inventory::DisplayItem(const size_t _SlotNumber, std::string_view _FileName)
{
	size_t Number = _SlotNumber;
	size_t SlotX = Number % MaxSlotX;
	size_t SlotY = Number / MaxSlotX;

	std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[SlotY][SlotX].Slot;
	if (nullptr == Slot)
	{
		MsgBoxAssert("생성되지 않았거나 존재하지 않는 슬롯입니다.");
		return;
	}

	Slot->SetSprite(_FileName);
	Slot->On();
}

// 인벤토리를 갱신하라고 요청받습니다.
void UI_Inventory::RenewInventory()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터에 접근하려 했습니다.");
		return;
	}

	Data->RenewInventory();
}


/////////////////////////////////////////////////////////////////////////////////////

// 자식에서 해주고 싶은 행동을 수행합니다.
void UI_Inventory::OpenChild()
{

}

void UI_Inventory::CloseChild()
{
	
}


// 좌표의 위치를 계산해줍니다.
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
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	m_CursorComposition.Cursor->Transform.SetLocalPosition(CalculateIndexToPos(_X, _Y));
	

	if (nullptr == m_CursorComposition.CursorOutline)
	{
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	m_CursorComposition.CursorOutline->Transform.SetLocalPosition(CalculateIndexToPos(_X, _Y));

	if (nullptr == m_CursorComposition.NameTooltip)
	{
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	if (-1 != Data->IsContain(_X, _Y))
	{
		m_CursorComposition.NameTooltip->Transform.SetLocalPosition(CalculateIndexToPos(_X, _Y) + NameTagPositionBaseOnSlotCenter);
		m_CursorComposition.NameTooltip->On();
	}
	else
	{
		m_CursorComposition.NameTooltip->Off();
	}
}

void UI_Inventory::ClearSlot(const unsigned int _X, const unsigned int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	Data->ClearData(_X, _Y);
}

void UI_Inventory::EraseSlotImg(const int _X, const int _Y)
{
	if (nullptr == InventorySlotArray[_Y][_X].Slot)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	InventorySlotArray[_Y][_X].Slot->SetSprite("Inventory_None.png");
	SelectSlot(_X, _Y);
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::UpdateInventory(float _Delta)
{
	DectedCloseInventory();
	UpdateCursor();

	// 임시코드
	if (true == GameEngineInput::IsPress(VK_CONTROL))
	{
		if (true == GameEngineInput::IsDown('4'))
		{
			PushItem("SilverStarFlower_Collect.png");
			PushItem("MapleHerb_Collect.png");
			PushItem("UncurseCandy.png");
			PushItem("PumpkinTerrier_Powder.png");
			PushItem("MapleHerb_Water.png");
		}
		if (true == GameEngineInput::IsDown('5'))
		{
			PushItem("Mongsiri_Collect.png");
		}
		if (true == GameEngineInput::IsDown('6'))
		{
			PushItem("Mongsiri_EncyclopediaIcon.png");
		}
		if (true == GameEngineInput::IsDown('7'))
		{
			PushItem("MoonButterfly_Water.png");
			PushItem("NutritionPotion_RecipePotionIcon.png");
		}
		if (true == GameEngineInput::IsDown('8'))
		{
			PushItem("WitchFlower_Water.png");
			PushItem("WitchFlower_Collect.png");
			PushItem("SilverStarFlower_Collect.png");
		}
		if (true == GameEngineInput::IsDown('9'))
		{
			UnlockSlot();
		}
		if (true == GameEngineInput::IsDown('3'))
		{
			ClearSlot(m_CurrentSlotX, m_CurrentSlotY);
		}
	}

	OpenCheck = false;
}

void UI_Inventory::DectedCloseInventory()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('S'))
		{
			Close();
			return;
		}
	}
}

void UI_Inventory::UpdateCursor()
{
	if (true == GameEngineInput::IsDown(VK_LEFT))
	{
		MoveCursor(-1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT))
	{
		MoveCursor(1, 0);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		MoveCursor(0, -1);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		MoveCursor(0, 1);
		return;
	}
}

void UI_Inventory::MoveCursor(const int _X, const int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
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