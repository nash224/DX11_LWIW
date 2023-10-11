#include "PreCompile.h"
#include "UI_BiologyPage.h"


#include "BiologyData.h"

UI_BiologyPage::UI_BiologyPage()
{
}

UI_BiologyPage::~UI_BiologyPage()
{
}


void UI_BiologyPage::Start()
{

}

void UI_BiologyPage::Update(float _Delta)
{

}

void UI_BiologyPage::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_BiologyPage::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 페이지를 생성해줍니다.
void UI_BiologyPage::CreatePage(std::string_view _BiologyName, int& PageCount)
{
	++PageCount;
	
	float4 MovePage = { -176.0f , 0.0f };

	// 짝수라면
	if (0 == PageCount % 2)
	{
		MovePage.X *= -1.0f;
	}

	Transform.AddLocalPosition(MovePage);

	const std::shared_ptr<BiologyData>& Data = BiologyData::Find(_BiologyName);

	std::string Name = Data->BiologyName;

	m_BiologyPageComposition.NameTag = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Attachment);
	m_BiologyPageComposition.NameTag->SetSprite("CreatureName.png");
	m_BiologyPageComposition.NameTag->Transform.SetLocalPosition({ -70.0f + 71.0f , 154.0f - 13.0f });

	m_BiologyPageComposition.Photo = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Attachment);
	m_BiologyPageComposition.Photo->SetSprite("Photo.png");
	m_BiologyPageComposition.Photo->Transform.SetLocalPosition({ -148.0f + 64.0f , 113.0f - 64.0f });

	m_BiologyPageComposition.Frame = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Frame);
	m_BiologyPageComposition.Frame->SetSprite("Base_LayoutLine_1.png");
	m_BiologyPageComposition.Frame->Transform.SetLocalPosition({ -138.0f + 138.0f , -28.0f - 1.0f });

	m_BiologyPageComposition.Illustration = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.Illustration->SetSprite(Name + "_Illustration.png");
	m_BiologyPageComposition.Illustration->Transform.SetLocalPosition({ -148.0f + 64.0f , 113.0f - 64.0f });

	m_BiologyPageComposition.Slot1 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.Slot1->SetSprite(ReturnEcologyTypeFileName(Data->EcologicalGroup));
	m_BiologyPageComposition.Slot1->Transform.SetLocalPosition({ -11.0f + 20.0f , 112.0f - 20.0f });

	m_BiologyPageComposition.Slot2 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.Slot2->SetSprite(ReturnEcologyTypeFileName(Data->Habitat));
	m_BiologyPageComposition.Slot2->Transform.SetLocalPosition({ 37.0f + 20.0f , 112.0f - 20.0f });

	m_BiologyPageComposition.Slot3 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.Slot3->SetSprite(ReturnEcologyTypeFileName(Data->AppearanceTime));
	m_BiologyPageComposition.Slot3->Transform.SetLocalPosition({ 85.0f + 20.0f , 112.0f - 20.0f });

	m_BiologyPageComposition.Tool = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.Tool->SetSprite("Tool_Icon.png", static_cast<int>(Data->GatherTool));
	m_BiologyPageComposition.Tool->Transform.SetLocalPosition({ -10.0f + 20.0f , 60.0f - 20.0f });

	m_BiologyPageComposition.ItemSpace = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Attachment);
	m_BiologyPageComposition.ItemSpace->SetSprite("Inventory_Empty_Slot.png");
	m_BiologyPageComposition.ItemSpace->Transform.SetLocalPosition({ -11.0f + 20.0f , 17.0f - 20.0f });

	m_BiologyPageComposition.ItemImg = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Component);
	m_BiologyPageComposition.ItemImg->SetSprite(Data->BiologyName + "_Collect.png");
	m_BiologyPageComposition.ItemImg->Transform.SetLocalPosition({ -11.0f + 20.0f , 17.0f - 20.0f });

	Off();
}


// 생태계 타입별로 파일명을 반환해줍니다.
std::string UI_BiologyPage::ReturnEcologyTypeFileName(EECOLOGYTYPE _Type)
{
	std::string TypeName = "IllustedBook_Ecology_";

	switch (_Type)
	{
	case EECOLOGYTYPE::None:
		TypeName += "Empty";
		break;
	case EECOLOGYTYPE::GreenForest:
		TypeName += "GreenForest";
		break;
	case EECOLOGYTYPE::ForestPlains:
		TypeName += "Plain";
		break;
	case EECOLOGYTYPE::ForestPlateau:
		TypeName += "plateau";
		break;
	case EECOLOGYTYPE::ForestWaterfall:
		TypeName += "Waterfall";
		break;
	case EECOLOGYTYPE::TopTree:
		break;
	case EECOLOGYTYPE::Day:
		TypeName += "AllDay";
		break;
	case EECOLOGYTYPE::Night:
		TypeName += "Night";
		break;
	case EECOLOGYTYPE::AllDay:
		TypeName += "AllDay";
		break;
	default:
		break;
	}

	 return TypeName += ".png";
}