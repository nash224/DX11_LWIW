#include "PreCompile.h"
#include "PumpkinTerrier.h"

PumpkinTerrier::PumpkinTerrier() 
{
}

PumpkinTerrier::~PumpkinTerrier() 
{
}


void PumpkinTerrier::Start()
{
	DynamicEntity::Start();
}

void PumpkinTerrier::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void PumpkinTerrier::Release()
{
	DynamicEntity::Release();

	m_Shadow = nullptr;
}

void PumpkinTerrier::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void PumpkinTerrier::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////