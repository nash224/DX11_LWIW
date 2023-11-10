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


// 이 객체를 지울때 GameEngineLevel의 GetObjectGroupConvert로 그룹을 받아와서 지울 수 있습니다.
// 날이 바뀌면 위 함수를 호출하여 모든 플레이 레벨의 아이템을 지울 예정입니다.
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




// 아이템 렌더러 생성
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
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
	// 떨어지는 중일 때
	if (true == IsFalling)
	{
		// 속력은 떨어지는속도
		float Speed = FallingSpeed * _Delta;
		// 떨어지는 값에 반영 후
		m_FallingYPosition -= Speed;

		// 떨어지는 값이 0이면
		if (m_FallingYPosition < 0.0f)
		{
			// 남은 지점만큼 떨어져야함.
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
	// 플레이어가 주으면
	if (true == IsEnalbeActive)
	{
		// 아이템 넣고
		UI_Inventory::PushItem(m_ItemName, m_Stack);

		// 삭제
		Death();
	}
}