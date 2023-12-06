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
	ItemData::CreateData("Item_Etc_11", { "Item_Etc_11", "빗자루", EITEM_TYPE::Tool });
	ItemData::CreateData("Item_Etc_12", { "Item_Etc_12", "잠자리채", EITEM_TYPE::Tool });



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
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "몽시리", "Mongsiri_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day, 
		{ {EBIOLOGYDESCTYPE::Observation, "굴을 파고 생활하며 2~4마리가 같은 굴에서 산다. 호기심이 많아 사람이 가까이 오면 먼저 다가간다."},{EBIOLOGYDESCTYPE::Method, "편안한 그립감을 주는 볼을 잡고 늘리면 보송보송한 털이 자연스레 손에 남아 있다."} } });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "호박 강아지", "PumpkinTerrier_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay, 
		{ {EBIOLOGYDESCTYPE::Observation, "'호박류'의 식물을 먹고 산다. 재생력이 강한 호박 덩굴에 몸이 감싸여 있는 경우가 많다."},{EBIOLOGYDESCTYPE::Method, "놀이를 좋아해서, 채집을 시도하면 술래잡기를 하려 한다."}, {EBIOLOGYDESCTYPE::Extra, "본래의 모습이 궁금하다면 감싸고 있는 덩굴을 모두 제거해보자."} } });
	BiologyData::CreateData("BushBug", { "BushBug", "덤불 깨비", "BushBug_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay, 
		{ {EBIOLOGYDESCTYPE::Observation, "덤불 안에 집을 짓고 산다. 작은 몸집에 맞지 않는 커다란 날개를 가지고 있다."},{EBIOLOGYDESCTYPE::Method, "움직이는 덤불을 본다면, 힘차게 흔들어보자. 일단 발견하면 채집하는 것은 어렵지 않다."} } });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "새싹새", "FlowerBird_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day, 
		{ {EBIOLOGYDESCTYPE::Observation, "초록숲 어디서나 볼 수 있는 흔한 새."},{EBIOLOGYDESCTYPE::Method, "머리 위의 싹은 시들거나 꽃을 피운다. 꽃을 피울 때, 놀래키면 꽃을 떨어트린다."},{EBIOLOGYDESCTYPE::Extra, "영양을 잘 섭취한 경우에는, 꽃을 많이 피우기도 한다."} } });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "푸른 방울 도마뱀", "BubbleLizard_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day, 
		{ {EBIOLOGYDESCTYPE::Observation, "날씨가 좋으면 연못 밖으로 나와 햇볕을 쬐어 일광욕을 한다. 맹한 표정으로 침을 흘리는 모습이 인기가 좋다."},{EBIOLOGYDESCTYPE::Method, "배를 만져주면 굉장히 좋아한다. 기분이 좋을 때 내뿜는 단단한 방울은 재료로 사용된다."} } });

	// 식물
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "마녀꽃", "WitchFlower_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay, 
		{ {EBIOLOGYDESCTYPE::Observation, "마녀가 무언가 만들 때 많이 사용하기 때문에, 마녀 꽃이라는 이름이 붙여졌다."},{EBIOLOGYDESCTYPE::Method, "다가가서 줄기를 잡고 가볍게 힘을 주면, 쑥 뽑혀 나온다."} } });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "은별방울꽃", "SilverStarFlower_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night, 
		{ {EBIOLOGYDESCTYPE::Observation, "은색 종 모양의 꽃은 실제 종처럼 은은한 소리를 낸다. 퍼지는 종소리는 어쩐지 서글픈 마음을 불러 일으킨다."},{EBIOLOGYDESCTYPE::Method, "밤에 빛을 내고 있을 때 부딧히면, 봉오리가 열리며 꽃가루가 흩뿌려진다."} } });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "단풍 허브", "MapleHerb_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay , 
		{ {EBIOLOGYDESCTYPE::Observation, "절벽에 뿌리를 내리고 자라는 붉은색을 허브, 겁쟁이 풀이라고도 불리는데, 아이들이 담력 시험의 일환으로 풀을 따기 때문이다."},{EBIOLOGYDESCTYPE::Method, "땅에 자라는 식물과 달리 뿌리를 사방으로 뻗어 있기 때문에, 위로 잡아 뽑기 보다는 좌우로 흔들면서 뽑는 것이 좋다."} } });


	// 물약
	std::string BadGrassPotionContent = "마녀들이 정원을 관리할 때 주로 사용하게 되는 물약이다. 만들 때 '나쁜 풀'에 대해 잘 생각하지 않으면 맛없는 야채들이 함께 사라지는 대참사가 벌어질 수도 있다.";
	std::string NutritionPotionContent = "대상에게 순간 다량의 영양분을 공급한다. 초보 원예가들에게 한 줄기 빛이 되는 듯 했으나, 지속 시간이 지난 후에 다시 시드는 식물들은 그들에게 더 큰 좌절감만 안겨줬다는 후문이 있다.";
	std::string FirecrackerPotionContent = "알아서 높이 날아올라 일정 높이 이상이 되면 터지면서 아름다운 불꽃으로 장관을 만드는 물약이다.";
	ProductRecipeData::CreateData("BadGrassPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"WitchFlower_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "BadGrassPotion", "나쁜 풀 제거 물약", BadGrassPotionContent });
	ProductRecipeData::CreateData("NutritionPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1}, {"MapleHerb_Water", 1 },{"BushBug_Water", 1  }}, EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "NutritionPotion", "영양 공급 물약", NutritionPotionContent });
	ProductRecipeData::CreateData("FirecrackerPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1,}, { "FlowerBird_Water", 1 },{"BushBug_Water", 1} }, EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirLeft, EBREWING_FIRE::Two, "FirecrackerPotion", "폭죽 물약", FirecrackerPotionContent });
	

	// 사탕
	std::string UncurseCandyContent = "양치 한 걸 까먹게하는 저주, 자주 넘어지게 하는 저주 등 가벼운 저주를 풀 수 있는 사탕이다. 달콤한 박하맛이 맛있다.";
	std::string HealingCandyContent = "무릎 까진거, 손가락 살짝 베인거, 가시 박힌거 정도는 치료해주는 사탕이다. 어린아이들을 위한 박하맛이 가미된 사탕이다. 중독성이 있기 때문에 반드시 양철통에 넣어 높은 서랍에 보관할 것.";
	ProductRecipeData::CreateData("UncurseCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three,  "UncurseCandy", "저주해제 사탕", UncurseCandyContent });
	ProductRecipeData::CreateData("HealingCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"WitchFlower_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "HealingCandy", "치료 사탕", HealingCandyContent });

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
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Blend_Alight", Desc);
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

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ContentsLight2DTexture");
		Mat->SetVertexShader("GaugeShader_VS");
		Mat->SetPixelShader("GaugeShader_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetBlendState("Blend_Alight");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("Light2DTexture");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetBlendState("Blend_Alight");
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