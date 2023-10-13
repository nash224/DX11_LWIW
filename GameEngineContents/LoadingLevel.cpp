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
		MsgBoxAssert("Á¸ÀçÇÏÁö ¾Ê´Â ¾×ÅÍ¸¦ »ç¿ëÇÏ·Á°í Çß½À´Ï´Ù.");
		return;
	}

	m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Play);
}

void LoadingLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (true == GameEngineInput::IsPress('T', this))
	{
		ActorRelease();
		GameEngineCore::ChangeLevel("WitchHouse_Yard");
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
		MsgBoxAssert("Ä«¸Þ¶ó¸¦ »ý¼ºÇÏÁö ¾Ê°í ¼³Á¤ÇÒ ¼ö ¾ø½À´Ï´Ù.");
		return;
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("¾×ÅÍ¸¦ »ý¼ºÇÏÁö ¾Ê¾Ò½À´Ï´Ù.");
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
		// ÇÃ·¹ÀÌ ¾×ÅÍ
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie");
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");

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


	// ´ÙÀ½ ·¹º§·Î ³Ñ¾î°¡¸é Release
	GlobalUtils::LoadAllFileInPath("Resources\\LoadingLevel");
}

void LoadingLevel::LoadSprite()
{
	if (false == GlobalSpriteLoadCheck)
	{
#pragma region Ellie Sprite
		// ±âº»Á¶ÀÛ
		GameEngineSprite::CreateCut("Ellie_Basic_Idle.png", 7, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_Walk.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Run.png", 9, 8);
		GameEngineSprite::CreateCut("Ellie_Basic_Throw.png", 8, 7);

		// ±âº»Á¶ÀÛ - Riding
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Standing.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Moving.png", 8, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Riding_Boosting.png", 8, 7);

		// ¼öÁý 
		GameEngineSprite::CreateCut("Ellie_Basic_ButterflyNet.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_RootUp.png", 10, 9);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_Sit.png", 7, 7);
		GameEngineSprite::CreateCut("Ellie_Basic_Collecting_Mongsiri.png", 5, 4);

		// ´ÜÀÏ ¹æÇâ
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


		{
			// Map
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("Resources");
			Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\");
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
		}

		// UI
		GameEngineSprite::CreateCut("PointArrow.png", 3, 2);
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
		GameEngineSprite::CreateCut("Inventory_SampleIcon.png", 3, 1);
		GameEngineSprite::CreateCut("Tool_Icon.png", 3, 1);

		GameEngineSprite::CreateCut("IllustedBook_Icon_Star.png", 3, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Fire.png", 5, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Ladle.png", 3, 1);


		{
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
		MsgBoxAssert("¾×ÅÍ¸¦ »ý¼ºÇÏÁö ¸øÇß½À´Ï´Ù.");
		return;
	}

	m_BackDrop->Init();
}

void LoadingLevel::LoadContentsData()
{
	EventData::Init();

	// ¾ÆÀÌÅÛ
	ItemData::CreateData("Mongsiri", { "Mongsiri", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });

	// Àç·á °¡°ø
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "¸ù½Ã¸®Áó", "Mongsiri", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "È£¹Ú °­¾ÆÁö ÅÐ ÆÄ¿ì´õ", "PumpkinTerrier", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug", { "BushBug_Water", "´ýºÒ ±úºñÁó", "BushBug", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird", { "FlowerBird_Water", "»õ²ÉÁó", "FlowerBird", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "¿ôÀ½¹æ¿ïÁó", "BubbleLizard", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "¸¶³à²ÉÁó", "WitchFlower", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "Àºº°¹æ¿ï²ÉÁó", "SilverStarFlower", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "´ÜÇ³ ÇãºêÁó", "MapleHerb", EBrewingMachineType::Extractor, 2 });

	// µ¿¹°
	BiologyData::CreateData("Mongsiri", {"Mongsiri", "¸ù½Ã¸®", "¸ù½Ã¸®ÅÐ", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day});
	BiologyData::CreateData("PumpkinTerrier", {"PumpkinTerrier", "È£¹Ú °­¾ÆÁö", "È£¹Ú °­¾ÆÁöÀÇ ÅÐ Á¶°¢", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay});
	BiologyData::CreateData("BushBug", {"BushBug", "´ýºÒ ±úºñ", "´ýºÒ ±úºñ", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", {"FlowerBird", "»õ½Ï»õ", "»õ²É", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day});
	BiologyData::CreateData("BubbleLizard", {"BubbleLizard", "Çª¸¥ ¹æ¿ï µµ¸¶¹ì", "¿ôÀ½¹æ¿ï", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day});

	// ½Ä¹°
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "¸¶³à²É", "¸¶³à²É »Ñ¸®", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "Àºº°¹æ¿ï²É", "Àºº°¹æ¿ï²É °¡·ç", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", {"MapleHerb", "´ÜÇ³ Çãºê", "´ÜÇ³ Çãºê", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay});

	// ¹°¾à
	ProductRecipeData::CreateData("BadGrassPotion", {"BadGrassPotion", "³ª»Û Ç® Á¦°Å ¹°¾à", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Four, "Mongsiri_Water", 2, "WitchFlower_Water", 2});
	ProductRecipeData::CreateData("NutritionPotion", {"NutritionPotion", "Ç® ¼ºÀå ¹°¾à", EBREWINGOPTION::Normal, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "SilverStarFlower_Water", 2, "MapleHerb_Water", 2, "BushBug_Water", 2});
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "ºÒ²É³îÀÌ ¹°¾à", EBREWINGOPTION::Hard, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "PumpkinTerrier_Powder", 2, "FlowerBird_Water", 2, "MoonButterfly_Water", 2 });

	// »çÅÁ
	ProductRecipeData::CreateData("UncurseCandy", {"UncurseCandy", "´ÜÇ³ Çãºê", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Three, "Mongsiri_Water", 2, "MapleHerb_Water", 2});
	ProductRecipeData::CreateData("HealingCandy", {"HealingCandy", "Ä¡·á »çÅÁ", EBREWINGOPTION::Easy, EBREWINGOPTION::StirRight, EBREWINGOPTION::Four, "WitchFlower_Water", 2, "MapleHerb_Water", 2});
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
	// LoadingLevel Resources
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