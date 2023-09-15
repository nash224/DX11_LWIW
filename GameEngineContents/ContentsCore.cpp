#include "PreCompile.h"
#include "ContentsCore.h"

#include "GlobalLoad.h"

#include "MainMenu.h"
#include "LoadingLevel.h"
#include "Field_Center.h"
#include "PlayLevel.h"

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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::ChangeLevel("MainMenu");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}