#include "PreCompile.h"
#include "MainMenu.h"


#include "GlobalValue.h"
#include "GlobalUtils.h"

#include "BackDrop_MainMenu.h"
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
		m_BackDrop = CreateActor<BackDrop_MainMenu>(EUPDATEORDER::Objects);
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

	{
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


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources");
		Dir.MoveChild("Main");

		std::vector<GameEngineDirectory> Result = Dir.GetAllDirectory();
		for (size_t i = 0; i < Result.size(); i++)
		{
			GameEngineDirectory& Dir = Result[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}


	{
		if (nullptr == m_LevelCameraControler)
		{
			MsgBoxAssert("카메라 컨트롤러를 생성하지 않고 사용하려고 했습니다.");
			return;
		}

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Parallax_Layer1.png");
		float4 TextureScale = Texture->GetScale();
		TextureScale.Y *= -1.0f;

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.X *= -1.0f;
		float4 MoveCameraPos = TextureScale + HWinScale;

		m_LevelCameraControler->SetWorldPostion(MoveCameraPos);
	}
}

void MainMenu::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	// 1. 액터 정리
	m_BackDrop->ReleaseCurrentLevelChildActor();

	// 2. 스프라이트 정리
	{
		GameEngineSprite::Release("Parallax_Layer1.png");
		GameEngineSprite::Release("Parallax_Layer3.png");
		GameEngineSprite::Release("Parallax_Layer4.png");
		GameEngineSprite::Release("Parallax_Layer5.png");
		GameEngineSprite::Release("Parallax_Layer6.png");
		GameEngineSprite::Release("Parallax_Layer7.png");
		GameEngineSprite::Release("Parallax_Layer8.png");
		GameEngineSprite::Release("Parallax_Layer10_2.png");

		GameEngineSprite::Release("MainMenuClothes");
		GameEngineSprite::Release("MainMenuElectric");
		GameEngineSprite::Release("MainMenuFlag");
		GameEngineSprite::Release("MainMenuHair");
		GameEngineSprite::Release("MainMenuMagicBack");
		GameEngineSprite::Release("MainMenuMagicFront");
		GameEngineSprite::Release("MainMenuMagicFront2");
	}

	// 3. 텍스처 정리
	GlobalUtils::ReleaseAllTextureInPath("Resources\\Main");

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Main");

	std::vector<GameEngineDirectory> Result = Dir.GetAllDirectory();
	for (size_t i = 0; i < Result.size(); i++)
	{
		GameEngineDirectory& Dir = Result[i];
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Release(Files[i].GetFileName());
		}
	}

	
	//GlobalUtils::releaseAllTextureInPath("Resources\\Main");

}