#include "PreCompile.h"
#include "ContentsCore.h"

#include "GlobalLoad.h"

#include "MainMenu.h"
#include "LoadingLevel.h"
#include "PlayLevel.h"
#include "Field_Center.h"
#include "WitchHouse_Yard.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GlobalLoad::LoadGlobalResource();
	GlobalValue::SetWindowScale(GetStartWindowSize());

	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::CreateLevel<LoadingLevel>("LoadingLevel");
	GameEngineCore::CreateLevel<Field_Center>("Field_Center");
	GameEngineCore::CreateLevel<WitchHouse_Yard>("WitchHouse_Yard");
	GameEngineCore::ChangeLevel("MainMenu");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}