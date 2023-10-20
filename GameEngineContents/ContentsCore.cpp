#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineBlend.h>

#include "GlobalLoad.h"

#include "LogoLevel.h"
#include "MainMenu.h"
#include "LoadingLevel.h"
#include "PlayLevel.h"
#include "Field_Center.h"
#include "WitchHouse_Yard.h"
#include "WitchHouse_UpFloor.h"
#include "WitchHouse_DownFloor.h"

#include "ContentsGUI.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineGUI::CreateGUIWindow<ContentsGUI>("ContentsGUI");
	GlobalLoad::LoadGlobalResource();
	GlobalValue::SetWindowScale(GetStartWindowSize());
	

	

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::CreateLevel<LoadingLevel>("LoadingLevel");
	GameEngineCore::CreateLevel<Field_Center>("Field_Center");
	GameEngineCore::CreateLevel<WitchHouse_Yard>("WitchHouse_Yard");
	GameEngineCore::CreateLevel<WitchHouse_UpFloor>("WitchHouse_UpFloor");
	GameEngineCore::CreateLevel<WitchHouse_DownFloor>("WitchHouse_DownFloor");
	GameEngineCore::ChangeLevel("MainMenu");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}