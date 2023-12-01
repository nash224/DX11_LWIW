#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"

#include "NormalProp.h"
#include "StaticEntity.h"

#include "LootedItem.h"


BackDrop_PlayLevel* BackDrop_PlayLevel::MainBackDrop = nullptr;
BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
	MainBackDrop = this;
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainBackDrop = this;
}

void BackDrop_PlayLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PixelVec.clear();
}


void BackDrop_PlayLevel::CreateItem(std::string_view _ItemName, const float4& _Position, const int _Stack /*= 1*/, const float _FallYPosition /*= 0.0f*/)
{
	std::shared_ptr<LootedItem> Item = GetLevel()->CreateActor<LootedItem>(EUPDATEORDER::Entity);
	const float Depth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::RootedItem);
	Item->Transform.SetLocalPosition(float4(_Position.X, _Position.Y, Depth));
	Item->BackManager = this;

	Item->SetStack(_Stack);

	if (0.0f != _FallYPosition)
	{
		Item->SetFallingTargetPosition(_FallYPosition);
	}

	Item->Init(_ItemName);
}


// 특정 위치에 픽셀데이터가 있는지 반환해줍니다.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (std::weak_ptr<NormalProp> Object : PixelVec)
	{
		if (true == Object.expired())
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Object.lock()->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Object.lock()->GetColor(_Position))
		{
			return true;
		}
	}

	for (std::weak_ptr<StaticEntity> Entity : PixelStaticEntityVec)
	{
		if (true == Entity.expired())
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return false;
		}

		if (false == Entity.lock()->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Entity.lock()->GetColor(_Position))
		{
			return true;
		}
	}

	return false;
}


void BackDrop_PlayLevel::CreateRenderActor(
	int _UpdateOrder,
	std::string_view _SpriteName,
	const float4& _Position,
	int _DepthType,
	bool _isFixDepth /*= true*/,
	float _DepthCorrection/*= 0.0f*/)
{
	float Depth = 0.0f;
	if (true == _isFixDepth)
	{
		Depth = DepthFunction::CalculateFixDepth(_DepthType);
	}
	else
	{
		Depth = DepthFunction::CalculateObjectDepth(BackScale.Y, _Position.Y + _DepthCorrection);
	}

	const float4 Position = float4(_Position.X, _Position.Y, Depth);

	std::shared_ptr<RendererActor> Object = GetLevel()->CreateActor<RendererActor>(_UpdateOrder);
	Object->Transform.SetLocalPosition(Position);
	Object->Init();
	Object->m_Renderer->SetSprite(_SpriteName);
}
