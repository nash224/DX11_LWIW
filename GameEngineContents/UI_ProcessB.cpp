#include "PreCompile.h"
#include "UI_ProcessB.h"

#include "IngredientData.h"
#include "ItemData.h"

#include "Ellie.h"
#include "UI_ProcessManager.h"
#include "UI_Inventory.h"

UI_ProcessB::UI_ProcessB() 
{
}

UI_ProcessB::~UI_ProcessB() 
{
}


void UI_ProcessB::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_ProcessB::Update(float _Delta)
{
	if (false == IsJustOpen)
	{
		UpdateInput();
	}

	IsJustOpen = false;
}

void UI_ProcessB::Release()
{
	BaseRenderer = nullptr;
	FrameRenderer = nullptr;
	ProductInfo.ProductRenderer = nullptr;
	ProductInfo.NameRenderer = nullptr;
	SourceInfo.SourceRenderer = nullptr;
	SourceInfo.SourceCntRenderer = nullptr;
	SourceInfo.SlashRenderer = nullptr;
	SourceInfo.NeedCntRenderer = nullptr;
	ProcessManager = nullptr;
}

void UI_ProcessB::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// 2번째창 이니셜
void UI_ProcessB::Init()
{
	RendererSetting();

	Off();
}

void UI_ProcessB::RendererSetting()
{
	const float BaseDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base);
	const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame);
	const float IconDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon);
	const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

	static constexpr float NameFontSize = 16.0f;
	static constexpr float CntFontSize = 13.0f;


	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
	BaseRenderer->SetSprite("Process_Base.png");

	FrameRenderer = CreateComponent<GameEngineUIRenderer>();
	FrameRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	FrameRenderer->SetSprite("Process_B_Contents.png");

	
	ProductInfo.ProductRenderer = CreateComponent<GameEngineUIRenderer>();
	ProductInfo.ProductRenderer->Transform.SetLocalPosition(float4(2.0f, 113.0f, IconDepth));

	ProductInfo.NameRenderer = CreateComponent<GameEngineUIRenderer>();
	ProductInfo.NameRenderer->Transform.SetLocalPosition(float4(2.0f, 78.0f, FontDepth));
	ProductInfo.NameRenderer->SetText(GlobalValue::Font_Sandoll, "", NameFontSize, BlackColor, FW1_TEXT_FLAG::FW1_CENTER);

	SourceInfo.SourceRenderer= CreateComponent<GameEngineUIRenderer>();
	SourceInfo.SourceRenderer->Transform.SetLocalPosition(float4(-76.0f, -1.0f, IconDepth));

	SourceInfo.NameRenderer = CreateComponent<GameEngineUIRenderer>();
	SourceInfo.NameRenderer->Transform.SetLocalPosition(float4(2.0f, 7.0f, FontDepth));
	SourceInfo.NameRenderer->SetText(GlobalValue::Font_Sandoll, "", NameFontSize, BlackColor, FW1_TEXT_FLAG::FW1_CENTER);

	static constexpr float SourceInfoFontYPos = 5.0f;

	SourceInfo.SlashRenderer = CreateComponent<GameEngineUIRenderer>();
	SourceInfo.SlashRenderer->Transform.SetLocalPosition(float4(76.0f, SourceInfoFontYPos, FontDepth));
	SourceInfo.SlashRenderer->SetText(GlobalValue::Font_Sandoll, "/", CntFontSize, BlackColor, FW1_TEXT_FLAG::FW1_RIGHT);
	
	SourceInfo.SourceCntRenderer= CreateComponent<GameEngineUIRenderer>();
	SourceInfo.SourceCntRenderer->Transform.SetLocalPosition(float4(64.0f, SourceInfoFontYPos, FontDepth));
	SourceInfo.SourceCntRenderer->SetText(GlobalValue::Font_Sandoll, "", CntFontSize, BlackColor, FW1_TEXT_FLAG::FW1_RIGHT);
	
	SourceInfo.NeedCntRenderer = CreateComponent<GameEngineUIRenderer>();
	SourceInfo.NeedCntRenderer->Transform.SetLocalPosition(float4(88.0f, SourceInfoFontYPos, FontDepth));
	SourceInfo.NeedCntRenderer->SetText(GlobalValue::Font_Sandoll, "", CntFontSize, BlackColor, FW1_TEXT_FLAG::FW1_RIGHT);
}


/////////////////////////////////////////////////////////////////////////////////////


void UI_ProcessB::Open(std::string_view _ProductName, int _ScrCount)
{
	ProductInfoSetting(_ProductName);
	SourceInfoSetting(_ProductName, _ScrCount);

	IsJustOpen = true;

	On();
}


void UI_ProcessB::ProductInfoSetting(std::string_view _ProductName)
{
	std::weak_ptr<IngredientData> Data = IngredientData::Find(_ProductName);
	if (true == Data.expired())
	{
		MsgBoxAssert("등록되지 않은 아이템 정보입니다.");
		return;
	}

	if (nullptr == ProductInfo.ProductRenderer || nullptr == ProductInfo.NameRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ProductInfo.ProductName = _ProductName;

	ProductInfo.ProductRenderer->SetSprite(_ProductName.data() + std::string(".png"));
	ProductInfo.NameRenderer->ChangeText(Data.lock()->KoreanName);
}

void UI_ProcessB::SourceInfoSetting(std::string_view _ProductName, int _ScrCount)
{
	std::weak_ptr<IngredientData> Data = IngredientData::Find(_ProductName);
	if (true == Data.expired())
	{
		MsgBoxAssert("등록되지 않은 데이터를 참조하려 했습니다.");
		return;
	}

	SourceInfo.ScrName = Data.lock()->SourceName;
	SourceInfo.NeedCount = Data.lock()->SourceCount;
	SourceInfo.ScrCount = _ScrCount;

	std::weak_ptr<ItemData> SrcData = ItemData::Find(Data.lock()->SourceName);
	if (true == SrcData.expired())
	{
		MsgBoxAssert("등록되지 않은 데이터를 참조하려 했습니다.");
		return;
	}


	if (nullptr == SourceInfo.SourceRenderer 
		|| nullptr == SourceInfo.NameRenderer 
		|| nullptr == SourceInfo.SourceCntRenderer 
		|| nullptr == SourceInfo.NeedCntRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	SourceInfo.SourceRenderer->SetSprite(Data.lock()->SourceName + std::string(".png"));
	SourceInfo.NameRenderer->ChangeText(SrcData.lock()->KoreanName);
	SourceInfo.SourceCntRenderer->ChangeText(std::to_string(_ScrCount));
	SourceInfo.NeedCntRenderer->ChangeText(std::to_string(Data.lock()->SourceCount));

	if (SourceInfo.NeedCount > _ScrCount)
	{
		const float4& REDCOLOR = float4(0.9f, 0.1f, 0.1f, 1.0f);
		SourceInfo.SourceCntRenderer->SetTextColor(REDCOLOR);
	}
	else
	{
		SourceInfo.SourceCntRenderer->SetTextColor(BlackColor);
	}
}

void UI_ProcessB::Close()
{
	Off();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_ProcessB::UpdateInput()
{
	if (SourceInfo.ScrCount >= SourceInfo.NeedCount)
	{
		if (true == GameEngineInput::IsDown('Z', this))
		{
			JuicyThis();
		}
	}

	if (true == GameEngineInput::IsPress('X', this))
	{
		if (nullptr == ProcessManager)
		{
			MsgBoxAssert("존재하지 않는 포인턴입니다.");
			return;
		}

		ProcessManager->OpenListWindow();
	}
}

void UI_ProcessB::JuicyThis()
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->WaitDone(EELLIE_STATE::Juicy);
	}

	if (nullptr == UI_Inventory::MainInventory)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return;
	}

	UI_Inventory::MainInventory->PopItem(SourceInfo.ScrName, SourceInfo.NeedCount);

	if (nullptr == ProcessManager)
	{
		MsgBoxAssert("가공 매니저가 존재하지 않습니다.");
		return;
	}

	ProcessManager->CreatedProductName = ProductInfo.ProductName;

	Off();
}
