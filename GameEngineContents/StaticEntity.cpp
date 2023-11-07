#include "PreCompile.h"
#include "StaticEntity.h"

#include "PlayLevel.h"


StaticEntity::StaticEntity() 
{
}

StaticEntity::~StaticEntity() 
{
}

void StaticEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void StaticEntity::Release()
{
	InteractiveActor::Release();
	PixelRenderer = nullptr;
	PixelCol = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


bool StaticEntity::GetPixelCheck()
{
	return isPixelSet;
}

void StaticEntity::SetPixelCollision(std::string_view _FileName)
{
	PixelCol = CreateComponent<PixelCollision>();
	

	PixelCol->SetPixelFileName(_FileName);

	PixelRenderer = CreateComponent<GameEngineSpriteRenderer>();
	PixelRenderer->Off();
	PixelRenderer->SetSprite(_FileName);
	isPixelSet = true;
}

GameEngineColor StaticEntity::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	return PixelCol->GetColor(_Position, Transform.GetLocalPosition(), _DefaultColor);
}

void StaticEntity::UpdatePixelCollision()
{
	if (nullptr != PixelRenderer)
	{
		if (true == PlayLevel::PixelDebugMode)
		{
			PixelRenderer->On();
		}
		else
		{
			PixelRenderer->Off();
		}
	}
}