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

	const float4& TagPosition = float4(-176.0f, 129.0f, AttachmentDepth);
	const float4& TagNamePosition = float4(-176.0f, 129.0f + TagFontYCorrection, FontDepth);
	const float4& PhotoPosition = float4(-176.0f, 25.0f, AttachmentDepth);
	const float4& IllustrationPosition = float4(-176.0f, 25.0f, ComponentDepth);
	const float4& FramePosition = float4(-176.0f, -46.0f, FrameDepth);
	const float4& StarPosition = float4(79.0f, 129.0f, ComponentDepth);
	const float4& StarFontPosition = float4(79.0f, 129.0f + ConditionYCorrection, FontDepth);
	const float4& FirePosition = float4(79.0f + OptionGap, 129.0f, ComponentDepth);
	const float4& FireFontPosition = float4(79.0f + OptionGap, 129.0f + ConditionYCorrection, FontDepth);
	const float4& LadlePosition = float4(79.0f + OptionGap * 2.0f, 129.0f, ComponentDepth);
	const float4& LadleFontPosition = float4(79.0f + OptionGap * 2.0f, 129.0f + ConditionYCorrection, FontDepth);

	static constexpr float ConditionFontSize = 16.0f;

	const std::shared_ptr<ProductRecipeData>& Data = ProductRecipeData::Find(_ProduectName);
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터입니다.");
		return;
	}

	PageInfo.ProductTag = CreateComponent<GameEngineUIRenderer>();
	PageInfo.ProductTag->SetSprite("Potion_Name.png");
	PageInfo.ProductTag->Transform.AddLocalPosition(TagPosition);

	PageInfo.PageFont.Tag = CreateComponent<GameEngineUIRenderer>();
	PageInfo.PageFont.Tag->SetText(GlobalValue::Font_Sandoll, Data->KoreanName, 20.0f, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.PageFont.Tag->Transform.SetLocalPosition(TagNamePosition);

	PageInfo.Photo = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Photo->SetSprite("Photo.png");
	PageInfo.Photo->Transform.AddLocalPosition(PhotoPosition);

	PageInfo.Illustration = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Illustration->SetSprite(Data->ProductName + "_Illustration.png");
	PageInfo.Illustration->Transform.AddLocalPosition(IllustrationPosition);

	PageInfo.Frame = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Frame->SetSprite("Base_LayoutLine_1.png");
	PageInfo.Frame->Transform.AddLocalPosition(FramePosition);

	PageInfo.Star = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Star->SetSprite("IllustedBook_Icon_Star.png", static_cast<int>(Data->Star));
	PageInfo.Star->Transform.AddLocalPosition(StarPosition);

	PageInfo.PageFont.Star = CreateComponent<GameEngineUIRenderer>();
	PageInfo.PageFont.Star->SetText(GlobalValue::Font_Sandoll, GetStarString(Data->Star), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.PageFont.Star->Transform.SetLocalPosition(StarFontPosition);

	PageInfo.Fire = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Fire->SetSprite("IllustedBook_Icon_Fire.png", static_cast<int>(Data->Fire));
	PageInfo.Fire->Transform.AddLocalPosition(FirePosition);

	PageInfo.PageFont.Fire = CreateComponent<GameEngineUIRenderer>();
	PageInfo.PageFont.Fire->SetText(GlobalValue::Font_Sandoll, GetFireString(Data->Fire), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.PageFont.Fire->Transform.SetLocalPosition(FireFontPosition);

	PageInfo.Ladle = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ladle->SetSprite("IllustedBook_Icon_Ladle.png", static_cast<int>(Data->Ladle));
	PageInfo.Ladle->Transform.AddLocalPosition(LadlePosition);

	PageInfo.PageFont.Fire = CreateComponent<GameEngineUIRenderer>();
	PageInfo.PageFont.Fire->SetText(GlobalValue::Font_Sandoll, GetLadleString(Data->Ladle), ConditionFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.PageFont.Fire->Transform.SetLocalPosition(LadleFontPosition);


	static constexpr float MaterialFontSize = 14.0f;
	static constexpr float MaterialFontCorrection = -26.0f;

	PageInfo.ItemSlots.resize(Data->Material.size());
	for (int i = 0; i < static_cast<int>(PageInfo.ItemSlots.size()); i++)
	{
		const float4& ItemSpacePosition = float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), AttachmentDepth);
		const float4& ItemSlotPosition = float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), ComponentDepth);
		const float4& MaterialFontPosition = float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i) + MaterialFontCorrection, FontDepth);

		std::shared_ptr<GameEngineUIRenderer> ItemSpace = CreateComponent<GameEngineUIRenderer>();
		ItemSpace->SetSprite("Inventory_Empty_Slot.png");
		ItemSpace->Transform.AddLocalPosition(ItemSpacePosition);
		PageInfo.ItemSlots[i].ItemSpace = ItemSpace;

		std::shared_ptr<GameEngineUIRenderer> ItemSlot = CreateComponent<GameEngineUIRenderer>();
		ItemSlot->SetSprite(Data->Material[i].MaterialName + ".png");
		ItemSlot->Transform.AddLocalPosition(ItemSlotPosition);
		PageInfo.ItemSlots[i].ItemSlot = ItemSlot;

		const std::shared_ptr<IngredientData>& Ingredient = IngredientData::Find(Data->Material[i].MaterialName);
		if (nullptr == Ingredient)
		{
			MsgBoxAssert("등록하지 않는 재료입니다.");
			return;
		}

		std::shared_ptr<GameEngineUIRenderer> Font = CreateComponent<GameEngineUIRenderer>();
		Font->SetText(GlobalValue::Font_Sandoll, Ingredient->KoreanName, MaterialFontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
		Font->Transform.AddLocalPosition(MaterialFontPosition);
		PageInfo.ItemSlots[i].IngredientName = Font;
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