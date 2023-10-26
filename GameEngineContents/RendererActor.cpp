#include "PreCompile.h"
#include "RendererActor.h"

RendererActor::RendererActor() 
{
}

RendererActor::~RendererActor() 
{
}


void RendererActor::Start()
{

}

void RendererActor::Update(float _Delta)
{
}

void RendererActor::Release()
{
	m_Renderer = nullptr;
}

void RendererActor::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void RendererActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void RendererActor::Init(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
}


