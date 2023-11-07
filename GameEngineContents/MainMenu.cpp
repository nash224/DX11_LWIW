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
	: m_BackDrop(nullptr)
{
}

MainMenu::~MainMenu() 
{
}



void MainMenu::Start()
{
	ContentsLevel::Start();

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Editor);
	}
}

void MainMenu::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('T', this))
	{
		GameEngineCore::ChangeLevel("WitchHouse_Yard");
	}
}

void MainMenu::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsLevel::LevelStart(_PrevLevel);

	LoadTexture();
	LoadSprite();
	InitActor();

	{
		if (nullptr == GlobalValue::g_CameraControler)
		{
			MsgBoxAssert("ī�޶� ��Ʈ�ѷ��� �������� �ʰ� ����Ϸ��� �߽��ϴ�.");
			return;
		}

		float4 CameraPosition = GlobalValue::GetWindowScale().Half();
		CameraPosition.Y *= -1.0f;
		GlobalValue::g_CameraControler->SetLocalPostion(CameraPosition);
	}
}

void MainMenu::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////

void MainMenu::LoadTexture()
{
	GlobalUtils::LoadAllFileInPath("Resources\\Main\\Train\\TitleSpriteName");
	GlobalUtils::LoadAllFileInPath("Resources\\Main\\Train\\TitleSprite");
}

void MainMenu::LoadSprite()
{
	// MainMenu
	if (nullptr == GameEngineSprite::Find("Title_Train_Moon.png"))
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("Resources");
			Dir.MoveChild("Resources\\Main\\Train\\Title_train_star");

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("Resources");
			Dir.MoveChild("Resources\\Main\\Train\\TitleSpriteName");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile File = Files[i];
				GameEngineSprite::CreateSingle(File.GetFileName());
			}
		}

		{
			GameEngineSprite::CreateCut("trainsmoke_big.png", 4, 1);
			GameEngineSprite::CreateCut("trainsmoke_mid.png", 5, 1);
			GameEngineSprite::CreateCut("trainsmoke_small.png", 4, 1);
		}
	}
}

void MainMenu::InitActor()
{
	m_BackDrop = CreateActor<BackDrop_MainMenu>(EUPDATEORDER::Objects);
	m_BackDrop->Init();

	std::shared_ptr<UI_MainMenu_Button> Title_UI = CreateActor<UI_MainMenu_Button>(EUPDATEORDER::Objects);
	Title_UI->Init();
}

void MainMenu::ReleaseSprite()
{
	{
		GameEngineSprite::Release("Title_train_star");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Main\\Train\\TitleSprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineSprite::Release(File.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Main\\Train\\TitleSpriteName");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineSprite::Release(File.GetFileName());
		}
	}

}

void MainMenu::ReleaseTexture()
{
	// 3. �ؽ�ó ����
	GlobalUtils::ReleaseAllTextureInPath("Resources\\Main\\Train\\TitleSpriteName");

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Main\\Train\\Title_train_star");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Release(File.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Main\\Train\\TitleSprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Release(File.GetFileName());
		}
	}
}

