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
		MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
		return;
	}

	InteractiveActor::InteractiveCol->Off();
}


void LootedItem::Init(std::string_view _ItemName)
{
	CreateItemRenderer(_ItemName);
	InteractiveRange = ItemInterativeRange;
}




// ������ ������ ����
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
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
				MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
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