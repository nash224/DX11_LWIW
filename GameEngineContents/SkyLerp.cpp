#include "PreCompile.h"
#include "SkyLerp.h"


SkyLerp* SkyLerp::SkyManager = nullptr;
SkyLerp::SkyLerp() 
{
}

SkyLerp::~SkyLerp() 
{
}


void SkyLerp::Start()
{
}

void SkyLerp::Update(float _Delta)
{
	SetSkyColor();
}

void SkyLerp::Release()
{
}

void SkyLerp::LevelStart(class GameEngineLevel* _NextLevel)
{
	SkyManager = this;
}

void SkyLerp::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void SkyLerp::Init()
{
	SkyManager = this;

	Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(ERENDERDEPTH::SkyBox)));


	Sun_Renderer = CreateComponent<GameEngineUIRenderer>();
	Sun_Renderer->SetSprite("SkyBox.png");
	Sun_Renderer->GetImageTransform().SetLocalScale(GlobalValue::GetWindowScale());
	Sun_Renderer->GetColorData().MulColor.A = 0.0f;
}


void SkyLerp::SetSkyColor()
{
	Sun_Renderer->GetColorData().MulColor = SkyColor;
}