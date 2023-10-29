#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineBlend.h>

#include "GlobalLoad.h"

#include "LogoLevel.h"
#include "MainMenu.h"
#include "PlayLevel.h"
#include "Field_Center.h"
#include "WitchHouse_Yard.h"
#include "WitchHouse_UpFloor.h"
#include "WitchHouse_DownFloor.h"
#include "MapEditorLevel.h"
#include "TestLevel.h"

#include "ContentsGUI.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GlobalLoad::LoadGlobalResource();
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor(float4{ 0.5f, 0.5f, 0.5f });
	GameEngineFont::Load("Liberation Sans");
	GameEngineFont::Load("Sandoll »ï¸³È£»§Ã¼ TTF Basic");
	GameEngineFont::Load("Perfect DOS VGA 437");
	InitResources();
	InitBlendResources();


	GlobalValue::SetWindowScale(GetStartWindowSize());
	

	

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::CreateLevel<Field_Center>("Field_Center");
	GameEngineCore::CreateLevel<WitchHouse_Yard>("WitchHouse_Yard");
	GameEngineCore::CreateLevel<WitchHouse_UpFloor>("WitchHouse_UpFloor");
	GameEngineCore::CreateLevel<WitchHouse_DownFloor>("WitchHouse_DownFloor");
	GameEngineCore::CreateLevel<TestLevel>("TestLevel");
	GameEngineCore::CreateLevel<MapEditorLevel>("MapEditorLevel");
	GameEngineCore::ChangeLevel("MainMenu");


	GameEngineGUI::CreateGUIWindow<ContentsGUI>("ContentsGUI");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}
