#include "PreCompile.h"
#include "UI_Inventory.h"


void Inventory::Init()
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("�θ� �������� �ʾҽ��ϴ�.");
		return;
	}

	size_t Amount = Parent->MaxSlotX * Parent->MaxSlotY;

	InventoryData.resize(Amount);
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		InventoryData[y].IsSlotEnabled = true;
	}
}


// �������� �����Ϳ� �ֽ��ϴ�. 
// �κ��丮�� ������ �̸��� �������� ������ �������� ���� ���ϰ�, �������� ������ �� ���Կ� �ֽ��ϴ�.
void Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	size_t Value = IsContain(_ItemName);
	// ������
	if (-1 == Value)
	{
		// ���ڸ��� ã�Ƽ�
		for (size_t i = 0; i < InventoryData.size(); i++)
		{
			// �־�޶�
			if ("" == InventoryData[i].SourceName)
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = i;
				break;
			}
		}
	}
	else
	{
		// ������
		InventoryData[Value].ItemCount += _Count;
	}

	Parent->DisplayItem(Value, _ItemName);
}


// �����Ϳ� ������ �̸��� ���� �������� �ִ��� �˻��մϴ�.
size_t Inventory::IsContain(std::string_view _ItemName)
{
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		if (_ItemName.data() == InventoryData[y].SourceName)
		{
			return y;
		}
	}

	return -1;
}


void Inventory::RenewInventory()
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("�θ� �������� �ʰ� �̹����� ��� �� �����ϴ�.");
		return;
	}

	for (size_t i = 0; i < InventoryData.size(); i++)
	{
		std::string_view FileName = InventoryData[i].SourceName;
		if ("" != FileName)
		{
			Parent->DisplayItem(i, FileName);
		}
	}
}


std::shared_ptr<Inventory> UI_Inventory::Data = nullptr;
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

	ChangeDataParent();
	RenewInventory();
}

void UI_Inventory::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::Init()
{
	if (nullptr == Data)
	{
		CreateData();
	}


	// ���� �迭 �����
	CreateBase();
	CreateSlotArray();
	Transform.AddLocalPosition({ -288.0f , 28.0f });

	// �θ� ���� ��, �׷���
	ChangeDataParent();
	RenewInventory();


	Off();
}

void UI_Inventory::CreateBase()
{
	m_InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Base);
	if (nullptr == m_InventoryBase)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_InventoryBase->SetSprite("Inventory_Base.png");
}

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

	Data->Parent = this;

	Data->Init();
}


// �������� �־�޶�� UI�� ���� Data�� ��û�մϴ�.
void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count = 1)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�������� �ʴ� �����Ϳ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	Data->PushItem(_ItemName, _Count);
}


void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("�����Ͱ� �������� �ʴµ� �������� �θ� �ٲٷ��� �߽��ϴ�.");
		return;
	}

	Data->Parent = this;
}

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

void UI_Inventory::OpenChild()
{

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




/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::UpdateInventory(float _Delta)
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('S'))
		{
			Close();
			return;
		}
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

	OpenCheck = false;
}