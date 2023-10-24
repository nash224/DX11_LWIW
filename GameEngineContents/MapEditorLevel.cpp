#include "PreCompile.h"
#include "MapEditorLevel.h"

MapEditorLevel::MapEditorLevel() 
{
}

MapEditorLevel::~MapEditorLevel() 
{
}


void MapEditorLevel::Start()
{
	ContentsLevel::Start();
}

void MapEditorLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);
}


void MapEditorLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);
}

void MapEditorLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

