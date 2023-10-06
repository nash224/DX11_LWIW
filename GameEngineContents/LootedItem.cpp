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

	m_CollectionMethod = ECOLLECTION_METHOD::Sit;
}

void LootedItem::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateItemInteraction();
}

void LootedItem::Release()
{
	StaticEntity::Release();

	m_ItemRenderer = nullptr;
	m_ItemCollision = nullptr;
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
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gathering);
	SetInteractionType(EINTERACTION_TYPE::Near);
	m_CollectionMethod = ECOLLECTION_METHOD::Sit;
	m_InteractiveRange = ItemInterativeRange;
}

void LootedItem::SetStack(const int _Value)
{
	m_Stack = _Value;
}

void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_ItemRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::RootedItem);
	if (nullptr == m_ItemRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_ItemRenderer->SetSprite(_ItemName);

	ItemName = _ItemName;
}

void LootedItem::CreateItemCollision()
{
	m_ItemCollision = CreateComponent<GameEngineCollision>(ECOLLISION::Entity);
	if (nullptr == m_ItemCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_ItemCollision->SetCollisionType(ColType::SPHERE2D);
	m_ItemCollision->Transform.SetLocalScale({ 80.0f, 80.0f });
}

void LootedItem::UpdateItemInteraction()
{
	if (true == IsEnalbeActive)
	{
		UI_Inventory::PushItem(ItemName, m_Stack);
		Death();
	}
}