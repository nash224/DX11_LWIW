#include "PreCompile.h"
#include "MainMenu.h"

// Global
#include "GlobalValue.h"
#include "GlobalUtils.h"

// Manager
#include "BackDrop_MainMenu.h"
#include "CameraControler.h"

// Actor
#include "UI_MainMenu_Button.h"
#include "TitleUI.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu() 
{
}



void MainMenu::Start()
{
	ContentsLevel::Start();

	if (nullptr != ContentsLevel::LevelCamera)
	{
		float4 CameraPosition = GlobalValue::GetWindowScale().Half();
		CameraPosition.Y *= -1.0f;
		
		ContentsLevel::LevelCamera->SetLocalPostion(CameraPosition);
		ContentsLevel::LevelCamera->SetCameraMode(ECAMERAMODE::Fix);
	}

	Back = CreateActor<BackDrop_MainMenu>(EUPDATEORDER::Objects);
}

void MainMenu::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('Q', this))
	{
		GameEngineCore::ChangeLevel("TestLevel");
	}

	if (true == GameEngineInput::IsDown('T', this))
	{
		GameEngineCore::ChangeLevel("WitchHouse_Yard");
	}
}

void MainMenu::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsLevel::LevelStart(_PrevLevel);
}

void MainMenu::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}