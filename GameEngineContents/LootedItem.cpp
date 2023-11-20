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

	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 80.0f, 80.0f }, 0.0f, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::Sit, ETOOLTYPE::Nothing);
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
	Stack = _Value;
}

void LootedItem::SetFallingTargetPosition(const float _YPosition)
{
	if (0.0f == _YPosition)
	{
		return;
	}

	IsFalling = true;
	FallingYDistance = _YPosition;


	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}

	InteractiveActor::InteractiveCol->Off();
}


void LootedItem::Init(std::string_view _ItemName)
{
	CreateItemRenderer(_ItemName);
	InteractiveRange = ItemInterativeRange;
}




// 아이템 렌더러 생성
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	std::string FileName = _ItemName.data();
	FileName += ".png";
	BodyRenderer->SetSprite(FileName);

	ItemName = _ItemName;
}


/////////////////////////////////////////////////////////////////////////////////////


void LootedItem::UpdateFallingItem(float _Delta)
{
	if (true == IsFalling)
	{
		float Speed = FallingSpeed * _Delta;
		FallingYDistance -= Speed;

		if (FallingYDistance < 0.0f)
		{
			Speed = FallingYDistance;
			FallingYDistance = 0.0f;

			if (nullptr == InteractiveActor::InteractiveCol)
			{
				MsgBoxAssert("충돌체가 존재하지 않습니다.");
				return;
			}

			InteractiveActor::InteractiveCol->On();

			IsFalling = false;
		}

		float4 AddPosition = { 0.0f, -Speed };

		Transform.AddLocalPosition(AddPosition);
	}
}


void LootedItem::UpdateItemInteraction()
{
	if (true == IsEnalbeActive)
	{
		UI_Inventory::PushItem(ItemName, Stack);

		Death();
	}
}