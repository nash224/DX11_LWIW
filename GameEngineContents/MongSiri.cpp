#include "PreCompile.h"
#include "MongSiri.h"

MongSiri::MongSiri() 
{
}

MongSiri::~MongSiri() 
{
}


void MongSiri::Start()
{
	DynamicEntity::Start();
}

void MongSiri::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void MongSiri::Release()
{
	DynamicEntity::Release();
}

void MongSiri::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void MongSiri::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////