#include "PreCompile.h"
#include "BackDrop_PlayLevel.h"

#include "NormalProp.h"
#include "StaticEntity.h"
#include "PixelManager.h"

#include "LootedItem.h"


BackDrop_PlayLevel::BackDrop_PlayLevel() 
{
}

BackDrop_PlayLevel::~BackDrop_PlayLevel() 
{
}

void BackDrop_PlayLevel::Start()
{
	PixelManagerPtr = GetLevel()->CreateActor<PixelManager>(EUPDATEORDER::Map);
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

GameEngineColor BackDrop_PlayLevel::GetColor(const float4& _Position, GameEngineColor _Color /*= GameEngineColor::WHITE*/)
{
	if (nullptr == PixelManagerPtr)
	{
		return _Color;
	}

	return PixelManagerPtr->GetColor(_Position, _Color);
}


void BackDrop_PlayLevel::CreateRenderActor(int _UpdateOrder, std::string_view _SpriteName,
	const float4& _Position, int _DepthType, bool _isFixDepth /*= true*/, float _DepthCorrection/*= 0.0f*/)
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
