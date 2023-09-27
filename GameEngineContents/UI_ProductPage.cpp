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
	PageCount += 2;

	const std::shared_ptr<ProductRecipeData>& Data = ProductRecipeData::Find(_ProduectName);

	m_ProductPageComposition.ProductTag = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.ProductTag->SetSprite("Potion_Name.png");
	m_ProductPageComposition.ProductTag->Transform.AddLocalPosition({ -176.0f , 129.0f });

	m_ProductPageComposition.Photo = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.Photo->SetSprite("Photo.png");
	m_ProductPageComposition.Photo->Transform.AddLocalPosition({ -176.0f , 25.0f });

	m_ProductPageComposition.Illustration = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.Illustration->SetSprite(Data->ProductName + "_Illustration.png");
	m_ProductPageComposition.Illustration->Transform.AddLocalPosition({ -176.0f , 25.0f });

	m_ProductPageComposition.Frame = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Frame);
	m_ProductPageComposition.Frame->SetSprite("Base_LayoutLine_1.png");
	m_ProductPageComposition.Frame->Transform.AddLocalPosition({ -176.0f , -46.0f });

	m_ProductPageComposition.Star = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.Star->SetSprite(ReturnIllustedBookFileName(Data->Star), ReturnIllustedBookIndex(Data->Star));
	m_ProductPageComposition.Star->Transform.AddLocalPosition({ 79.0f , 129.0f });

	m_ProductPageComposition.Fire = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.Fire->SetSprite(ReturnIllustedBookFileName(Data->Fire), ReturnIllustedBookIndex(Data->Fire));
	m_ProductPageComposition.Fire->Transform.AddLocalPosition({ 79.0f + CONST_OptionGap , 129.0f });

	m_ProductPageComposition.Ladle = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.Ladle->SetSprite(ReturnIllustedBookFileName(Data->Ladle), ReturnIllustedBookIndex(Data->Ladle));
	m_ProductPageComposition.Ladle->Transform.AddLocalPosition({ 79.0f + CONST_OptionGap * 2.0f, 129.0f });

	m_ProductPageComposition.ItemSpace1 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.ItemSpace1->SetSprite("Inventory_Empty_Slot.png");
	m_ProductPageComposition.ItemSpace1->Transform.AddLocalPosition({ 79.0f , 45.0f });

	m_ProductPageComposition.ItemSlot1 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.ItemSlot1->SetSprite(Data->Material1 + ".png");
	m_ProductPageComposition.ItemSlot1->Transform.AddLocalPosition({ 79.0f , 45.0f });

	m_ProductPageComposition.ItemSpace2 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
	m_ProductPageComposition.ItemSpace2->SetSprite("Inventory_Empty_Slot.png");
	m_ProductPageComposition.ItemSpace2->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap });

	m_ProductPageComposition.ItemSlot2 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
	m_ProductPageComposition.ItemSlot2->SetSprite(Data->Material2 + ".png");
	m_ProductPageComposition.ItemSlot2->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap });

	if ("" != Data->Material3)
	{
		m_ProductPageComposition.ItemSpace3 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Attachment);
		m_ProductPageComposition.ItemSpace3->SetSprite("Inventory_Empty_Slot.png"); 
		m_ProductPageComposition.ItemSpace3->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f });

		m_ProductPageComposition.ItemSlot3 = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERORDER::Component);
		m_ProductPageComposition.ItemSlot3->SetSprite(Data->Material3 + ".png");
		m_ProductPageComposition.ItemSlot3->Transform.AddLocalPosition({ 79.0f , 45.0f - CONST_ItemSpaceGap * 2.0f });
	}

	Off();
}

std::string UI_ProductPage::ReturnIllustedBookFileName(EBREWINGOPTION _Option)
{
	std::string FileName = "IllustedBook_Icon_";

	switch (_Option)
	{
	case EBREWINGOPTION::None:
	{
		MsgBoxAssert("해당 양조 옵션은 존재하지 않습니다.");
	}
		break;
	case EBREWINGOPTION::Easy:
	case EBREWINGOPTION::Normal:
	case EBREWINGOPTION::Hard:
		FileName += "Star";
		break;
	case EBREWINGOPTION::StirNone:
	case EBREWINGOPTION::StirRight:
	case EBREWINGOPTION::StirLeft:
		FileName += "Ladle";
		break;
	case EBREWINGOPTION::One:
	case EBREWINGOPTION::Two:
	case EBREWINGOPTION::Three:
	case EBREWINGOPTION::Four:
	case EBREWINGOPTION::Five:
		FileName += "Fire";
		break;
	default:
		break;
	}

	return FileName += ".png";
}

int UI_ProductPage::ReturnIllustedBookIndex(EBREWINGOPTION _Option)
{
	int Index = -1;

	switch (_Option)
	{
	case EBREWINGOPTION::None:
	{
		MsgBoxAssert("해당 양조 옵션은 존재하지 않습니다.");
		return -1;
	}
		break;
	case EBREWINGOPTION::Easy:
		Index = 0;
		break;
	case EBREWINGOPTION::Normal:
		Index = 1;
		break;
	case EBREWINGOPTION::Hard:
		Index = 2;
		break;
	case EBREWINGOPTION::StirNone:
		Index = 0;
		break;
	case EBREWINGOPTION::StirRight:
		Index = 1;
		break;
	case EBREWINGOPTION::StirLeft:
		Index = 2;
		break;
	case EBREWINGOPTION::One:
		Index = 0;
		break;
	case EBREWINGOPTION::Two:
		Index = 1;
		break;
	case EBREWINGOPTION::Three:
		Index = 2;
		break;
	case EBREWINGOPTION::Four:
		Index = 3;
		break;
	case EBREWINGOPTION::Five:
		Index = 4;
		break;
	default:
		break;
	}

	return Index;
}