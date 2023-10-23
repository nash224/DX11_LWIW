#include "PreCompile.h"
#include "UI_ProcessListUnit.h"

#include "IngredientData.h"


UI_ProcessListUnit::UI_ProcessListUnit() 
{
}

UI_ProcessListUnit::~UI_ProcessListUnit() 
{
}


void UI_ProcessListUnit::Start()
{

}

void UI_ProcessListUnit::Update(float _Delta)
{

}

void UI_ProcessListUnit::Release()
{
	Panel = nullptr;
	ItemSlot = nullptr;
	ItemImg = nullptr;
}

void UI_ProcessListUnit::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_ProcessListUnit::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_ProcessListUnit::Init(std::string_view _ProcessName)
{
	// 정보 읽기
	std::shared_ptr<IngredientData> Data = IngredientData::Find(_ProcessName);

	ItemName = Data->Name;
	ItemKRName = Data->KoreanName;
	NeedCount = Data->SourceCount;
	SrcName = Data->SourceName;

	// 렌더러 세팅
	Panel = CreateComponent<GameEngineUIRenderer>();
	Panel->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	Panel->SetSprite("Process_A_List.png");

	ItemSlot = CreateComponent<GameEngineUIRenderer>();
	ItemSlot->Transform.SetLocalPosition(float4(-76.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	ItemSlot->SetSprite("Process_A_Slot.png");

	ItemImg = CreateComponent<GameEngineUIRenderer>();
	ItemImg->Transform.SetLocalPosition(float4(-76.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Icon)));
	ItemImg->SetSprite(_ProcessName.data() + std::string(".png"));

	ItemMaskImg = CreateComponent<GameEngineUIRenderer>();
	ItemMaskImg->Transform.SetLocalPosition(float4(-76.0f, 0.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Icon_Mask)));
	ItemMaskImg->SetSprite(_ProcessName.data() + std::string("_Mask.png"));

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
		ItemImg->Off();
	}
	else if (EPROCESSUNITSTATE::NotPossible == State)
	{
		ItemMaskImg->GetColorData().MulColor.A = 0.6f;
		ItemMaskImg->On();
	}
	else
	{
		ItemMaskImg->Off();
	}
}