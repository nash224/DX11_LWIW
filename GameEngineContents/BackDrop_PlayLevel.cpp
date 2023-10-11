#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"


#include "Prop.h"
#include "StaticEntity.h"
#include "PortalObject.h"

#include "LootedItem.h"



BackDrop_PlayLevel* BackDrop_PlayLevel::MainBackDrop = nullptr;
BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}


void BackDrop_PlayLevel::Start()
{
	BackDrop::Start();
}

void BackDrop_PlayLevel::Update(float _Delta)
{
	BackDrop::Update(_Delta);
}

void BackDrop_PlayLevel::Release()
{
	BackDrop::Release();

	MainBackDrop = nullptr;
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);

	MainBackDrop = this;
}

void BackDrop_PlayLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BackDrop_PlayLevel::Init()
{
	MainBackDrop = this;
}



// ����� ����� ���� �Ϲ� �ؽ�ó�� �ȼ� �浹 �ؽ�ó�� ��ȯ�����ݴϴ�.
void BackDrop_PlayLevel::EnableDebugMode(bool _Value)
{
	for (size_t i = 0; i < vecProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}


	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
			return;
		}

		Object->EnableDebugMode(_Value);
	}

	EnableBackDropElemnetDebugMode(_Value);
}



// Ư�� ��ġ�� �ȼ������Ͱ� �ִ��� ��ȯ���ݴϴ�.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("�������� ���� ���͸� �����Ϸ��� �߽��ϴ�.");
			return false;
		}

		if (false == Object->PixelRendererCheck)
		{
			continue;
		}

		if (_CheckColor == Object->GetColor(_Position))
		{
			return true;
		}
	}

	return false;
}

// ���̹��� ���
float BackDrop_PlayLevel::ZSort(const float _PositionY) const
{
	float4 BackGroundScale = GetBackGroundScale();
	if (float4::ZERO == BackGroundScale)
	{
		BackGroundScale = GlobalValue::GetWindowScale();
	}

	float Depth = (BackGroundScale.Y + _PositionY) / BackGroundScale.Y;
	return Depth;
}


void BackDrop_PlayLevel::CreateItem(std::string_view _ItemName, const float4& _Position, const int _Stack /*= 1*/)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<LootedItem> Item = CurLevel->CreateActor<LootedItem>(EUPDATEORDER::Objects);
	if (nullptr == Item)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	Item->Init(_ItemName);
	Item->SetStack(_Stack);
	Item->Transform.SetLocalPosition(_Position);
	Item->BackManager = this;
	LootedItemList.push_back(Item);
}

// ������ ����
std::list<std::shared_ptr<class LootedItem>>& BackDrop_PlayLevel::GetLootedItemList() 
{
	return LootedItemList;
}


void BackDrop_PlayLevel::ActorRelease()
{
	BackDrop::ActorRelease();

	for (size_t i = 0; i < vecPixelProps.size(); i++)
	{
		std::shared_ptr<Prop> Object = vecPixelProps[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
			return;
		}

		Object->Death();
	}

	vecPixelProps.clear();


	for (size_t i = 0; i < vecStaticEntity.size(); i++)
	{
		std::shared_ptr<StaticEntity> Object = vecStaticEntity[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
			return;
		}

		Object->Death();
	}

	vecStaticEntity.clear();


	// ��Ż �����ϰ�
	for (size_t i = 0; i < vecPortalObject.size(); i++)
	{
		std::shared_ptr<PortalObject> Object = vecPortalObject[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("���߿� ������ ��ü�� �����մϴ�.");
			return;
		}

		Object->ActorRelease();
	}

	vecPortalObject.clear();
}