#include "PreCompile.h"
#include "UI_Dictionary.h"

#include "ItemInfo.h"
#include "UI_BiologyPage.h"

EDICTIONARYCATEGORY UI_Dictionary::g_CurrentCategory = EDICTIONARYCATEGORY::None;
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
	UI_ToggleActor::Update(_Delta);

	UpdateDictionary();
}

void UI_Dictionary::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Dictionary::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
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



	g_CurrentCategory = EDICTIONARYCATEGORY::CreaturePage;
	m_CurrentLeftPage = 1;
}


// å ����
void UI_Dictionary::CreateBase()
{
	// Base
	m_BaseRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Base);
	if (nullptr == m_BaseRenderer)
	{
		MsgBoxAssert("Base�� �������� ���߽��ϴ�.");
		return;
	}

	m_BaseRenderer->SetSprite("Base.png");
}

// ī�װ� ����
void UI_Dictionary::CreateCategory()
{
	float4 SetLocalPos = float4{ -345.0f , 128.0f };

	m_CategoryRenderer.Creature = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	if (nullptr == m_CategoryRenderer.Creature)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Creature->SetSprite("Tag_Creature_Normal.png");
	m_CategoryRenderer.Creature->SetPivotType(PivotType::Right);
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


	m_CategoryRenderer.Plant = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	if (nullptr == m_CategoryRenderer.Plant)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Plant->SetSprite("Tag_Plant_Normal.png");
	m_CategoryRenderer.Plant->SetPivotType(PivotType::Right);
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


	m_CategoryRenderer.Potion = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	if (nullptr == m_CategoryRenderer.Potion)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Potion->SetSprite("Tag_Potion_Normal.png");
	m_CategoryRenderer.Potion->SetPivotType(PivotType::Right);
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


	m_CategoryRenderer.Candy = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	if (nullptr == m_CategoryRenderer.Candy)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_CategoryRenderer.Candy->SetSprite("Tag_Candy_Normal.png");
	m_CategoryRenderer.Candy->SetPivotType(PivotType::Right);
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
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		break;
	default:
		break;
	}
}

#pragma endregion



// �θ��� Open�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::OpenChild()
{
	OpenCategoryPage(g_CurrentCategory);
}

// �θ��� Close�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::CloseChild()
{
	CloseCategoryPage(g_CurrentCategory);
}




void UI_Dictionary::OpenCategoryPage(EDICTIONARYCATEGORY _Type)
{
	if (m_CurrentLeftPage < 1)
	{
		MsgBoxAssert("0�������� �������� �ʽ��ϴ�.");
		return;
	}

	// 2�� ������ 3,4 �������� �����ϴ�.
	int OpenPage = m_CurrentLeftPage - 1;

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
		if (m_CurrentLeftPage != m_CreaturePageCount)
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
		if (m_CurrentLeftPage != m_PlantPageCount)
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
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		break;
	default:
		break;
	}
}

// Ư�� ī�װ� �������� ���ϴ�.
void UI_Dictionary::CloseCategoryPage(EDICTIONARYCATEGORY _Type)
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
		break;
	case EDICTIONARYCATEGORY::CandyPage:
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
		if (true == GameEngineInput::IsDown('D'))
		{
			Close();
			return true;
		}
	}

	OpenCheck = false;
	return false;
}

// �������� �ѰŰ��� ���� �����մϴ�.
bool UI_Dictionary::CheckTurningPage()
{
	if (true == GameEngineInput::IsDown(VK_LEFT))
	{
		PrevPage();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT))
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
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		break;
	default:
		break;
	}

	if (m_CurrentLeftPage == MaxPage || m_CurrentLeftPage + 1 == MaxPage)
	{
		return;
	}

	m_CurrentLeftPage += 2;

	CloseCategoryPage(g_CurrentCategory);
	OpenCategoryPage(g_CurrentCategory);
}

// �������� ���������� �Ѿ�ϴ�.
void UI_Dictionary::PrevPage()
{
	// SFX

	if (m_CurrentLeftPage <= 2)
	{
		return;
	}

	m_CurrentLeftPage -= 2;

	CloseCategoryPage(g_CurrentCategory);
	OpenCategoryPage(g_CurrentCategory);
}


// ī�װ� ��ȯ�� �����մϴ�.
bool UI_Dictionary::CheckMoveCategory()
{
	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		NextCategory();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		PrevCategory();
		return true;
	}



	return false;
}


void UI_Dictionary::PrevCategory()
{
	// ���� ī�װ� �ݰ�
	OffCategoryMark();
	CloseCategoryPage(g_CurrentCategory);

	// ���� ��
	int CurCategory = static_cast<int>(g_CurrentCategory);
	--CurCategory;
	if (0 == CurCategory)
	{
		CurCategory = 4;
	}

	g_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	// ���� �������� ������ 1�� �ʱ�ȭ
	m_CurrentLeftPage = 1;

	// ����.
	OpenCategoryPage(g_CurrentCategory);
	ChangeCategoryMark();
}

void UI_Dictionary::NextCategory()
{
	// ���� ī�װ� �ݰ�
	OffCategoryMark();
	CloseCategoryPage(g_CurrentCategory);

	// ���� ��
	int CurCategory = static_cast<int>(g_CurrentCategory);
	++CurCategory;
	if (5 == CurCategory)
	{
		CurCategory = 1;
	}

	g_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	// ���� �������� ������ 1�� �ʱ�ȭ
	m_CurrentLeftPage = 1;

	// ����.
	OpenCategoryPage(g_CurrentCategory);
	ChangeCategoryMark();
};


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