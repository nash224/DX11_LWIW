#include "PreCompile.h"
#include "UI_ProcessListUnit.h"

#include "IngredientData.h"


UI_ProcessListUnit::UI_ProcessListUnit() 
{
}

UI_ProcessListUnit::~UI_ProcessListUnit() 
{
}



void UI_ProcessListUnit::Release()
{
	BaseRenderer = nullptr;
	SlotRenderer = nullptr;
	MaterialRenderer = nullptr;
	MaterialMaskRenderer = nullptr;
	NameRenderer = nullptr;
}

void UI_ProcessListUnit::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_ProcessListUnit::Init(std::string_view _ProcessName)
{
	std::weak_ptr<IngredientData> Data = IngredientData::Find(_ProcessName);
	if (true == Data.expired())
	{
		MsgBoxAssert("존재하지 않는 데이터입니다.");
		return;
	}

	ItemName = Data.lock()->Name;
	ItemKRName = Data.lock()->KoreanName;
	NeedCount = Data.lock()->SourceCount;
	SrcName = Data.lock()->SourceName;

	const float FrameDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float AttachmentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	const float IconDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon);
	const float Icon_MaskDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon_Mask);
	const float FontDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	BaseRenderer->SetSprite("Process_A_List.png");

	SlotRenderer = CreateComponent<GameEngineUIRenderer>();
	SlotRenderer->Transform.SetLocalPosition(float4(-76.0f, 0.0f, AttachmentDepth));
	SlotRenderer->SetSprite("Process_A_Slot.png");

	MaterialRenderer = CreateComponent<GameEngineUIRenderer>();
	MaterialRenderer->Transform.SetLocalPosition(float4(-76.0f, 0.0f, IconDepth));
	MaterialRenderer->SetSprite(_ProcessName.data() + std::string(".png"));

	MaterialMaskRenderer  = CreateComponent<GameEngineUIRenderer>();
	MaterialMaskRenderer ->Transform.SetLocalPosition(float4(-76.0f, 0.0f, Icon_MaskDepth));
	MaterialMaskRenderer ->SetSprite(_ProcessName.data() + std::string("_Mask.png"));

	NameRenderer = CreateComponent<GameEngineUIRenderer>();
	NameRenderer->Transform.SetLocalPosition(float4(16.0f, 8.0f, FontDepth));
	NameRenderer->SetText(GlobalValue::Font_Sandoll, ItemKRName, 15.0f, float4(0.1f, 0.1f, 0.1f, 1.0f), FW1_TEXT_FLAG::FW1_CENTER);

	Off();
}

// 렌더러 갱신
void UI_ProcessListUnit::RenewRenderer()
{
	if (SrcCount >= NeedCount)
	{
		State = EPROCESSUNITSTATE::Possible;
	}
	else if (SrcCount < NeedCount)
	{
		State = EPROCESSUNITSTATE::NotPossible;
	}

	if (EPROCESSUNITSTATE::Unknown == State)
	{
		MaterialRenderer->Off();
	}
	else if (EPROCESSUNITSTATE::NotPossible == State)
	{
		MaterialMaskRenderer->GetColorData().MulColor.A = 0.6f;
		MaterialMaskRenderer->On();
	}
	else
	{
		MaterialMaskRenderer->Off();
	}
}