#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineBlend.h>

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
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "¸¶³àÀÇ ²ÉÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "¸ù½Ã¸® ÅÐÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "½£Ç®¹ú·¹ Áó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "¸ÞÀÌÇÃ Çãºê ²ÉÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Water", { "SilverStarFlower_Water", "½Ç¹öº§ ²ÉÁó", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "¸¶³àÀÇ ²É", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "²É", EITEM_TYPE::Ingredient});

	// Æ÷¼Ç
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "³ª»Û Ç® Á¦°Å¹°¾à", EITEM_TYPE::Ingredient});

	// ¼ö¸®Àç·á 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "³ª¹µ°¡Áö", EITEM_TYPE::RepairMaterial });

	// À½½Ä
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Food });



	// Àç·á °¡°ø
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "¸ù½Ã¸®Áó", "Mongsiri_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "È£¹Ú °­¾ÆÁö ÅÐ ÆÄ¿ì´õ", "PumpkinTerrier_Collect", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug_Water", { "BushBug_Water", "´ýºÒ ±úºñÁó", "BushBug_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "»õ²ÉÁó", "FlowerBird_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "¿ôÀ½¹æ¿ïÁó", "BubbleLizard_Collect", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "¸¶³à²ÉÁó", "WitchFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "Àºº°¹æ¿ï²ÉÁó", "SilverStarFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "´ÜÇ³ ÇãºêÁó", "MapleHerb_Collect", EBrewingMachineType::Extractor, 2 });

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
	ProductRecipeData::CreateData("BadGrassPotion", { "BadGrassPotion", "³ª»Û Ç® Á¦°Å ¹°¾à", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "Mongsiri_Water", 1, "WitchFlower_Water", 1 });
	ProductRecipeData::CreateData("NutritionPotion", { "NutritionPotion", "Ç® ¼ºÀå ¹°¾à", EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "SilverStarFlower_Water", 1, "MapleHerb_Water", 1, "BushBug_Water", 1 });
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "ºÒ²É³îÀÌ ¹°¾à", EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "PumpkinTerrier_Powder", 1, "FlowerBird_Water", 1, "MoonButterfly_Water", 1 });

	// »çÅÁ
	ProductRecipeData::CreateData("UncurseCandy", { "UncurseCandy", "´ÜÇ³ Çãºê", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three, "Mongsiri_Water", 1, "MapleHerb_Water", 1 });
	ProductRecipeData::CreateData("HealingCandy", { "HealingCandy", "Ä¡·á »çÅÁ", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "WitchFlower_Water", 1, "MapleHerb_Water", 1 });
}



void ContentsCore::InitBlendResources()
{
	D3D11_BLEND_DESC Desc = {};

	// ·»´õÅ¸°Ù´ç ºí·£µå ¿É¼ÇÀ» °¢°¢ Àû¿ëÇÒ²¨³Ä
	Desc.IndependentBlendEnable = false;

	// ·»´õÅ¸°Ù 0¹ø 
	// ºí·£µå Çã¿ë
	Desc.RenderTarget[0].BlendEnable = true;

	// »ö±ò ÀüÃ¼¸¦ ´ë»óÀ¸·Î »ï°Ú´Ù.
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// »öÀ» ´õÇÑ´Ù
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_blend

	// src srcColor * srcÀÇ ¾ËÆÄ
	// 1, 0, 0(, 1) * 1.0f
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // srcÆÑÅÍ

	// src 1, 0, 0, 1 * (1 - srcÀÇ ¾ËÆÄ)
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;	// »öÀ» ´õÇÏ´Âµ¥
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;	// ¼Ò½º´Â »ö¸¸ÀÔÈû
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;	// ¿øº»Àº À¯Áö

	std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("Overlay", Desc);
}