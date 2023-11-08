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
	// «√∑π¿Ã æ◊≈Õ
	GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// ≈©∏Æ√≥
	GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// ∏ 
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// æŸ∏Æ
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// ∫¯¿⁄∑Á
	GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\NPC");					// NPC 

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

	// æ∆¿Ã≈€
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "∏∂≥‡¿« ≤…¡Û", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "∏˘Ω√∏Æ ≈–¡Û", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "Ω£«Æπ˙∑π ¡Û", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "∏ﬁ¿Ã«√ «„∫Í ≤…¡Û", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Water", { "SilverStarFlower_Water", "Ω«πˆ∫ß ≤…¡Û", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "∏˘Ω√∏Æ≈–", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "∏˘Ω√∏Æ≈–", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "∏∂≥‡¿« ≤…", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "≤…", EITEM_TYPE::Ingredient });

	// ∆˜º«
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "≥™ª€ «Æ ¡¶∞≈π∞æ‡", EITEM_TYPE::Ingredient });

	// ºˆ∏Æ¿Á∑· 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "≥™πµ∞°¡ˆ", EITEM_TYPE::RepairMaterial });

	// ¿ΩΩƒ
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "∏˘Ω√∏Æ≈–", EITEM_TYPE::Food });



	// ¿Á∑· ∞°∞¯
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "∏˘Ω√∏Æ¡Û", "Mongsiri_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "»£π⁄ ∞≠æ∆¡ˆ ≈– ∆ƒøÏ¥ı", "PumpkinTerrier_Collect", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug_Water", { "BushBug_Water", "¥˝∫“ ±˙∫Ò¡Û", "BushBug_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "ªı≤…¡Û", "FlowerBird_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "øÙ¿ΩπÊøÔ¡Û", "BubbleLizard_Collect", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "∏∂≥‡≤…¡Û", "WitchFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "¿∫∫∞πÊøÔ≤…¡Û", "SilverStarFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "¥‹«≥ «„∫Í¡Û", "MapleHerb_Collect", EBrewingMachineType::Extractor, 2 });

	// µøπ∞
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "∏˘Ω√∏Æ", "∏˘Ω√∏Æ≈–", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "»£π⁄ ∞≠æ∆¡ˆ", "»£π⁄ ∞≠æ∆¡ˆ¿« ≈– ¡∂∞¢", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("BushBug", { "BushBug", "¥˝∫“ ±˙∫Ò", "¥˝∫“ ±˙∫Ò", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "ªıΩœªı", "ªı≤…", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "«™∏• πÊøÔ µµ∏∂πÏ", "øÙ¿ΩπÊøÔ", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day });

	// Ωƒπ∞
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "∏∂≥‡≤…", "∏∂≥‡≤… ª—∏Æ", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "¿∫∫∞πÊøÔ≤…", "¿∫∫∞πÊøÔ≤… ∞°∑Á", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "¥‹«≥ «„∫Í", "¥‹«≥ «„∫Í", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay });

	// π∞æ‡
	ProductRecipeData::CreateData("BadGrassPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"WitchFlower_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "BadGrassPotion", "≥™ª€ «Æ ¡¶∞≈ π∞æ‡" });
	ProductRecipeData::CreateData("NutritionPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1}, {"MapleHerb_Water", 1 },{"BushBug_Water", 1  }}, EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "NutritionPotion", "«Æ º∫¿Â π∞æ‡" });
	ProductRecipeData::CreateData("FirecrackerPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"PumpkinTerrier_Powder", 1,}, { "FlowerBird_Water", 1 },{"MoonButterfly_Water", 1} }, EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "FirecrackerPotion", "∫“≤…≥Ó¿Ã π∞æ‡" });

	// ªÁ≈¡
	ProductRecipeData::CreateData("UncurseCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three,  "UncurseCandy", "¥‹«≥ «„∫Í" });
	ProductRecipeData::CreateData("HealingCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"WitchFlower_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "HealingCandy", "ƒ°∑· ªÁ≈¡" });
}



void ContentsCore::InitBlendResources()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src∆—≈Õ
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;

		const std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("Blend_Light", Desc);

		std::shared_ptr<GameEngineMaterial> OverRayMaterial = GameEngineMaterial::Create("2DTexture_Light");
		OverRayMaterial->SetVertexShader("TextureShader_VS");
		OverRayMaterial->SetPixelShader("TextureShader_PS");
		OverRayMaterial->SetBlendState("Blend_Light");
	}


	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src∆—≈Õ
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