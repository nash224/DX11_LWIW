#include "PreCompile.h"
#include "StaticEntity.h"

StaticEntity::StaticEntity() 
{
}

StaticEntity::~StaticEntity() 
{
}


void StaticEntity::Start()
{
	InteractiveActor::Start();
}

void StaticEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void StaticEntity::Release()
{
	InteractiveActor::Release();
}

void StaticEntity::LevelStart(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelStart(_NextLevel);
}

void StaticEntity::LevelEnd(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////