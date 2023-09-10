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

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Editor);
	}
}

void MainMenu::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('T'))
	{
		ActorRelease();

		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void MainMenu::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsLevel::LevelStart(_PrevLevel);

	LoadTexture();
	LoadSprite();
	InitActor();

	{
		if (nullptr == m_LevelCameraControler)
		{
			MsgBoxAssert("카메라 컨트롤러를 생성하지 않고 사용하려고 했습니다.");
			return;
		}

		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Title_Train_Sky.png");
		float4 HScale = Texture->GetScale().Half();
		HScale.Y *= -1.0f;
		m_LevelCameraControler->SetWorldPostion(HScale);
	}
}

void MainMenu::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}



void MainMenu::LoadTexture()
{
	GlobalUtils::LoadAllFileInPath("Resources\\Main\\Train\\TitleSpriteName");
	GlobalUtils::LoadAllFileInPath("Resources\\Main\\Train\\TitleSprite");
}

void MainMenu::LoadSprite()
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

void MainMenu::InitActor()
{
	m_BackDrop = CreateActor<BackDrop_MainMenu>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다");
		return;
	}

	m_BackDrop->Init();
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
	// 3. 텍스처 정리
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



void MainMenu::ActorRelease()
{
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
		m_BackDrop = nullptr;
	}
}