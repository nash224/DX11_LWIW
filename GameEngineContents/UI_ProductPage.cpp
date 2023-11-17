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

	static constexpr float OptionGap = 100.0f;
	static constexpr float ItemSpaceGap = 74.0f;

	PageCount += 2;

	const float AttachmentDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float ComponentDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component);
	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	const float4& TagPosition = float4(-176.0f, 129.0f, AttachmentDepth);
	const float4& PhotoPosition = float4(-176.0f, 25.0f, AttachmentDepth);
	const float4& IllustrationPosition = float4(-176.0f, 25.0f, ComponentDepth);
	const float4& FramePosition = float4(-176.0f, -46.0f, FrameDepth);
	const float4& StarPosition = float4(79.0f, 129.0f, ComponentDepth);
	const float4& FirePosition = float4(79.0f + OptionGap, 129.0f, ComponentDepth);
	const float4& LadlePosition = float4(79.0f + OptionGap * 2.0f, 129.0f, ComponentDepth);

	const std::shared_ptr<ProductRecipeData>& Data = ProductRecipeData::Find(_ProduectName);
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터입니다.");
		return;
	}

	PageInfo.ProductTag = CreateComponent<GameEngineUIRenderer>();
	PageInfo.ProductTag->SetSprite("Potion_Name.png");
	PageInfo.ProductTag->Transform.AddLocalPosition(TagPosition);

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

	PageInfo.Fire = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Fire->SetSprite("IllustedBook_Icon_Fire.png", static_cast<int>(Data->Fire));
	PageInfo.Fire->Transform.AddLocalPosition(FirePosition);

	PageInfo.Ladle = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ladle->SetSprite("IllustedBook_Icon_Ladle.png", static_cast<int>(Data->Ladle));
	PageInfo.Ladle->Transform.AddLocalPosition(LadlePosition);

	PageInfo.ItemSlots.resize(Data->Material.size());
	for (int i = 0; i < static_cast<int>(PageInfo.ItemSlots.size()); i++)
	{
		const float4& ItemSpacePosition = float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), AttachmentDepth);
		const float4& ItemSlotPosition = float4(79.0f, 45.0f - ItemSpaceGap * static_cast<float>(i), ComponentDepth);

		std::shared_ptr<GameEngineUIRenderer> ItemSpace = CreateComponent<GameEngineUIRenderer>();
		ItemSpace->SetSprite("Inventory_Empty_Slot.png");
		ItemSpace->Transform.AddLocalPosition(ItemSpacePosition);
		PageInfo.ItemSlots[i].ItemSpace = ItemSpace;

		std::shared_ptr<GameEngineUIRenderer> ItemSlot = CreateComponent<GameEngineUIRenderer>();
		ItemSlot->SetSprite(Data->Material[i].MaterialName + ".png");
		ItemSlot->Transform.AddLocalPosition(ItemSlotPosition);
	}

	Off();
}
