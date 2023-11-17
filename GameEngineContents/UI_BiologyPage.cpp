#include "PreCompile.h"
#include "UI_BiologyPage.h"


#include "BiologyData.h"
#include "ItemData.h"

UI_BiologyPage::UI_BiologyPage()
{
}

UI_BiologyPage::~UI_BiologyPage()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 페이지를 생성해줍니다.
void UI_BiologyPage::CreatePage(std::string_view _BiologyName, int& PageCount)
{
	++PageCount;
	
	float4 MovePage = float4( -176.0f , 0.0f );

	// 짝수라면
	if (0 == PageCount % 2)
	{
		MovePage.X *= -1.0f;
	}

	Transform.AddLocalPosition(MovePage);

	const std::shared_ptr<BiologyData>& Data = BiologyData::Find(_BiologyName);
	if (nullptr == Data)
	{
		MsgBoxAssert("등록되지 않는 데이터입니다.");
		return;
	}

	std::string Name = Data->BiologyName;

	static constexpr float SlotGap = 48.0f;

	const float AttachmentDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float ComponentDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component);
	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	const float4& NameTagBasePosition = float4(1.0f, 150.0f, AttachmentDepth);
	const float4& TagNamePosition = float4(1.0f, 158.0f, FontDepth);
	const float4& FramePosition = float4(0.0f, -29.0f, FrameDepth);
	const float4& PhotoPosition = float4(-84.0f, 49.0f, AttachmentDepth);
	const float4& IllustrationPosition = float4(-84.0f, 49.0f, ComponentDepth);
	const float4& EcologicalNamePosition = float4(9.0f, 96.0f + 30.0f, FontDepth);
	const float4& Slot1Position = float4(9.0f, 92.0f, ComponentDepth);
	const float4& Slot2Position = float4(9.0f + SlotGap, 92.0f, ComponentDepth);
	const float4& Slot3Position = float4(9.0f + SlotGap*2.0f, 92.0f, ComponentDepth);

	const float4& ToolPosition = float4(10.0f, 44.0f, ComponentDepth);

	const float4& ItemSpacePosition = float4(9.0f, -3.0f, AttachmentDepth);
	const float4& ItemImgPosition = float4(9.0f, -3.0f, ComponentDepth);
	const float4& ItemNamePosition = float4(36.0f, 4.0f, FontDepth);

	const float4& BlackFontColor = float4(0.1f, 0.1f, 0.1f, 1.0f);


	PageInfo.NameTag.Base = CreateComponent<GameEngineUIRenderer>();
	PageInfo.NameTag.Base->SetSprite("CreatureName.png");
	PageInfo.NameTag.Base->Transform.SetLocalPosition(NameTagBasePosition);

	PageInfo.NameTag.MaterialName = CreateComponent<GameEngineUIRenderer>();
	PageInfo.NameTag.MaterialName->SetText(GlobalValue::Font_Sandoll, Data->KoreanName, 20.0f, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.NameTag.MaterialName->Transform.SetLocalPosition(TagNamePosition);

	PageInfo.Frame = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Frame->SetSprite("Base_LayoutLine_1.png");
	PageInfo.Frame->Transform.SetLocalPosition(FramePosition);

	PageInfo.Illustration.Photo = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Illustration.Photo->SetSprite("Photo.png");
	PageInfo.Illustration.Photo->Transform.SetLocalPosition(PhotoPosition);

	PageInfo.Illustration.Illustration = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Illustration.Illustration->SetSprite(Name + "_Illustration.png");
	PageInfo.Illustration.Illustration->Transform.SetLocalPosition(IllustrationPosition);


	PageInfo.Ecological.Font = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ecological.Font->SetText(GlobalValue::Font_Sandoll, "생태정보", 12.0f, BlackFontColor, FW1_TEXT_FLAG::FW1_CENTER);
	PageInfo.Ecological.Font->Transform.SetLocalPosition(EcologicalNamePosition);

	PageInfo.Ecological.Slot1 = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ecological.Slot1->SetSprite(ReturnEcologyTypeFileName(Data->EcologicalGroup));
	PageInfo.Ecological.Slot1->Transform.SetLocalPosition(Slot1Position);

	PageInfo.Ecological.Slot2 = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ecological.Slot2->SetSprite(ReturnEcologyTypeFileName(Data->Habitat));
	PageInfo.Ecological.Slot2->Transform.SetLocalPosition(Slot2Position);

	PageInfo.Ecological.Slot3 = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Ecological.Slot3->SetSprite(ReturnEcologyTypeFileName(Data->AppearanceTime));
	PageInfo.Ecological.Slot3->Transform.SetLocalPosition(Slot3Position);

	PageInfo.Tool = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Tool->SetSprite("Tool_Icon.png", static_cast<int>(Data->GatherTool));
	PageInfo.Tool->Transform.SetLocalPosition(ToolPosition);

	PageInfo.Item.ItemSpace = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Item.ItemSpace->SetSprite("Inventory_Empty_Slot.png");
	PageInfo.Item.ItemSpace->Transform.SetLocalPosition(ItemSpacePosition);

	PageInfo.Item.ItemImg = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Item.ItemImg->SetSprite(Data->BiologyName + "_Collect.png");
	PageInfo.Item.ItemImg->Transform.SetLocalPosition(ItemImgPosition);

	const std::shared_ptr<ItemData>& MaterialData = ItemData::Find(Data->ItemName);
	if (nullptr == MaterialData)
	{
		MsgBoxAssert("등록되지 않는 데이터입니다.");
		return;
	}

	PageInfo.Item.ItemName = CreateComponent<GameEngineUIRenderer>();
	PageInfo.Item.ItemName->SetText(GlobalValue::Font_Sandoll, MaterialData->KoreanName, 15.0f, BlackFontColor, FW1_TEXT_FLAG::FW1_LEFT);
	PageInfo.Item.ItemName->Transform.SetLocalPosition(ItemNamePosition);

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