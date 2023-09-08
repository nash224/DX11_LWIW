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

	m_BackDrop = CreateActor<BackDrop_MainMenu>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다");
		return;
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
		GlobalUtils::LoadAllFileInPath("Resources\\Main\\Train\\TitleSpriteName");

		GameEngineSprite::CreateSingle("Background_Shadow-Title.png");
		GameEngineSprite::CreateSingle("Title_Train_Bridge.png");
		GameEngineSprite::CreateSingle("Title_Train_Bridge_Down.png");
		GameEngineSprite::CreateSingle("Title_Train_Sky.png");
		GameEngineSprite::CreateSingle("Title_Train_Water.png");
		GameEngineSprite::CreateSingle("Title_Train_Light.png");
		GameEngineSprite::CreateSingle("Title_Train_Moon.png");
		GameEngineSprite::CreateSingle("Title_Train_Mountain.png");
		GameEngineSprite::CreateSingle("Title_Train_Train.png");
		GameEngineSprite::CreateSingle("Title_Train_Train_1.png");
		GameEngineSprite::CreateSingle("Title_Train_Train_2.png");
		GameEngineSprite::CreateSingle("Title_Train_Train_3.png");
		GameEngineSprite::CreateSingle("Title_Train_Train_4.png");
		GameEngineSprite::CreateSingle("Title_Train_WaterShine.png");
		GameEngineSprite::CreateSingle("Title_Train_Window_0.png");
		GameEngineSprite::CreateSingle("Title_Train_Window_1.png");
		GameEngineSprite::CreateSingle("Title_Train_Window_2.png");
		GameEngineSprite::CreateSingle("Title_Train_WindowWater_blur.png");
		GameEngineSprite::CreateSingle("trainsmoke_big.png");
		GameEngineSprite::CreateSingle("trainsmoke_mid.png");
		GameEngineSprite::CreateSingle("trainsmoke_small.png");
		GameEngineSprite::CreateSingle("Title_train_star0.png");


	}

	{	
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Main\\Train\\Title_train_star0");

		std::vector<GameEngineDirectory> Result = Dir.GetAllDirectory();
		for (size_t i = 0; i < Result.size(); i++)
		{
			GameEngineDirectory& Dir = Result[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}



	{
		/*GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources");
		Dir.MoveChild("Main");

		std::vector<GameEngineDirectory> Result = Dir.GetAllDirectory();
		for (size_t i = 0; i < Result.size(); i++)
		{
			GameEngineDirectory& Dir = Result[i];
			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}*/
	}


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

	// 1. 액터 정리
	m_BackDrop->ReleaseCurrentLevelChildActor();

	// 2. 스프라이트 정리
	{
		GameEngineSprite::Release("Background_Shadow-Title.png");
		GameEngineSprite::Release("Title_Train_Bridge.png");
		GameEngineSprite::Release("Title_Train_Bridge_Down.png");
		GameEngineSprite::Release("Title_Train_Sky.png");
		GameEngineSprite::Release("Title_Train_Water.png");
		GameEngineSprite::Release("Title_Train_Light.png");
		GameEngineSprite::Release("Title_Train_Moon.png");
		GameEngineSprite::Release("Title_Train_Mountain.png");
		GameEngineSprite::Release("Title_Train_Train.png");
		GameEngineSprite::Release("Title_Train_Train_1.png");
		GameEngineSprite::Release("Title_Train_Train_2.png");
		GameEngineSprite::Release("Title_Train_Train_3.png");
		GameEngineSprite::Release("Title_Train_Train_4.png");
		GameEngineSprite::Release("Title_Train_WaterShine.png");
		GameEngineSprite::Release("Title_Train_Window_0.png");
		GameEngineSprite::Release("Title_Train_Window_1.png");
		GameEngineSprite::Release("Title_Train_Window_2.png");
		GameEngineSprite::Release("Title_Train_WindowWater_blur.png");
		GameEngineSprite::Release("trainsmoke_big.png");
		GameEngineSprite::Release("trainsmoke_mid.png");
		GameEngineSprite::Release("trainsmoke_small.png");
	}

	// 3. 텍스처 정리
	GlobalUtils::ReleaseAllTextureInPath("Resources\\Main\\Train\\TitleSpriteName");

	//GameEngineDirectory Dir;
	//Dir.MoveParentToExistsChild("Resources");
	//Dir.MoveChild("Resources\\Main\\Prev");

	//std::vector<GameEngineDirectory> Result = Dir.GetAllDirectory();
	//for (size_t i = 0; i < Result.size(); i++)
	//{
	//	GameEngineDirectory& Dir = Result[i];
	//	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	//	for (size_t i = 0; i < Files.size(); i++)
	//	{
	//		GameEngineTexture::Release(Files[i].GetFileName());
	//	}
	//}

	
	//GlobalUtils::releaseAllTextureInPath("Resources\\Main");

}