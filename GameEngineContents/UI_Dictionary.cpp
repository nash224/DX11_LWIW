#include "PreCompile.h"
#include "UI_Dictionary.h"

#include "ItemInfo.h"
#include "UI_BiologyPage.h"

EDICTIONARYCATEGORY UI_Dictionary::m_CurrentCategory = EDICTIONARYCATEGORY::None;
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

// ������ �������� �����մϴ�.
void UI_Dictionary::Init()
{
	// Base
	m_BaseRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Base);
	if (nullptr == m_BaseRenderer)
	{
		MsgBoxAssert("Base�� �������� ���߽��ϴ�.");
		return;
	}

	m_BaseRenderer->SetSprite("Base.png");

	// CreaturePage
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "Mongsiri");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "PumpkinTerrier");

	m_CurrentCategory = EDICTIONARYCATEGORY::CreaturePage;
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

// �θ��� Open�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::OpenChild()
{
	if (-1 == m_CurrentPage)
	{
		MsgBoxAssert("0�������� �������� �ʽ��ϴ�.");
		return;
	}

	int OpenPage = (m_CurrentPage - 1) / 2;

	switch (m_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
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

		// �������� ¦����� ����������
		if (0 == m_CreaturePageCount % 2)
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

		// �������� ¦����� ����������
		if (0 == m_PlantPageCount % 2)
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

// �θ��� Close�Լ��� �ڽĿ��� ������� �ൿ�� �����մϴ�.
void UI_Dictionary::CloseChild()
{
	switch (m_CurrentCategory)
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
		for (size_t i = 0; i < vecCreaturePage.size(); i++)
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

void UI_Dictionary::NextPage()
{

}

void UI_Dictionary::PrevPage()
{

}



bool UI_Dictionary::CheckMoveCategory()
{
	if (true == GameEngineInput::IsDown(VK_UP))
	{
		PrevCategory();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		NextCategory();
		return true;
	}



	return false;
}

void UI_Dictionary::PrevCategory()
{

}

void UI_Dictionary::NextCategory()
{

}