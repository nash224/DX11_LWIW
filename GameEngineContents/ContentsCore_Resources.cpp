#include "PreCompile.h"
#include "ContentsCore.h"


// data
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"


void ContentsCore::InitResources()
{
	if (nullptr == GameEngineTexture::Find("Ellie_Basic_ButterflyNet.png"))
	{
		// ÇÃ·¹ÀÌ ¾×ÅÍ
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// Å©¸®Ã³
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// ¸Ê
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// ¾Ù¸®
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// ºøÀÚ·ç
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\NPC");					// NPC 

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
	}


	// Map
	if (nullptr == GameEngineSprite::Find("GroundBase.png"))
	{
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

	LoadContentsData();
}


void ContentsCore::LoadContentsData()
{
	EventData::Init();

	// ¾ÆÀÌÅÛ
	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "¸¶³àÀÇ ²É", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "²É", EITEM_TYPE::Ingredient});

	// ¼ö¸®Àç·á 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "³ª¹µ°¡Áö", EITEM_TYPE::RepairMaterial });

	// À½½Ä
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Food });



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
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "¸ù½Ã¸®", "¸ù½Ã¸®ÅÐ", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "È£¹Ú °­¾ÆÁö", "È£¹Ú °­¾ÆÁöÀÇ ÅÐ Á¶°¢", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("BushBug", { "BushBug", "´ýºÒ ±úºñ", "´ýºÒ ±úºñ", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "»õ½Ï»õ", "»õ²É", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "Çª¸¥ ¹æ¿ï µµ¸¶¹ì", "¿ôÀ½¹æ¿ï", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day });

	// ½Ä¹°
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "¸¶³à²É", "¸¶³à²É »Ñ¸®", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "Àºº°¹æ¿ï²É", "Àºº°¹æ¿ï²É °¡·ç", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "´ÜÇ³ Çãºê", "´ÜÇ³ Çãºê", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay });

	// ¹°¾à
	ProductRecipeData::CreateData("BadGrassPotion", { "BadGrassPotion", "³ª»Û Ç® Á¦°Å ¹°¾à", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Four, "Mongsiri_Water", 2, "WitchFlower_Water", 2 });
	ProductRecipeData::CreateData("NutritionPotion", { "NutritionPotion", "Ç® ¼ºÀå ¹°¾à", EBREWINGOPTION::Normal, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "SilverStarFlower_Water", 2, "MapleHerb_Water", 2, "BushBug_Water", 2 });
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "ºÒ²É³îÀÌ ¹°¾à", EBREWINGOPTION::Hard, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "PumpkinTerrier_Powder", 2, "FlowerBird_Water", 2, "MoonButterfly_Water", 2 });

	// »çÅÁ
	ProductRecipeData::CreateData("UncurseCandy", { "UncurseCandy", "´ÜÇ³ Çãºê", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Three, "Mongsiri_Water", 2, "MapleHerb_Water", 2 });
	ProductRecipeData::CreateData("HealingCandy", { "HealingCandy", "Ä¡·á »çÅÁ", EBREWINGOPTION::Easy, EBREWINGOPTION::StirRight, EBREWINGOPTION::Four, "WitchFlower_Water", 2, "MapleHerb_Water", 2 });
}
