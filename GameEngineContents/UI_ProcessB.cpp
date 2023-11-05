#include "PreCompile.h"
#include "UI_ProcessB.h"


#include "IngredientData.h"
#include "UI_ProcessManager.h"
#include "UI_Inventory.h"
#include "Ellie.h"

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
	m_Base = nullptr;
	m_Frame = nullptr;
	m_ProcessBProductInfo.ProductImg = nullptr;
	m_ProcessBSourceInfo.SrcImg = nullptr;
	ProcessManager = nullptr;
}

void UI_ProcessB::LevelStart(class GameEngineLevel* _NextLevel)
{

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
	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Process_Base.png");

	m_Frame = CreateComponent<GameEngineUIRenderer>();
	m_Frame->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_Frame->SetSprite("Process_B_Contents.png");

	
	m_ProcessBProductInfo.ProductImg = CreateComponent<GameEngineUIRenderer>();
	m_ProcessBProductInfo.ProductImg->Transform.SetLocalPosition(float4(2.0f, 113.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon)));

	m_ProcessBSourceInfo.SrcImg= CreateComponent<GameEngineUIRenderer>();
	m_ProcessBSourceInfo.SrcImg->Transform.SetLocalPosition(float4(-76.0f, -1.0f, GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon)));
	
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
	m_ProcessBProductInfo.ProductName = _ProductName;

	if (nullptr == m_ProcessBProductInfo.ProductImg)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_ProcessBProductInfo.ProductImg->SetSprite(_ProductName.data() + std::string(".png"));
}

void UI_ProcessB::SourceInfoSetting(std::string_view _ProductName, int _ScrCount)
{
	std::shared_ptr<IngredientData> Data = IngredientData::Find(_ProductName);
	m_ProcessBSourceInfo.ScrName = Data->SourceName;
	m_ProcessBSourceInfo.NeedCount = Data->SourceCount;
	m_ProcessBSourceInfo.ScrCount = _ScrCount;

	if (nullptr == m_ProcessBSourceInfo.SrcImg)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_ProcessBSourceInfo.SrcImg->SetSprite(Data->SourceName + std::string(".png"));
}

void UI_ProcessB::Close()
{
	Off();
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_ProcessB::UpdateInput()
{
	if (m_ProcessBSourceInfo.ScrCount >= m_ProcessBSourceInfo.NeedCount)
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

// 재료만큼 뺀다
void UI_ProcessB::JuicyThis()
{
	// 앨리 상태
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->WaitDone(EELLIE_STATE::Juicy);
	}

	if (nullptr == UI_Inventory::MainInventory)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return;
	}

	UI_Inventory::MainInventory->PopItem(m_ProcessBSourceInfo.ScrName, 2);

	if (nullptr == ProcessManager)
	{
		MsgBoxAssert("가공 매니저가 존재하지 않습니다.");
		return;
	}

	ProcessManager->CreatedProductName = m_ProcessBProductInfo.ProductName;

	Off();
}
