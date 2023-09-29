#include "PreCompile.h"
#include "UI_Inventory.h"

std::vector<std::vector<InventoryInfo>> UI_Inventory::InventoryData;
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
}

void UI_Inventory::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::Init()
{
	CreateBase();
	CreateSlotArray();
	Transform.AddLocalPosition({ -288.0f , 28.0f });

	Off();
}

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

void UI_Inventory::CreateSlotArray()
{
	if (true == InventoryData.empty())
	{
		InitData();
	}

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

// 전역으로 한번만 실행됩니다.
void UI_Inventory::InitData()
{
	InventoryData.resize(MaxSlotY);
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		InventoryData[y].resize(MaxSlotX);
		for (size_t x = 0; x < MaxSlotX; x++)
		{
			InventoryData[y][x].IsSlotEnabled = true;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////

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

	OpenCheck = false;
}