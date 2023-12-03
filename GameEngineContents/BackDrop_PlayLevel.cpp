#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"

#include "NormalProp.h"
#include "StaticEntity.h"

#include "LootedItem.h"


BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}

void BackDrop_PlayLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
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


// Ư�� ��ġ�� �ȼ������Ͱ� �ִ��� ��ȯ���ݴϴ�.
bool BackDrop_PlayLevel::IsColorAtPosition(const float4& _Position, GameEngineColor _CheckColor)
{
	for (const std::shared_ptr<NormalProp>& Object : PixelVec)
	{
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

	for (const std::shared_ptr<StaticEntity>& Entity : PixelStaticEntityVec)
	{
		if (nullptr == Entity)
		{
			MsgBoxAssert("�������� ���� ���͸� �����Ϸ��� �߽��ϴ�.");
			return false;
		}

		if (false == Entity->GetPixelCheck())
		{
			continue;
		}

		if (_CheckColor == Entity->GetColor(_Position))
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
