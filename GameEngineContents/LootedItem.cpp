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
	InteractiveActor::Start();

	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 120.0f, 80.0f }, 0.0f, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::Sit, ETOOLTYPE::Nothing);
}

void LootedItem::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
	UpdateFallingItem(_Delta);
	UpdateItemInteraction();
}

void LootedItem::Release()
{
	InteractiveActor::Release();
}


// �� ��ü�� ���ﶧ GameEngineLevel�� GetObjectGroupConvert�� �׷��� �޾ƿͼ� ���� �� �ֽ��ϴ�.
// ���� �ٲ�� ��� �����˴ϴ�.


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
	InteractiveRange = 20.0f;
}




// ������ ������ ����
void LootedItem::CreateItemRenderer(std::string_view _ItemName)
{
	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BodyRenderer->SetSprite(_ItemName.data() + std::string(".png"));

	ItemName = _ItemName;
}


void LootedItem::UpdateFallingItem(float _Delta)
{
	if (true == IsFalling)
	{
		float Speed = FallingSpeed * _Delta;
		FallingYDistance -= Speed;

		bool isFallDone = (FallingYDistance < 0.0f);
		if (isFallDone)
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

		Transform.AddLocalPosition(float4(0.0f, -Speed));
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