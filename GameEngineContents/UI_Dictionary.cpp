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
// 이니셜

// 사전의 페이지를 생성합니다.
void UI_Dictionary::Init()
{
	// Base
	m_BaseRenderer = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Base);
	if (nullptr == m_BaseRenderer)
	{
		MsgBoxAssert("Base를 생성하지 못했습니다.");
		return;
	}

	m_BaseRenderer->SetSprite("Base.png");

	// CreaturePage
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "Mongsiri");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "PumpkinTerrier");

	m_CurrentCategory = EDICTIONARYCATEGORY::CreaturePage;
}


// 카테고리 페이지를 추가합니다.
void UI_Dictionary::CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
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
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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

// 부모의 Open함수에 자식에서 해줘야할 행동을 선언합니다.
void UI_Dictionary::OpenChild()
{
	if (-1 == m_CurrentPage)
	{
		MsgBoxAssert("0페이지는 존재하지 않습니다.");
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
			MsgBoxAssert("존재하지 않는 벡터를 참조했습니다.");
			return;
		}

		OddPage->On();

		// 페이지가 짝수라면 양쪽페이지
		if (0 == m_CreaturePageCount % 2)
		{
			std::shared_ptr<UI_BiologyPage> EvenPage = vecCreaturePage[OpenPage];
			if (nullptr == EvenPage)
			{
				MsgBoxAssert("존재하지 않는 벡터를 참조했습니다.");
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
			MsgBoxAssert("존재하지 않는 벡터를 참조했습니다.");
			return;
		}

		OddPage->On();

		// 페이지가 짝수라면 양쪽페이지
		if (0 == m_PlantPageCount % 2)
		{
			std::shared_ptr<UI_BiologyPage> EvenPage = vecPlantPage[OpenPage];
			if (nullptr == EvenPage)
			{
				MsgBoxAssert("존재하지 않는 벡터를 참조했습니다.");
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

// 부모의 Close함수에 자식에서 해줘야할 행동을 선언합니다.
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
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
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
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
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
// 업데이트

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

// 사전이 열렸는지 감지합니다.
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