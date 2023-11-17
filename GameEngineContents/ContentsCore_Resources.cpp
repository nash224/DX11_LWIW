#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineBlend.h>

// data
#include "ContentsEvent.h"
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"


void ContentsCore::InitResources()
{
	// ÇÃ·¹ÀÌ ¾×ÅÍ
	GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// Å©¸®Ã³
	GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// ¸Ê
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// ¾Ù¸®
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// ºøÀÚ·ç
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\NPC");					// NPC 
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Fx");					// Fx

	GameEngineSprite::CreateSingle("Broom_Particle.png");

	{
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

	LoadContentsData();
}


void ContentsCore::LoadContentsData()
{
	ContentsEvent::Init();

	// ¾ÆÀÌÅÛ
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "¸¶³àÀÇ ²ÉÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "¸ù½Ã¸® ÅÐÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "½£Ç®¹ú·¹ Áó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "¸ÞÀÌÇÃ Çãºê Áó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "Àºº°¹æ¿ï²ÉÁó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "²É»õÀÇ ²É Áó", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MoonButterfly_Water", { "MoonButterfly_Water", "´Þºû ³ªºñ Áó", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "¸ù½Ã¸®ÅÐ", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "¹ú·¹", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "¸¶³àÀÇ ²É", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "²É»õÀÇ ²É", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Collect", { "MapleHerb_Collect", "¸ÞÀÌÇÃ Çãºê", EITEM_TYPE::Ingredient });
	ItemData::CreateData("SilverStarFlower_Collect", { "SilverStarFlower_Collect", "Àºº°¹æ¿ï²É °¡·ç", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MoonButterfly_Collect", { "MoonButterfly_Collect", "´Þºû ³ªºñ", EITEM_TYPE::Ingredient });

	// Äù½ºÆ®
	ItemData::CreateData("Item_Etc_10", { "Item_Etc_10", "ÂøÁó±â À¯¸®º´", EITEM_TYPE::Quest });

	// Æ÷¼Ç
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "³ª»Û Ç® Á¦°Å¹°¾à", EITEM_TYPE::Potion });
	ItemData::CreateData("NutritionPotion", { "NutritionPotion", "¿µ¾ç °ø±Þ ¹°¾à", EITEM_TYPE::Potion });
	ItemData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "ÆøÁ× ¹°¾à", EITEM_TYPE::Potion });

	ItemData::CreateData("UncurseCandy", { "UncurseCandy", "ÀúÁÖÇØÁ¦ »çÅÁ", EITEM_TYPE::Potion });
	ItemData::CreateData("HealingCandy", { "HealingCandy", "È¸º¹ »çÅÁ", EITEM_TYPE::Potion });

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
	ProductRecipeData::CreateData("BadGrassPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"WitchFlower_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "BadGrassPotion", "³ª»Û Ç® Á¦°Å ¹°¾à" });
	ProductRecipeData::CreateData("NutritionPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1}, {"MapleHerb_Water", 1 },{"BushBug_Water", 1  }}, EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "NutritionPotion", "¿µ¾ç °ø±Þ ¹°¾à" });
	ProductRecipeData::CreateData("FirecrackerPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1,}, { "FlowerBird_Water", 1 },{"BushBug_Water", 1} }, EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "FirecrackerPotion", "ºÒ²É³îÀÌ ¹°¾à" });

	// »çÅÁ
	ProductRecipeData::CreateData("UncurseCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three,  "UncurseCandy", "´ÜÇ³ Çãºê" });
	ProductRecipeData::CreateData("HealingCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"WitchFlower_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "HealingCandy", "Ä¡·á »çÅÁ" });
}



void ContentsCore::InitMaterialResoruces()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // srcÆÑÅÍ
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		const std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("Blend_Light", Desc);

		std::shared_ptr<GameEngineMaterial> LightMaterial = GameEngineMaterial::Create("2DTexture_Light");
		LightMaterial->SetVertexShader("TextureShader_VS");
		LightMaterial->SetPixelShader("TextureShader_PS");
		LightMaterial->SetBlendState("Blend_Light");
	}

	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // srcÆÑÅÍ
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		const std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("Overlay", Desc);

		std::shared_ptr<GameEngineMaterial> OverRayMaterial = GameEngineMaterial::Create("Texture2D_Overlay");
		OverRayMaterial->SetVertexShader("TextureShader_VS");
		OverRayMaterial->SetPixelShader("TextureShader_PS");
		OverRayMaterial->SetBlendState("Overlay");
	}




	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("SkyLightEffect2D");
		Mat->SetVertexShader("SkyLightEffect_VS");
		Mat->SetPixelShader("SkyLightEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("OutLineEffect2D");
		Mat->SetVertexShader("OutLineEffect_VS");
		Mat->SetPixelShader("OutLineEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("LineGaugeTexture2D");
		Mat->SetVertexShader("LineGaugeShader_VS");
		Mat->SetPixelShader("LineGaugeShader_PS");
	}
}

void ContentsCore::InitAutoCompile()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("GameEngineContentsShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (GameEngineFile& pFile : Files)
		{
			GameEngineShader::AutoCompile(pFile);
		}
	}
}