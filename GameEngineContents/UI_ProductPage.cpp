#include "PreCompile.h"
#include "UI_ProductPage.h"

#include "ProductRecipeData.h"


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
	if (nullptr == GameEngineSprite::Find("IllustedBook_Icon_Star.png"))
	{
		GameEngineSprite::CreateCut("IllustedBook_Icon_Star.png", 3, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Ladle.png", 3, 1);
		GameEngineSprite::CreateCut("IllustedBook_Icon_Fire.png", 5, 1);
	}

	PageCount += 2;

	float4 CompositionPosition = float4::ZERO;

	const std::shared_ptr<ProductRecipeData>& Data = ProductRecipeData::Find(_ProduectName);

	m_ProductPageComposition.ProductTag = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.ProductTag->SetSprite("Potion_Name.png");
	CompositionPosition = { -176.0f , 129.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment) };
	m_ProductPageComposition.ProductTag->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Photo = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Photo->SetSprite("Photo.png");
	CompositionPosition = { -176.0f , 25.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment) };
	m_ProductPageComposition.Photo->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Illustration = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Illustration->SetSprite(Data->ProductName + "_Illustration.png");
	CompositionPosition = { -176.0f , 25.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.Illustration->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Frame = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Frame->SetSprite("Base_LayoutLine_1.png");
	CompositionPosition = { -176.0f , -46.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame) };
	m_ProductPageComposition.Frame->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Star = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Star->SetSprite("IllustedBook_Icon_Star.png", static_cast<int>(Data->Star));
	CompositionPosition = { 79.0f , 129.0f  , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.Star->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Fire = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Fire->SetSprite("IllustedBook_Icon_Fire.png", static_cast<int>(Data->Fire));
	CompositionPosition = { 79.0f + CONST_OptionGap , 129.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.Fire->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.Ladle = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.Ladle->SetSprite("IllustedBook_Icon_Ladle.png", static_cast<int>(Data->Ladle));
	CompositionPosition = { 79.0f + CONST_OptionGap * 2.0f, 129.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.Ladle->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.ItemSpace1 = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.ItemSpace1->SetSprite("Inventory_Empty_Slot.png");
	CompositionPosition = { 79.0f , 45.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment) };
	m_ProductPageComposition.ItemSpace1->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.ItemSlot1 = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.ItemSlot1->SetSprite(Data->Material[0].MaterialName + ".png");
	CompositionPosition = { 79.0f , 45.0f  , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.ItemSlot1->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.ItemSpace2 = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.ItemSpace2->SetSprite("Inventory_Empty_Slot.png");
	CompositionPosition = { 79.0f , 45.0f - CONST_ItemSpaceGap  , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment) };
	m_ProductPageComposition.ItemSpace2->Transform.AddLocalPosition(CompositionPosition);

	m_ProductPageComposition.ItemSlot2 = CreateComponent<GameEngineUIRenderer>();
	m_ProductPageComposition.ItemSlot2->SetSprite(Data->Material[1].MaterialName + ".png");
	CompositionPosition = { 79.0f , 45.0f - CONST_ItemSpaceGap , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
	m_ProductPageComposition.ItemSlot2->Transform.AddLocalPosition(CompositionPosition);

	if ("" != Data->Material[2].MaterialName)
	{
		m_ProductPageComposition.ItemSpace3 = CreateComponent<GameEngineUIRenderer>();
		m_ProductPageComposition.ItemSpace3->SetSprite("Inventory_Empty_Slot.png"); 
		CompositionPosition = { 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment) };
		m_ProductPageComposition.ItemSpace3->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f });

		m_ProductPageComposition.ItemSlot3 = CreateComponent<GameEngineUIRenderer>();
		m_ProductPageComposition.ItemSlot3->SetSprite(Data->Material[2].MaterialName + ".png");
		CompositionPosition = { 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component) };
		m_ProductPageComposition.ItemSlot3->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f });
	}

	Off();
}
