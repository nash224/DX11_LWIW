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
}


bool StaticEntity::GetPixelCheck() const
{
	return isPixelSet;
}

void StaticEntity::SetPixelCollision(std::string_view _FileName)
{
	PixelRenderer = CreateComponent<GameEngineSpriteRenderer>();
	PixelRenderer->SetViewCameraSelect(static_cast<int>(ECAMERAORDER::MainPrev));
	PixelRenderer->RenderBaseInfoValue.Target0 = 0;
	PixelRenderer->RenderBaseInfoValue.Target1 = 1;
	PixelRenderer->On();
	PixelRenderer->SetSprite(_FileName);

	isPixelSet = true;
}