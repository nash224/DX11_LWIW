#include "PreCompile.h"
#include "ALightActor.h"

ALightActor::ALightActor() 
{
}

ALightActor::~ALightActor() 
{
}


void ALightActor::Start()
{
}

void ALightActor::Update(float _Delta)
{
}

void ALightActor::Release()
{
	RendererActor::Release();
}

void ALightActor::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void ALightActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////