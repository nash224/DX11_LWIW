#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "GlobalLoad.h"

#include "LogoLevel.h"
#include "MainMenu.h"
#include "Field_Center.h"
#include "WitchHouse_Yard.h"
#include "WitchHouse_UpFloor.h"
#include "WitchHouse_DownFloor.h"
#include "DreamLevel.h"
#include "EndingLevel.h"
#include "TestLevel.h"
#include "MapEditorLevel.h"

#include "ContentsGUI.h"

ContentsCore::ContentsCore()
{
	GameEngineInput::AddInputObject(this);
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GlobalValue::SetWindowScale(GetStartWindowSize());
	GlobalLoad::LoadGlobalResource();
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor(float4{ 0.5f, 0.5f, 0.5f });
	GameEngineFont::Load("카페24 아네모네");
	GameEngineFont::Load("Liberation Sans");
	GameEngineFont::Load("Sandoll 삼립호빵체 TTF Basic");
	GameEngineFont::Load("Perfect DOS VGA 437");
	GameEngineFont::Load("제주한라산");

	GlobalValue::SetSoundVolume(0.5f);

	InitResources();
	InitAutoCompile();
	InitMaterialResoruces();
	

	
	ImGuiCoreWindow = GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	ImGuiCoreWindow->Off();


	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<MainMenu>("MainMenu");
	GameEngineCore::CreateLevel<Field_Center>("Field_Center");
	GameEngineCore::CreateLevel<WitchHouse_Yard>("WitchHouse_Yard");
	GameEngineCore::CreateLevel<WitchHouse_UpFloor>("WitchHouse_UpFloor");
	GameEngineCore::CreateLevel<WitchHouse_DownFloor>("WitchHouse_DownFloor");
	GameEngineCore::CreateLevel<DreamLevel>("DreamLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");
	GameEngineCore::CreateLevel<TestLevel>("TestLevel");
	GameEngineCore::CreateLevel<MapEditorLevel>("MapEditorLevel");
	GameEngineCore::ChangeLevel("LogoLevel");


	ImGuiContentWindow = GameEngineGUI::CreateGUIWindow<ContentsGUI>("ContentsGUI");
	ImGuiContentWindow->Off();
}

void ContentsCore::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_F6, this))
	{
		if (nullptr != ImGuiCoreWindow)
		{
			if (true == ImGuiCoreWindow->IsUpdate())
			{
				ImGuiCoreWindow->Off();
			}
			else
			{
				ImGuiCoreWindow->On();
			}
		}
	}

	if (GameEngineInput::IsDown(VK_F7, this))
	{
		if (nullptr != ImGuiContentWindow)
		{
			if (true == ImGuiContentWindow->IsUpdate())
			{
				ImGuiContentWindow->Off();
			}
			else
			{
				ImGuiContentWindow->On();
			}
		}
	}

}