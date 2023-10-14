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

// ������ ������ ����
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_ItemRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_ItemRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_ItemRenderer->SetSprite(_ItemName);

	ItemName = _ItemName;
}

// ������ ��ȣ�ۿ� �浹ü ����
void LootedItem::CreateItemCollision()
{
	m_ItemCollision = CreateComponent<GameEngineCollision>(ECOLLISION::Entity);
	if (nullptr == m_ItemCollision)
	{
		MsgBoxAssert("�浹ü�� �������� ���߽��ϴ�.");
		return;
	}

	m_ItemCollision->SetCollisionType(ColType::SPHERE2D);
	m_ItemCollision->Transform.SetLocalScale({ 80.0f, 80.0f });
}

void LootedItem::UpdateItemInteraction()
{
	// �÷��̾ ������
	if (true == IsEnalbeActive)
	{
		// ������ �ְ�
		UI_Inventory::PushItem(ItemName, m_Stack);

		// ����Ʈ���� �����ϰ�
		std::list<std::shared_ptr<LootedItem>>& ItemList = BackManager->GetLootedItemList();
		ItemList.remove(GetDynamic_Cast_This<LootedItem>());

		// ����
		Death();
	}
}