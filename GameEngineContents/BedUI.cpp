#include "PreCompile.h"
#include "BedUI.h"

BedUI::BedUI() 
{
}

BedUI::~BedUI() 
{
}

void BedUI::Update(float _Delta)
{
	State.Update(_Delta);
}

void BedUI::Release()
{
	BaseRenderer = nullptr;
	HedFontRenderer = nullptr;
	CursorInfo.CursorRenderer = nullptr;
	SlotInfo.clear();
}

void BedUI::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BedUI::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BedUI::Init()
{
	RendererSetting();
}

void BedUI::RendererSetting()
{

}