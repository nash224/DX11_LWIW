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


// 특정 위치에 픽셀데이터가 있는지 반환해줍니다.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (size_t i = 0; i < PixelVec.size(); i++)
	{
		std::shared_ptr<NormalProp> Object = PixelVec[i];
		if (nullptr == Object)
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
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

// 깊이버퍼 계산
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

// 아이템 생성 : 
// 아이템 이름
// 위치
// 개수
// 떨어질 거리
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

