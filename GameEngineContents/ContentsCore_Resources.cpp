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
		// �÷��� ����
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// ũ��ó
		GlobalUtils::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// ��
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// �ٸ�
		GlobalUtils::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// ���ڷ�
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

	// ������
	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "���ø���", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "���ø���", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "������ ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "��", EITEM_TYPE::Ingredient});

	// ������� 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "��������", EITEM_TYPE::RepairMaterial });

	// ����
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "���ø���", EITEM_TYPE::Food });



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
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "���ø�", "���ø���", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "ȣ�� ������", "ȣ�� �������� �� ����", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("BushBug", { "BushBug", "���� ����", "���� ����", ETOOLTYPE::FeaturePan, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "���ϻ�", "����", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "Ǫ�� ��� ������", "�������", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day });

	// �Ĺ�
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "�����", "����� �Ѹ�", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "��������", "�������� ����", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "��ǳ ���", "��ǳ ���", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay });

	// ����
	ProductRecipeData::CreateData("BadGrassPotion", { "BadGrassPotion", "���� Ǯ ���� ����", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Four, "Mongsiri_Water", 2, "WitchFlower_Water", 2 });
	ProductRecipeData::CreateData("NutritionPotion", { "NutritionPotion", "Ǯ ���� ����", EBREWINGOPTION::Normal, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "SilverStarFlower_Water", 2, "MapleHerb_Water", 2, "BushBug_Water", 2 });
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "�Ҳɳ��� ����", EBREWINGOPTION::Hard, EBREWINGOPTION::StirRight, EBREWINGOPTION::Three, "PumpkinTerrier_Powder", 2, "FlowerBird_Water", 2, "MoonButterfly_Water", 2 });

	// ����
	ProductRecipeData::CreateData("UncurseCandy", { "UncurseCandy", "��ǳ ���", EBREWINGOPTION::Easy, EBREWINGOPTION::StirNone, EBREWINGOPTION::Three, "Mongsiri_Water", 2, "MapleHerb_Water", 2 });
	ProductRecipeData::CreateData("HealingCandy", { "HealingCandy", "ġ�� ����", EBREWINGOPTION::Easy, EBREWINGOPTION::StirRight, EBREWINGOPTION::Four, "WitchFlower_Water", 2, "MapleHerb_Water", 2 });
}
