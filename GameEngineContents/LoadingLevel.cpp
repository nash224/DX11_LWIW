#include "PreCompile.h"
#include "LoadingLevel.h"

#include "GlobalUtils.h"

#include "BackDrop_Loading.h"

#include "CameraControler.h"
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"



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
		MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ��� �߽��ϴ�.");
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
	LoadContentsData();

	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("ī�޶� �������� �ʰ� ������ �� �����ϴ�.");
		return;
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("���͸� �������� �ʾҽ��ϴ�.");
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
		// �÷��� ����
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie");
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie");
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");

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


	// ���� ������ �Ѿ�� Release
	GlobalUtils::LoadAllFileInPath("Resources\\LoadingLevel");
}

void LoadingLevel::LoadSprite()
{
	if (false == GlobalSpriteLoadCheck)
	{
#pragma region Ellie Sprite
		// �⺻����
		GameEngineSprite::CreateCut("Ellie_Basic_Idle.png", 7, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Walk.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Run.png", 9, 8);
		GameEngineSprite::CreateCut("Ellie_Basic_Throw.png", 8, 7);

		// �⺻���� - Riding
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Standing.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Moving.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Boosting.png", 8, 7);

		// ���� 
		GameEngineSprite::CreateCut("Ellie_Basic_ButterflyNet.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_RootUp.png", 10, 9);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_Sit.png", 7, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Collecting_Mongsiri.png", 5, 4);

		// ���� ����
		GameEngineSprite::CreateCut("Ellie_Basic_Cheer.png", 6, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Fail.png", 6, 5);
		GameEngineSprite::CreateCut("Ellie_Basic_Drink.png", 6, 5);

#pragma endregion 

#pragma region Actor Sprite

		// MongSiri
		GameEngineSprite::CreateSingle("SquishychubHole.png");
		GameEngineSprite::CreateCut("Mongsiri_Collected.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_CollectedA.png", 4, 1);
		GameEngineSprite::CreateCut("Mongsiri_Disappear.png", 6, 6);
		GameEngineSprite::CreateCut("Mongsiri_Escape.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_Idle.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleA.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleB.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_Jump.png", 5, 5);

#pragma endregion 


		// UI
		GameEngineSprite::CreateCut("PointArrow.png", 3, 2);
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
		GameEngineSprite::CreateCut("Inventory_SampleIcon.png", 3, 1);
		GameEngineSprite::CreateCut("Tool_Icon.png", 3, 1);

		GameEngineSprite::CreateCut("IllustedBook_Icon_Star.png", 3, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Fire.png", 5, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Ladle.png", 3, 1);


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
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_BackDrop->Init();
}

void LoadingLevel::LoadContentsData()
{
	EventData::Init();

	// ������
	ItemData::CreateData("Mongsiri", { "Mongsiri", "���ø���", EITEM_TYPE::Ingredient });

	// ��� ����
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "���ø���", "Mongsiri", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "ȣ�� ������ �� �Ŀ��", "PumpkinTerrier", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug", { "BushBug_Water", "���� ������", "BushBug", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird", { "FlowerBird_Water", "������", "FlowerBird", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "���������", "BubbleLizard", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "�������", "WitchFlower", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "����������", "SilverStarFlower", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "��ǳ �����", "MapleHerb", EBrewingMachineType::Extractor, 2 });

	// ����
	BiologyData::CreateData("Mongsiri", {"Mongsiri", "���ø�", "���ø���", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day});
	BiologyData::CreateData("PumpkinTerrier", {"PumpkinTerrier", "ȣ�� ������", "ȣ�� �������� �� ����", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay});
	BiologyData::CreateData("BushBug", {"BushBug", "���� ����", "���� ����", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", {"FlowerBird", "���ϻ�", "����", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day});
	BiologyData::CreateData("BubbleLizard", {"BubbleLizard", "Ǫ�� ��� ������", "�������", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day});

	// �Ĺ�
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "�����", "����� �Ѹ�", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "��������", "�������� ����", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", {"MapleHerb", "��ǳ ���", "��ǳ ���", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay});

	// ����
	ProductRecipeData::CreateData("BadGrassPotion", {"BadGrassPotion", "���� Ǯ ���� ����", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Four, "Mongsiri_Water", 2, "WitchFlower_Water", 2});
	ProductRecipeData::CreateData("NutritionPotion", {"NutritionPotion", "Ǯ ���� ����", EBREWINGOPTION::Normal, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "SilverStarFlower_Water", 2, "MapleHerb_Water", 2, "BushBug_Water", 2});
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "�Ҳɳ��� ����", EBREWINGOPTION::Hard, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "PumpkinTerrier_Powder", 2, "FlowerBird_Water", 2, "MoonButterfly_Water", 2 });

	// ����
	ProductRecipeData::CreateData("UncurseCandy", {"UncurseCandy", "��ǳ ���", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Three, "Mongsiri_Water", 2, "MapleHerb_Water", 2});
	ProductRecipeData::CreateData("HealingCandy", {"HealingCandy", "ġ�� ����", EBREWINGOPTION::Easy, EBREWINGOPTION::StirRight, EBREWINGOPTION::Four, "WitchFlower_Water", 2, "MapleHerb_Water", 2});
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