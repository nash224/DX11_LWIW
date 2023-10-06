#include "PreCompile.h"
#include "DynamicEntity.h"

DynamicEntity::DynamicEntity() 
{
}

DynamicEntity::~DynamicEntity() 
{
}


void DynamicEntity::Start()
{
	InteractiveActor::Start();
}

void DynamicEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void DynamicEntity::Release()
{
	InteractiveActor::Release();
}


void DynamicEntity::LevelStart(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelStart(_NextLevel);
}

void DynamicEntity::LevelEnd(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////