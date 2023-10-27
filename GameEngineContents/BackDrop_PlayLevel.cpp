#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"


#include "NormalProp.h"
#include "StaticEntity.h"

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
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelStart(_NextLevel);

	MainBackDrop = this;
}

void BackDrop_PlayLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	BackDrop::LevelEnd(_NextLevel);

	PixelVec.clear();
	PixelStaticEntityVec.clear();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// Ư�� ��ġ�� �ȼ������Ͱ� �ִ��� ��ȯ���ݴϴ�.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (size_t i = 0; i < PixelVec.size(); i++)
	{
		std::shared_ptr<NormalProp> Object = PixelVec[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("�������� ���� ���͸� �����Ϸ��� �߽��ϴ�.");
			return false;
		}

		if (false == Object->GetPixelCheck())
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

	float Depth = (BackGroundScale.Y + _PositionY);
	return Depth;
}

// ������ ���� : 
// ������ �̸�
// ��ġ
// ����
// ������ �Ÿ�
void BackDrop_PlayLevel::CreateItem(std::string_view _ItemName, const float4& _Position, const int _Stack /*= 1*/, const float _FallYPosition /*= 0.0f*/)
{
	std::shared_ptr<LootedItem> Item = GetLevel()->CreateActor<LootedItem>(EUPDATEORDER::Objects);

	Item->BackManager = this;

	float4 Position = _Position;
	Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::RootedItem);
	Item->Transform.SetLocalPosition(Position);

	Item->SetStack(_Stack);

	if (0.0f != _FallYPosition)
	{
		Item->SetFallingTargetPosition(_FallYPosition);
	}

	Item->Init(_ItemName);
}

