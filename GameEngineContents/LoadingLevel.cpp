#include "PreCompile.h"
#include "LoadingLevel.h"


#include "GlobalUtils.h"

#include "BackDrop_Loading.h"
#include "CameraControler.h"
#include "BiologyData.h"



LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}


void LoadingLevel::Start()
{
	ContentsLevel::Start();

	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("존재하지 않는 액터를 사용하려고 했습니다.");
		return;
	}

	m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
}

void LoadingLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (true == GameEngineInput::IsPress('T'))
	{
		ActorRelease();
		GameEngineCore::ChangeLevel("WitchHouse_UpFloor");
	}
}

void LoadingLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();
	LoadItemInfo();

	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("카메라를 생성하지 않고 설정할 수 없습니다.");
		return;
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 않았습니다.");
		return;
	}

	float4 CameraPos = m_BackDrop->GetBackGroundScale();
	CameraPos = CameraPos.Half();
	CameraPos.Y *= -1.0f;
	GlobalValue::g_CameraControler->SetLocalPostion(CameraPos);
	
}

void LoadingLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);

	ActorRelease();
	ReleaseSprite();
	ReleaseTexture();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void LoadingLevel::LoadTexture()
{
	if (false == GlobalTextureLoadCheck)
	{
		// 플레이 액터
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie");


		//UI
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI");
		std::vector<GameEngineDirectory> Directions = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directions.size(); i++)
		{
			GameEngineDirectory Direction = Directions[i];
			std::vector<GameEngineFile> Files = Direction.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile pFile = Files[i];
				GameEngineTexture::Load(pFile.GetStringPath());
			}
		}

		GlobalTextureLoadCheck = true;
	}


	// 다음 레벨로 넘어가면 Release
	GlobalUtils::LoadAllFileInPath("Resources\\LoadingLevel");
}

void LoadingLevel::LoadSprite()
{
	if (false == GlobalSpriteLoadCheck)
	{
		// 기본조작
		GameEngineSprite::CreateCut("Ellie_Basic_Idle.png", 7, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Walk.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Run.png", 9, 8);
		GameEngineSprite::CreateCut("Ellie_Basic_Throw.png", 8, 7);

		// 기본조작 - Riding
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Standing.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Moving.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Boosting.png", 8, 7);


		// 수집 
		GameEngineSprite::CreateCut("Ellie_Basic_ButterflyNet.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_RootUp.png", 10, 9);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_Sit.png", 7, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Collecting_Mongsiri.png", 5, 4);

		// 단일 방향
		GameEngineSprite::CreateCut("Ellie_Basic_Cheer.png", 6, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Fail.png", 6, 5);
		GameEngineSprite::CreateCut("Ellie_Basic_Drink.png", 6, 5);

		// UI
		GameEngineSprite::CreateCut("Interaction_Arrow.png", 5, 1);
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
		GameEngineSprite::CreateCut("Inventory_SampleIcon.png", 3, 1);
		GameEngineSprite::CreateCut("Tool_Icon.png", 4, 1);


		//UI
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite");
		std::vector<GameEngineDirectory> Directions = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directions.size(); i++)
		{
			GameEngineDirectory Direction = Directions[i];
			std::vector<GameEngineFile> Files = Direction.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile pFile = Files[i];
				GameEngineSprite::CreateSingle(pFile.GetFileName());
			}
		}


		GlobalSpriteLoadCheck = true;
	}


	GameEngineSprite::CreateSingle("Loading_Back.png");
}

void LoadingLevel::LoadActor()
{
	m_BackDrop = CreateActor<BackDrop_Loading>(EUPDATEORDER::Objects);
	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BackDrop->Init();
}

void LoadingLevel::LoadItemInfo()
{
	BiologyData::CreateData("Mongsiri", {"Mongsiri", "몽시리", "몽시리털", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day});
	BiologyData::CreateData("PumpkinTerrier", {"PumpkinTerrier", "호박 강아지", "호박 강아지의 털 조각", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay});
	BiologyData::CreateData("BushBug", {"BushBug", "덤불 깨비", "덤불 깨비", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", {"FlowerBird", "새싹새", "새꽃", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day});
	BiologyData::CreateData("BubbleLizard", {"BubbleLizard", "푸른 방울 도마뱀", "웃음방울", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day});


	BiologyData::CreateData("WitchFlower", { "WitchFlower", "마녀꽃", "마녀꽃 뿌리", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "은별방울꽃", "은별방울꽃 가루", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", {"MapleHerb", "단풍 허브", "단풍 허브", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay});
}


void LoadingLevel::ActorRelease()
{
	if (nullptr != m_BackDrop)
	{
		m_BackDrop->ActorRelease();
		m_BackDrop = nullptr;
	}
}

void LoadingLevel::ReleaseSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\LoadingLevel");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::Release(File.GetFileName());
	}
}

void LoadingLevel::ReleaseTexture()
{
	GlobalUtils::ReleaseAllTextureInPath("Resources\\LoadingLevel");
}