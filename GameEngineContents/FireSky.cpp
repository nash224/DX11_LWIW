#include "PreCompile.h"
#include "FireSky.h"

FireSky::FireSky() 
{
}

FireSky::~FireSky() 
{
}


void FireSky::Release()
{
	LineRenderer = nullptr;
}

void FireSky::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void FireSky::Init()
{
	RendererSetting();
}

void FireSky::RendererSetting()
{
	LineRenderer = CreateComponent<GameEngineSpriteRenderer>();
	LineRenderer->AutoSpriteSizeOn();
	LineRenderer->CreateAnimation("Line", "FireLine.png", 0.1f, 0, 4, false);
	LineRenderer->FindAnimation("Line")->Inter[0] = 2.0f;
	LineRenderer->RenderBaseInfoValue.Target3 = 1;
	LineRenderer->Off();
}