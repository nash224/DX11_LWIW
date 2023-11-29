#include "PreCompile.h"
#include "UI_ProductPage.h"

#include "ProductRecipeData.h"
#include "IngredientData.h"


UI_ProductPage::UI_ProductPage() 
{
}

UI_ProductPage::~UI_ProductPage() 
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

	static constexpr float OptionGap = 100.0f;
	static constexpr float ItemSpaceGap = 74.0f;

	PageCount += 2;

	const float AttachmentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float ComponentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component);
	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	static constexpr float ConditionYCorrection = -32.0f;
	static constexpr float TagFontYCorrection = 26.0f;

	static constexpr float ConditionFontSize = 16.0f;

	const std::shared_ptr<ProductRecipeData>& Data = ProductRecipeData::Find(_ProduectName);
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터입니다.");
		return;
	}

	Page.ProductTag = CreateComponent<GameEngineUIRenderer>();
	Page.ProductTag->SetSprite("Potion_Name.png");
	Page.ProductTag->Transform.AddLocalPosition(float4(-176.0f, 129.0f, AttachmentDepth));

	Page.PageFont.Tag = CreateComponent<GameEngineUIRenderer>();
	Page.PageFont.Tag->SetText(GlobalValue::Font_Sandoll, Data->KoreanName, 20.0f, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	Page.PageFont.Tag->Transform.SetLocalPosition(float4(-176.0f, 129.0f + TagFontYCorrection, FontDepth));

	Page.Photo = CreateComponent<GameEngineUIRenderer>();
	Page.Photo->SetSprite("Photo.png");
	Page.Photo->Transform.AddLocalPosition(float4(-176.0f, 25.0f, AttachmentDepth));

	Page.Illustration = CreateComponent<GameEngineUIRenderer>();
	Page.Illustration->SetSprite(Data->ProductName + "_Illustration.png");
	Page.Illustration->Transform.AddLocalPosition(float4(-176.0f, 25.0f, ComponentDepth));

	Page.Frame = CreateComponent<GameEngineUIRenderer>();
	Page.Frame->SetSprite("Base_LayoutLine_1.png");
	Page.Frame->Transform.AddLocalPosition(float4(-176.0f, -46.0f, FrameDepth));

	Page.Star = CreateComponent<GameEngineUIRenderer>();
	Page.Star->SetSprite("IllustedBook_Icon_Star.png", static_cast<int>(Data->Star));
	Page.Star->Transform.AddLocalPosition(float4(79.0f, 129.0f, ComponentDepth));

	Page.PageFont.Star = CreateComponent<GameEngineUIRenderer>();
	Page.PageFont.Star->SetText(GlobalValue::Font_Sandoll, GetStarString(Data->Star), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	Page.PageFont.Star->Transform.SetLocalPosition(float4(79.0f, 129.0f + ConditionYCorrection, FontDepth));

	Page.Fire = CreateComponent<GameEngineUIRenderer>();
	Page.Fire->SetSprite("IllustedBook_Icon_Fire.png", static_cast<int>(Data->Fire));
	Page.Fire->Transform.AddLocalPosition(float4(79.0f + OptionGap, 129.0f, ComponentDepth));

	Page.PageFont.Fire = CreateComponent<GameEngineUIRenderer>();
	Page.PageFont.Fire->SetText(GlobalValue::Font_Sandoll, GetFireString(Data->Fire), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	Page.PageFont.Fire->Transform.SetLocalPosition(float4(79.0f + OptionGap, 129.0f + ConditionYCorrection, FontDepth));

	Page.Ladle = CreateComponent<GameEngineUIRenderer>();
	Page.Ladle->SetSprite("IllustedBook_Icon_Ladle.png", static_cast<int>(Data->Ladle));
	Page.Ladle->Transform.AddLocalPosition(float4(79.0f + OptionGap * 2.0f, 129.0f, ComponentDepth));

	Page.PageFont.Fire = CreateComponent<GameEngineUIRenderer>();
	Page.PageFont.Fire->SetText(GlobalValue::Font_Sandoll, GetLadleString(Data->Ladle), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	Page.PageFont.Fire->Transform.SetLocalPosition(float4(79.0f + OptionGap * 2.0f, 129.0f + ConditionYCorrection, FontDepth));

	std::string ContentText = StringFunction::InsertNewLineBTWWord(Data->Content, 24);

	Page.DESC = CreateComponent<GameEngineUIRenderer>();
	Page.DESC->SetText(GlobalValue::Font_Sandoll, ContentText, 14.0f, float4(0.1f, 0.1f, 0.1f, 1.0f));
	Page.DESC->Transform.SetLocalPosition(float4(-306.0f, -58.0f, FontDepth));


	static constexpr float MaterialFontSize = 14.0f;
	static constexpr float MaterialFontCorrection = -26.0f;

	Page.ItemSlots.resize(Data->Material.size());
	for (int i = 0; i < static_cast<int>(Page.ItemSlots.size()); i++)
	{
		std::shared_ptr<GameEngineUIRenderer> ItemSpace = CreateComponent<GameEngineUIRenderer>();
		ItemSpace->SetSprite("Inventory_Empty_Slot.png");
		ItemSpace->Transform.AddLocalPosition(float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), AttachmentDepth));
		Page.ItemSlots[i].ItemSpace = ItemSpace;

		std::shared_ptr<GameEngineUIRenderer> ItemSlot = CreateComponent<GameEngineUIRenderer>();
		ItemSlot->SetSprite(Data->Material[i].MaterialName + ".png");
		ItemSlot->Transform.AddLocalPosition(float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), ComponentDepth));
		Page.ItemSlots[i].ItemSlot = ItemSlot;

		const std::shared_ptr<IngredientData>& Ingredient = IngredientData::Find(Data->Material[i].MaterialName);
		if (nullptr == Ingredient)
		{
			MsgBoxAssert("등록하지 않는 재료입니다.");
			return;
		}

		std::shared_ptr<GameEngineUIRenderer> Font = CreateComponent<GameEngineUIRenderer>();
		Font->SetText(GlobalValue::Font_Sandoll, Ingredient->KoreanName, MaterialFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
		Font->Transform.AddLocalPosition(float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i) + MaterialFontCorrection, FontDepth));
		Page.ItemSlots[i].IngredientName = Font;
	}

	Off();
}

std::string UI_ProductPage::GetStarString(EBREWING_DIFFICULTY _Number)
{
	std::string ReturnValue;

	switch (_Number)
	{
	case EBREWING_DIFFICULTY::Easy:
		ReturnValue = "쉬움";
		break;
	case EBREWING_DIFFICULTY::Normal:
		ReturnValue = "보통";
		break;
	case EBREWING_DIFFICULTY::Hard:
		ReturnValue = "어려움";
		break;
	default:
		break;
	}
	
	return ReturnValue;
}

std::string UI_ProductPage::GetFireString(EBREWING_FIRE _Number)
{
	std::string ReturnValue;

	switch (_Number)
	{
	case EBREWING_FIRE::One:
		ReturnValue = "1단";
		break;
	case EBREWING_FIRE::Two:
		ReturnValue = "2단";
		break;
	case EBREWING_FIRE::Three:
		ReturnValue = "3단";
		break;
	case EBREWING_FIRE::Four:
		ReturnValue = "4단";
		break;
	case EBREWING_FIRE::Five:
		ReturnValue = "5단";
		break;
	default:
		break;
	}

	return ReturnValue;
}

std::string UI_ProductPage::GetLadleString(EBREWING_DIRECTION _Number)
{
	std::string ReturnValue;

	switch (_Number)
	{
	case EBREWING_DIRECTION::StirNone:
		ReturnValue = "젓지 않음";
		break;
	case EBREWING_DIRECTION::StirRight:
		ReturnValue = "시계 방향";
		break;
	case EBREWING_DIRECTION::StirLeft:
		ReturnValue = "반시계 방향";
		break;
	default:
		break;
	}

	return ReturnValue;
}