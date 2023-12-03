#include "PreCompile.h"
#include "FxBase.h"

FxBase::FxBase() 
{
}

FxBase::~FxBase() 
{
}


void FxBase::Init()
{
	Fx = CreateComponent<GameEngineSpriteRenderer>();
}

void FxBase::Release()
{
	Fx = nullptr;
}

void FxBase::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////