#include "PreCompile.h"
#include "RendererActor.h"

RendererActor::RendererActor() 
{
}

RendererActor::~RendererActor() 
{
}


void RendererActor::Release()
{
	m_Renderer = nullptr;
}

void RendererActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void RendererActor::Init(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
}