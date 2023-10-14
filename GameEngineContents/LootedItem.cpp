#include "PreCompile.h"
#include "LootedItem.h"

#include "UI_Inventory.h"
#include "BackDrop_PlayLevel.h"

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
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::Sit, ETOOLTYPE::Nothing);
	m_InteractiveRange = ItemInterativeRange;
}

void LootedItem::SetStack(const int _Value)
{
	m_Stack = _Value;
}

// 아이템 렌더러 생성
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_ItemRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_ItemRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_ItemRenderer->SetSprite(_ItemName);

	ItemName = _ItemName;
}

// 아이템 상호작용 충돌체 생성
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
	// 플레이어가 주으면
	if (true == IsEnalbeActive)
	{
		// 아이템 넣고
		UI_Inventory::PushItem(ItemName, m_Stack);

		// 리스트에서 제거하고
		std::list<std::shared_ptr<LootedItem>>& ItemList = BackManager->GetLootedItemList();
		ItemList.remove(GetDynamic_Cast_This<LootedItem>());

		// 삭제
		Death();
	}
}