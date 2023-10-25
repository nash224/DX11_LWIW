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
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "������ ����", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "���ø� ����", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "��Ǯ���� ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "������ ��� ����", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Water", { "SilverStarFlower_Water", "�ǹ��� ����", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "���ø���", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "���ø���", EITEM_TYPE::Ingredient });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "������ ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "��", EITEM_TYPE::Ingredient});

	// ����
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "���� Ǯ ���Ź���", EITEM_TYPE::Ingredient});

	// ������� 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "��������", EITEM_TYPE::RepairMaterial });

	// ����
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "���ø���", EITEM_TYPE::Food });



	// ��� ����
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "���ø���", "Mongsiri_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "ȣ�� ������ �� �Ŀ��", "PumpkinTerrier_Collect", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug_Water", { "BushBug_Water", "���� ������", "BushBug_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "������", "FlowerBird_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "���������", "BubbleLizard_Collect", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "�������", "WitchFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "����������", "SilverStarFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "��ǳ �����", "MapleHerb_Collect", EBrewingMachineType::Extractor, 2 });

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
	ProductRecipeData::CreateData("BadGrassPotion", { "BadGrassPotion", "���� Ǯ ���� ����", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "Mongsiri_Water", 1, "WitchFlower_Water", 1 });
	ProductRecipeData::CreateData("NutritionPotion", { "NutritionPotion", "Ǯ ���� ����", EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "SilverStarFlower_Water", 1, "MapleHerb_Water", 1, "BushBug_Water", 1 });
	ProductRecipeData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "�Ҳɳ��� ����", EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "PumpkinTerrier_Powder", 1, "FlowerBird_Water", 1, "MoonButterfly_Water", 1 });

	// ����
	ProductRecipeData::CreateData("UncurseCandy", { "UncurseCandy", "��ǳ ���", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three, "Mongsiri_Water", 1, "MapleHerb_Water", 1 });
	ProductRecipeData::CreateData("HealingCandy", { "HealingCandy", "ġ�� ����", EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "WitchFlower_Water", 1, "MapleHerb_Water", 1 });
}



void ContentsCore::InitBlendResources()
{
	D3D11_BLEND_DESC Desc = {};

	// ����Ÿ�ٴ� ���� �ɼ��� ���� �����Ҳ���
	Desc.IndependentBlendEnable = false;

	// ����Ÿ�� 0�� 
	// ���� ���
	Desc.RenderTarget[0].BlendEnable = true;

	// ���� ��ü�� ������� ��ڴ�.
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ���� ���Ѵ�
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_blend

	// src srcColor * src�� ����
	// 1, 0, 0(, 1) * 1.0f
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src����

	// src 1, 0, 0, 1 * (1 - src�� ����)
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;	// ���� ���ϴµ�
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;	// �ҽ��� ��������
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;	// ������ ����

	std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("Overlay", Desc);
}