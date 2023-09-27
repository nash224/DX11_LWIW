#include "PreCompile.h"
#include "UI_ProductPage.h"

UI_ProductPage::UI_ProductPage() 
{
}

UI_ProductPage::~UI_ProductPage() 
{
}


void UI_ProductPage::Start()
{

}

void UI_ProductPage::Update(float _Delta)
{

}

void UI_ProductPage::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_ProductPage::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_ProductPage::CreatePage(std::string_view _ProduectName, int& PageCount)
{
	++PageCount;

	/*const std::shared_ptr<BiologyData>& Data = BiologyData::Find(_BiologyName);*/

	/*std::string Name = Data->BiologyName;*/

	m_ProductPageComposition.ProductTag = CreateComponent<GameEngineSpriteRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.ProductTag->SetSprite("Potion_Name.png");

	m_ProductPageComposition.Photo = CreateComponent<GameEngineSpriteRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.Photo->SetSprite("Photo.png");

	m_ProductPageComposition.Illustration = CreateComponent<GameEngineSpriteRenderer>(EUI_RENDERORDERORDER::Component);
	/*m_ProductPageComposition.Photo->SetSprite("Photo.png");*/

	m_ProductPageComposition.Frame = CreateComponent<GameEngineSpriteRenderer>(EUI_RENDERORDERORDER::Frame);
	m_ProductPageComposition.Frame->SetSprite("Base_LayoutLine_1.png");

	m_ProductPageComposition.Star = CreateComponent<GameEngineSpriteRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.Star->SetSprite("Base_LayoutLine_1.png");

}
