#include "PreCompile.h"
#include "UI_Dictionary.h"

#include "UIManager.h"
#include "UI_BiologyPage.h"
#include "UI_ProductPage.h"

EDICTIONARYCATEGORY UI_Dictionary::g_CurrentCategory = EDICTIONARYCATEGORY::None;
int UI_Dictionary::g_CurrentLeftPage = 0;
UI_Dictionary::UI_Dictionary() 
{
}

UI_Dictionary::~UI_Dictionary() 
{
}


void UI_Dictionary::Start()
{
	UI_ToggleActor::Start();
}

void UI_Dictionary::Update(float _Delta)
{
	if (false == OnLevelStartCheck)
	{
		OnLevelStart();
		OnLevelStartCheck = true;
	}

	UI_ToggleActor::Update(_Delta);

	UpdateDictionary();
}

void UI_Dictionary::OnLevelStart()
{
	ChangeCategoryMark();
}

void UI_Dictionary::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Dictionary::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);

	OffCategoryMark();
	OnLevelStartCheck = false;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//
// �̴ϼ�

#pragma region �̴ϼ�

// ������ �������� �����մϴ�.
void UI_Dictionary::Init()
{
	// Base
	CreateBase();

	// Category
	CreateCategory();

	// CreaturePage
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "Mongsiri");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "PumpkinTerrier");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "BushBug");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "FlowerBird");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "BubbleLizard");

	// PlantPage
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "WitchFlower");
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "SilverStarFlower");
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "MapleHerb");



	// PotionPage
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "BadGrassPotion");
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "NutritionPotion");
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "FirecrackerPotion");

	// CandyPage
	CreatePage(EDICTIONARYCATEGORY::CandyPage, "UncurseCandy");
	CreatePage(EDICTIONARYCATEGORY::CandyPage, "HealingCandy");

	if (EDICTIONARYCATEGORY::None == g_CurrentCategory)
	{
		g_CurrentCategory = EDICTIONARYCATEGORY::CreaturePage;

		g_CurrentLeftPage = 1;
	}

	ChangeCategoryMark();
}


// å ����
void UI_Dictionary::CreateBase()
{
	// Base
	m_BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_BaseRenderer)
	{
		MsgBoxAssert("Base�� �������� ���߽��ϴ�.");
		return;
	}

	float ZOrder = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base);
	m_BaseRenderer->Transform.SetLocalPosition({ 0.0f , 0.0f, ZOrder });
	m_BaseRenderer->SetSprite("Base.png");
}

// ī�װ� ����
void UI_Dictionary::CreateCategory()
{
	float4 SetLocalPos = float4{ -345.0f , 128.0f };

	m_CategoryRenderer.Creature = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_CategoryRenderer.Creature)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Creature->SetSprite("Tag_Creature_Normal.png");
	m_CategoryRenderer.Creature->SetPivotType(PivotType::Right);

	SetLocalPos.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	m_CategoryRenderer.Creature->Transform.SetLocalPosition(SetLocalPos);

	std::shared_ptr<GameEngineTexture> CreatureTexture = GameEngineTexture::Find("Tag_Creature_Normal.png");
	if (nullptr == CreatureTexture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 HTextureScale = CreatureTexture->GetScale().Half();
	SetLocalPos.Y -= HTextureScale.Y + CategoryGap;


	std::shared_ptr<GameEngineTexture> PlantTexture = GameEngineTexture::Find("Tag_Plant_Normal.png");
	if (nullptr == PlantTexture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HTextureScale = PlantTexture->GetScale().Half();
	SetLocalPos.Y -= HTextureScale.Y;


	m_CategoryRenderer.Plant = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_CategoryRenderer.Plant)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Plant->SetSprite("Tag_Plant_Normal.png");
	m_CategoryRenderer.Plant->SetPivotType(PivotType::Right);

	SetLocalPos.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	m_CategoryRenderer.Plant->Transform.SetLocalPosition(SetLocalPos);

	SetLocalPos.Y -= HTextureScale.Y + CategoryGap;


	std::shared_ptr<GameEngineTexture> PotionTexture = GameEngineTexture::Find("Tag_Potion_Normal.png");
	if (nullptr == PotionTexture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HTextureScale = PotionTexture->GetScale().Half();
	SetLocalPos.Y -= HTextureScale.Y;


	m_CategoryRenderer.Potion = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_CategoryRenderer.Potion)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Potion->SetSprite("Tag_Potion_Normal.png");
	m_CategoryRenderer.Potion->SetPivotType(PivotType::Right);

	SetLocalPos.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	m_CategoryRenderer.Potion->Transform.SetLocalPosition(SetLocalPos);

	SetLocalPos.Y -= HTextureScale.Y + CategoryGap;



	std::shared_ptr<GameEngineTexture> CandyTexture = GameEngineTexture::Find("Tag_Candy_Normal.png");
	if (nullptr == CandyTexture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HTextureScale = CandyTexture->GetScale().Half();
	SetLocalPos.Y -= HTextureScale.Y;


	m_CategoryRenderer.Candy = CreateComponent<GameEngineUIRenderer>();
	if (nullptr == m_CategoryRenderer.Candy)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}
	 
	m_CategoryRenderer.Candy->SetSprite("Tag_Candy_Normal.png");
	m_CategoryRenderer.Candy->SetPivotType(PivotType::Right);

	SetLocalPos.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	m_CategoryRenderer.Candy->Transform.SetLocalPosition(SetLocalPos);
}

// ī�װ� �������� �߰��մϴ�.
void UI_Dictionary::CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}
	
	switch (_Type)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		std::shared_ptr<UI_BiologyPage> Page = CurLevel->CreateActor<UI_BiologyPage>(EUPDATEORDER::UIComponent);
		if (nullptr == Page)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Page->CreatePage(Name, m_CreaturePageCount);
		vecCreaturePage.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		std::shared_ptr<UI_BiologyPage> Page = CurLevel->CreateActor<UI_BiologyPage>(EUPDATEORDER::UIComponent);
		if (nullptr == Page)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Page->CreatePage(Name, m_PlantPageCount);
		vecPlantPage.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		std::shared_ptr<UI_ProductPage> Page = CurLevel->CreateActor<UI_ProductPage>(EUPDATEORDER::UIComponent);
		if (nullptr == Page)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Page->CreatePage(Name, m_PotionPageCount);
		vecPotionPage.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		std::shared_ptr<UI_ProductPage> Page = CurLevel->CreateActor<UI_ProductPage>(EUPDATEORDER::UIComponent);
		if (nullptr == Page)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		Page->CreatePage(Name, m_CandyPageCount);
		vecCandyPage.push_back(Page);
	}
		break;
	default:
		break;
	}
}

#pragma endregion


// �θ��� Open�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::OpenInternal()
{
	OpenNextPage(g_CurrentCategory);
}

// �θ��� Close�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::CloseInternal()
{
	CloseCurrentPage(g_CurrentCategory);
}



// ���� ���� ��Ĩ�ϴ�.
void UI_Dictionary::OpenNextPage(EDICTIONARYCATEGORY _Type)
{
	if (g_CurrentLeftPage < 1)
	{
		MsgBoxAssert("0�������� �������� �ʽ��ϴ�.");
		return;
	}

	// OpenPage�� 2�� ������ 3,4 �������� �����ϴ�.
	int OpenPage = g_CurrentLeftPage - 1;

	switch (g_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
	{
		MsgBoxAssert("���� ī�װ��δ� ������ �Ұ����մϴ�.");
		return;
	}
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		std::shared_ptr<UI_BiologyPage> OddPage = vecCreaturePage[OpenPage++];
		if (nullptr == OddPage)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
			return;
		}

		OddPage->On();

		// ���� �������� ������ Ȧ���� ���ɴϴ�.
		// ������ �������� ���� �������� ���ٸ� ������ ����ִٴ� ������ �� ������ �����Ű�� �ʽ��ϴ�.
		if (g_CurrentLeftPage != m_CreaturePageCount)
		{
			std::shared_ptr<UI_BiologyPage> EvenPage = vecCreaturePage[OpenPage];
			if (nullptr == EvenPage)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
				return;
			}

			EvenPage->On();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		std::shared_ptr<UI_BiologyPage> OddPage = vecPlantPage[OpenPage++];
		if (nullptr == OddPage)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
			return;
		}

		OddPage->On();

		// ���� �������� ������ Ȧ���� ���ɴϴ�.
		// ������ �������� ���� �������� ���ٸ� ������ ����ִٴ� ������ �� ������ �����Ű�� �ʽ��ϴ�.
		if (g_CurrentLeftPage != m_PlantPageCount)
		{
			std::shared_ptr<UI_BiologyPage> EvenPage = vecPlantPage[OpenPage];
			if (nullptr == EvenPage)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
				return;
			}

			EvenPage->On();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		OpenPage /= 2;
		std::shared_ptr<UI_ProductPage> Page = vecPotionPage[OpenPage];
		if (nullptr == Page)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
			return;
		}

		Page->On();
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		OpenPage /= 2;
		std::shared_ptr<UI_ProductPage> Page = vecCandyPage[OpenPage];
		if (nullptr == Page)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����߽��ϴ�.");
			return;
		}

		Page->On();
	}
		break;
	default:
		break;
	}
}

// Ư�� ī�װ� �������� ���ϴ�.
void UI_Dictionary::CloseCurrentPage(EDICTIONARYCATEGORY _Type)
{
	switch (_Type)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		for (size_t i = 0; i < vecCreaturePage.size(); i++)
		{
			std::shared_ptr<UI_BiologyPage> Object = vecCreaturePage[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("���� �迭�� �������� �ʴ� ���Ͱ� �ֽ��ϴ�.");
				return;
			}

			Object->Off();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		for (size_t i = 0; i < vecPlantPage.size(); i++)
		{
			std::shared_ptr<UI_BiologyPage> Object = vecPlantPage[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("���� �迭�� �������� �ʴ� ���Ͱ� �ֽ��ϴ�.");
				return;
			}

			Object->Off();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		for (size_t i = 0; i < vecPotionPage.size(); i++)
		{
			std::shared_ptr<UI_ProductPage> Object = vecPotionPage[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("���� �迭�� �������� �ʴ� ���Ͱ� �ֽ��ϴ�.");
				return;
			}

			Object->Off();
		}
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		for (size_t i = 0; i < vecCandyPage.size(); i++)
		{
			std::shared_ptr<UI_ProductPage> Object = vecCandyPage[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("���� �迭�� �������� �ʴ� ���Ͱ� �ֽ��ϴ�.");
				return;
			}

			Object->Off();
		}
	}
		break;
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
// 
// ������Ʈ

void UI_Dictionary::UpdateDictionary()
{
	if (true == CheckOpenDictionary())
	{
		return;
	}
	
	if (true == CheckTurningPage())
	{
		return;
	}

	if (true == CheckMoveCategory())
	{
		return;
	}
}

// ������ ���ȴ��� �����մϴ�.
bool UI_Dictionary::CheckOpenDictionary()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('D', this))
		{
			Close();
			return true;
		}
	}

	OpenCheck = false;
	return false;
}


// ī�װ� ��ȯ�� �����մϴ�.
bool UI_Dictionary::CheckMoveCategory()
{
	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		NextCategory();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		PrevCategory();
		return true;
	}

	return false;
}

// �������� �ѰŰ��� ���� �����մϴ�.
bool UI_Dictionary::CheckTurningPage()
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		PrevPage();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		NextPage();
		return true;
	}

	return false;
}

// �������� ���������� �Ѿ�ϴ�.
void UI_Dictionary::NextPage()
{
	// SFX

	int MaxPage = -1;

	switch (g_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
	{
		MsgBoxAssert("None�� ���� �� �����ϴ�.");
		return;
	}
	break;
	case EDICTIONARYCATEGORY::CreaturePage:
		MaxPage = m_CreaturePageCount;
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		MaxPage = m_PlantPageCount;
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		MaxPage = m_PotionPageCount;
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		MaxPage = m_CandyPageCount;
		break;
	default:
		break;
	}

	if (g_CurrentLeftPage == MaxPage || g_CurrentLeftPage + 1 == MaxPage)
	{
		return;
	}

	g_CurrentLeftPage += 2;

	CloseCurrentPage(g_CurrentCategory);
	OpenNextPage(g_CurrentCategory);
}

// �������� ���������� �Ѿ�ϴ�.
void UI_Dictionary::PrevPage()
{
	// SFX

	if (g_CurrentLeftPage <= 2)
	{
		return;
	}

	g_CurrentLeftPage -= 2;

	CloseCurrentPage(g_CurrentCategory);
	OpenNextPage(g_CurrentCategory);
}



// ���� ī�װ��� ���ư��ϴ�.
void UI_Dictionary::PrevCategory()
{
	// ���� ī�װ� �ݰ�
	OffCategoryMark();
	CloseCurrentPage(g_CurrentCategory);

	// ���� ��
	int CurCategory = static_cast<int>(g_CurrentCategory);
	--CurCategory;
	if (0 == CurCategory)
	{
		CurCategory = 4;
	}

	g_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	// ���� �������� ������ 1�� �ʱ�ȭ
	g_CurrentLeftPage = 1;

	// ����.
	OpenNextPage(g_CurrentCategory);
	ChangeCategoryMark();
}

// ���� ī�װ��� �̵��մϴ�.
void UI_Dictionary::NextCategory()
{
	// ���� ī�װ� �ݰ�
	OffCategoryMark();
	CloseCurrentPage(g_CurrentCategory);

	// ���� ��
	int CurCategory = static_cast<int>(g_CurrentCategory);
	++CurCategory;
	if (5 == CurCategory)
	{
		CurCategory = 1;
	}

	g_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	// ���� �������� ������ 1�� �ʱ�ȭ
	g_CurrentLeftPage = 1;

	// ����.
	OpenNextPage(g_CurrentCategory);
	ChangeCategoryMark();
};

// ī�װ� å���̸� �����մϴ�
void UI_Dictionary::OffCategoryMark()
{
	switch (g_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
		if (nullptr == m_CategoryRenderer.Creature)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Creature->SetSprite("Tag_Creature_Normal.png");
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		if (nullptr == m_CategoryRenderer.Plant)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Plant->SetSprite("Tag_Plant_Normal.png");
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		if (nullptr == m_CategoryRenderer.Potion)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Potion->SetSprite("Tag_Potion_Normal.png");
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		if (nullptr == m_CategoryRenderer.Candy)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Candy->SetSprite("Tag_Candy_Normal.png");
		break;
	default:
		break;
	}
}

// ī�װ� å���̸� �����մϴ�.
void UI_Dictionary::ChangeCategoryMark()
{
	switch (g_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
		if (nullptr == m_CategoryRenderer.Creature)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Creature->SetSprite("Tag_Creature_Selected.png");
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		if (nullptr == m_CategoryRenderer.Plant)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Plant->SetSprite("Tag_Plant_Selected.png");
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		if (nullptr == m_CategoryRenderer.Potion)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Potion->SetSprite("Tag_Potion_Selected.png");
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		if (nullptr == m_CategoryRenderer.Candy)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�");
			return;
		}

		m_CategoryRenderer.Candy->SetSprite("Tag_Candy_Selected.png");
		break;
	default:
		break;
	}
}