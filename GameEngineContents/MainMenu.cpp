#include "PreCompile.h"
#include "MainMenu.h"


#include "GlobalValue.h"
#include "GlobalUtils.h"

#include "BackDrop.h"
#include "CameraControler.h"
#include "TestActor.h"

MainMenu::MainMenu()
	: m_BackDrop(nullptr)
{
}

MainMenu::~MainMenu() 
{
}



void MainMenu::Start()
{
	ContentsLevel::Start();

	LevelType = ELEVELTYPE::MainMenu;

	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop>(EUPDATEORDER::Objects);
		m_BackDrop->SetLevelType(static_cast<int>(LevelType));
	}

	m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Editor);
}

void MainMenu::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('T'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void MainMenu::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsLevel::LevelStart(_PrevLevel);

	GlobalUtils::LoadAllFileInPath("Resources\\Main");

	GameEngineSprite::CreateSingle("Parallax_Layer1.png");
	GameEngineSprite::CreateSingle("Parallax_Layer3.png");
	GameEngineSprite::CreateSingle("Parallax_Layer4.png");
	GameEngineSprite::CreateSingle("Parallax_Layer5.png");
	GameEngineSprite::CreateSingle("Parallax_Layer6.png");
	GameEngineSprite::CreateSingle("Parallax_Layer7.png");
	GameEngineSprite::CreateSingle("Parallax_Layer8.png");
	GameEngineSprite::CreateSingle("Parallax_Layer10_2.png");
}

void MainMenu::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
	//GlobalUtils::releaseAllTextureInPath("Resources\\Main");

}