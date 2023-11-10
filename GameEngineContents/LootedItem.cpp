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
	UpdateFallingItem(_Delta);
	UpdateItemInteraction();
}

void LootedItem::Release()
{
	StaticEntity::Release();
}

void LootedItem::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}


// �� ��ü�� ���ﶧ GameEngineLevel�� GetObjectGroupConvert�� �׷��� �޾ƿͼ� ���� �� �ֽ��ϴ�.
// ���� �ٲ�� �� �Լ��� ȣ���Ͽ� ��� �÷��� ������ �������� ���� �����Դϴ�.
void LootedItem::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void LootedItem::SetStack(const int _Value)
{
	m_Stack = _Value;
}

void LootedItem::SetFallingTargetPosition(const float _YPosition)
{
	if (0.0f == _YPosition)
	{
		return;
	}

	IsFalling = true;
	m_FallingYPosition = _YPosition;
}


void LootedItem::Init(std::string_view _ItemName)
{
	CreateAndSetCollision(ECOLLISION::Entity, { 80.0f, 80.0f }, 0.0f, ColType::SPHERE2D);
	CreateItemRenderer(_ItemName);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::Sit, ETOOLTYPE::Nothing);
	m_InteractiveRange = ItemInterativeRange;
}




// ������ ������ ����
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	std::string ItemName = _ItemName.data();
	ItemName += ".png";
	m_Body->SetSprite(ItemName);

	m_ItemName = _ItemName;
}


/////////////////////////////////////////////////////////////////////////////////////


void LootedItem::UpdateFallingItem(float _Delta)
{
	// �������� ���� ��
	if (true == IsFalling)
	{
		// �ӷ��� �������¼ӵ�
		float Speed = FallingSpeed * _Delta;
		// �������� ���� �ݿ� ��
		m_FallingYPosition -= Speed;

		// �������� ���� 0�̸�
		if (m_FallingYPosition < 0.0f)
		{
			// ���� ������ŭ ����������.
			Speed = m_FallingYPosition;
			m_FallingYPosition = 0.0f;

			IsFalling = false;
		}

		float4 AddPosition = { 0.0f, -Speed };

		Transform.AddLocalPosition(AddPosition);
	}
}


void LootedItem::UpdateItemInteraction()
{
	// �÷��̾ ������
	if (true == IsEnalbeActive)
	{
		// ������ �ְ�
		UI_Inventory::PushItem(m_ItemName, m_Stack);

		// ����
		Death();
	}
}