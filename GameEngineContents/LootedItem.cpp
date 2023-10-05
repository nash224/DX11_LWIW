#include "PreCompile.h"
#include "LootedItem.h"

#include "UI_Inventory.h"

LootedItem::LootedItem() 
{
}

LootedItem::~LootedItem() 
{
}


void LootedItem::Start()
{
	StaticEntity::Start();
}

void LootedItem::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateItemInteraction();
}

void LootedItem::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void LootedItem::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void LootedItem::Init(std::string_view _ItemName)
{
	CreateItemRenderer(_ItemName);
	CreateItemCollision();
}

void LootedItem::SetStack(const int _Value)
{
	m_Stack = _Value;
}

void LootedItem::ActorRelease() 
{

}

void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_ItemRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_ItemRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	ItemName = _ItemName.data();
	std::string ItemSpriteName = _ItemName.data();
	ItemSpriteName += "_Collect.png";

	m_ItemRenderer->SetSprite(ItemSpriteName);
}

void LootedItem::CreateItemCollision()
{
	m_ItemCollision = CreateComponent<GameEngineCollision>(ERENDERORDER::Object);
	if (nullptr == m_ItemCollision)
	{
		MsgBoxAssert("�浹ü�� �������� ���߽��ϴ�.");
		return;
	}

	m_ItemCollision->SetCollisionType(ColType::SPHERE2D);
	m_ItemCollision->Transform.SetLocalScale(GlobalValue::GetItemScale());
}

void LootedItem::UpdateItemInteraction()
{
	if (true == IsEnalbeActive)
	{
		std::vector<std::shared_ptr<GameEngineCollision>> OtherCol;
		if (true == m_ItemCollision->Collision(ECOLLISION::Player))
		{
			if (m_Stack < 1)
			{
				MsgBoxAssert("������ ���� �������� �κ��丮�� ���� �� �����ϴ�.");
				return;
			}

			UI_Inventory::MainInventory->PushItem(ItemName, m_Stack);
			Death();
		}
	}
