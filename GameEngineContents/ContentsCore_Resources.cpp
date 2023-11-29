#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineBlend.h>

// data
#include "ContentsEvent.h"
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"
#include "QuestData.h"


void ContentsCore::InitResources()
{
	// 플레이 액터
	FileLoadFunction::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// 크리처
	FileLoadFunction::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// 맵
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// 앨리
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// 빗자루
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\NPC");					// NPC 
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Fx");					// Fx

	GameEngineSprite::CreateSingle("Broom_Particle.png");
	GameEngineSprite::CreateSingle("Broomstick_Collide_Particle.png");

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

	// 아이템
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "마녀꽃 즙", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "몽시리털즙", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "덤풀 깨비 즙", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "단풍 허브 즙", EITEM_TYPE::Ingredient });
	ItemData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "은별방울꽃즙", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "새꽃물", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MoonButterfly_Water", { "MoonButterfly_Water", "달빛 나비 즙", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "몽시리털", EITEM_TYPE::Source });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "덤불 깨비", EITEM_TYPE::Source });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "마녀꽃", EITEM_TYPE::Source });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "새꽃", EITEM_TYPE::Source });
	ItemData::CreateData("MapleHerb_Collect", { "MapleHerb_Collect", "단풍 허브", EITEM_TYPE::Source });
	ItemData::CreateData("SilverStarFlower_Collect", { "SilverStarFlower_Collect", "은별방울꽃 가루", EITEM_TYPE::Source });
	ItemData::CreateData("MoonButterfly_Collect", { "MoonButterfly_Collect", "달빛 나비", EITEM_TYPE::Source });
	ItemData::CreateData("PumpkinTerrier_Collect", { "PumpkinTerrier_Collect", "호박 강아지의 털 조각", EITEM_TYPE::Source });
	ItemData::CreateData("BubbleLizard_Collect", { "BubbleLizard_Collect", "웃음방울", EITEM_TYPE::Source });

	// 퀘스트
	ItemData::CreateData("Item_Etc_10", { "Item_Etc_10", "착즙기 유리병", EITEM_TYPE::Quest });

	// 포션
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "나쁜 풀 제거물약", EITEM_TYPE::Potion });
	ItemData::CreateData("NutritionPotion", { "NutritionPotion", "영양 공급 물약", EITEM_TYPE::Potion });
	ItemData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "폭죽 물약", EITEM_TYPE::Potion });

	ItemData::CreateData("UncurseCandy", { "UncurseCandy", "저주해제 사탕", EITEM_TYPE::Potion });
	ItemData::CreateData("HealingCandy", { "HealingCandy", "회복 사탕", EITEM_TYPE::Potion });

	// 수리재료 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "나뭇가지", EITEM_TYPE::RepairMaterial });

	// 음식
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "사과", EITEM_TYPE::Food });

	// 도구
	ItemData::CreateData("Item_Etc_11", { "Item_Etc_11", "잠자리채", EITEM_TYPE::Tool });
	ItemData::CreateData("Item_Etc_12", { "Item_Etc_12", "빗자루", EITEM_TYPE::Tool });



	// 재료 가공
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "몽시리털즙", "Mongsiri_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "호박 강아지 털 파우더", "PumpkinTerrier_Collect", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug_Water", { "BushBug_Water", "덤불깨비즙", "BushBug_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "새꽃물", "FlowerBird_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "웃음방울즙", "BubbleLizard_Collect", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "마녀꽃 즙", "WitchFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "은별방울꽃즙", "SilverStarFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "단풍 허브 즙", "MapleHerb_Collect", EBrewingMachineType::Extractor, 2 });

	// 동물
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "몽시리", "Mongsiri_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "호박 강아지", "PumpkinTerrier_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("BushBug", { "BushBug", "덤불 깨비", "BushBug_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "새싹새", "FlowerBird_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "푸른 방울 도마뱀", "BubbleLizard_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day });

	// 식물
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "마녀꽃", "WitchFlower_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "은별방울꽃", "SilverStarFlower_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "단풍 허브", "MapleHerb_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay });

	// 물약
	ProductRecipeData::CreateData("BadGrassPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"WitchFlower_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "BadGrassPotion", "나쁜 풀 제거 물약" , {} });
	ProductRecipeData::CreateData("NutritionPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1}, {"MapleHerb_Water", 1 },{"BushBug_Water", 1  }}, EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "NutritionPotion", "영양 공급 물약", {} });
	ProductRecipeData::CreateData("FirecrackerPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1,}, { "FlowerBird_Water", 1 },{"BushBug_Water", 1} }, EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirLeft, EBREWING_FIRE::Two, "FirecrackerPotion", "폭죽 물약" , {} });

	// 사탕
	/*std::vector<ProduectDESC> UncurseCandyDESCArray = { {EPRODUCTDESCTYPE::Observation, "마녀가 무언가 만들 때 많이 사용하기 때문에, 마녀 꽃이라는 이름이 붙여졌다."},{EPRODUCTDESCTYPE::, "마녀가 무언가 만들 때 많이 사용하기 때문에, 마녀 꽃이라는 이름이 붙여졌다."} };*/
	ProductRecipeData::CreateData("UncurseCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three,  "UncurseCandy", "저주해제 사탕" });
	ProductRecipeData::CreateData("HealingCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"WitchFlower_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "HealingCandy", "치료 사탕" });

	QuestData::CreateData("FindLetter", { "FindLetter" , "편지 읽기", "마당에 있는 편지를 읽어보자." });
	QuestData::CreateData("StartTraining", { "StartTraining" , "수습 시작", "폭죽 물약을 만들어서 정식 \n마녀가 되자." });
	QuestData::CreateData("Repair_Extractor", { "Repair_Extractor" , "착즙기 수리", "착즙기를 수리할 방법을 \n찾아보자." });
	QuestData::CreateData("Craft_Potion", { "Craft_Potion" , "나쁜 풀 제거 물약 제조", "D 키를 눌러 도감을 확인 후,\n나쁜 풀 제거 물약을 제작하자." });
	QuestData::CreateData("Aurea_Cure", { "Aurea_Cure" , "저주 해제 사탕 제조", "아우레아에게 저주 해제\n사탕을 주자." });
	QuestData::CreateData("Dian_BadWeedPotion", { "Dian_BadWeedPotion" , "물약 검증", "다이엔에게 나쁜 풀 제거\n물약을 주자." });
	QuestData::CreateData("Dian_Cracker_Recipe", { "Dian_Cracker_Recipe" , "폭죽 포션 레시피", "다이엔에게 영양 공급\n물약을 주자." });
	QuestData::CreateData("Craft_Cracker_Potion", { "Craft_Cracker_Potion" , "폭죽 포션 제작", "수습을 마치기 위해 폭죽\n물약을 제작하자." });
	QuestData::CreateData("Show_Cracker_Potion", { "Show_Cracker_Potion" , "정식까지 한 걸음", "초록숲 평원으로 가서\n정식 마녀가 되자." });
}



void ContentsCore::InitMaterialResoruces()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src팩터
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Blend_Light", Desc);

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

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src팩터
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Overlay", Desc);

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
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("GaugeTexture2D");
		Mat->SetVertexShader("GaugeShader_VS");
		Mat->SetPixelShader("GaugeShader_PS");
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