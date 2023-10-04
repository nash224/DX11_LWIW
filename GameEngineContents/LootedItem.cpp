#include "PreCompile.h"
#include "LootedItem.h"

LootedItem::LootedItem() 
{
}

LootedItem::~LootedItem() 
{
}


void LootedItem::Start()
{
	StaticEntity::Start();
}

void LootedItem::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void LootedItem::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void LootedItem::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////