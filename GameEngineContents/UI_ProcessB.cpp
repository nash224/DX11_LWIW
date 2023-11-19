#include "PreCompile.h"
#include "UI_ProcessB.h"

#include "IngredientData.h"

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
	SourceInfo.SourceRenderer = nullptr;
	ProcessManager = nullptr;
}

void UI_ProcessB::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// 2��°â �̴ϼ�
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

	BaseRenderer = CreateComponent<GameEngineUIRenderer>();
	BaseRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, BaseDepth));
	BaseRenderer->SetSprite("Process_Base.png");

	FrameRenderer = CreateComponent<GameEngineUIRenderer>();
	FrameRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, FrameDepth));
	FrameRenderer->SetSprite("Process_B_Contents.png");

	
	ProductInfo.ProductRenderer = CreateComponent<GameEngineUIRenderer>();
	ProductInfo.ProductRenderer->Transform.SetLocalPosition(float4(2.0f, 113.0f, IconDepth));

	SourceInfo.SourceRenderer= CreateComponent<GameEngineUIRenderer>();
	SourceInfo.SourceRenderer->Transform.SetLocalPosition(float4(-76.0f, -1.0f, IconDepth));
	
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
	ProductInfo.ProductName = _ProductName;

	if (nullptr == ProductInfo.ProductRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	ProductInfo.ProductRenderer->SetSprite(_ProductName.data() + std::string(".png"));
}

void UI_ProcessB::SourceInfoSetting(std::string_view _ProductName, int _ScrCount)
{
	std::weak_ptr<IngredientData> Data = IngredientData::Find(_ProductName);
	if (true == Data.expired())
	{
		MsgBoxAssert("��ϵ��� ���� �����͸� �����Ϸ� �߽��ϴ�.");
		return;
	}

	SourceInfo.ScrName = Data.lock()->SourceName;
	SourceInfo.NeedCount = Data.lock()->SourceCount;
	SourceInfo.ScrCount = _ScrCount;

	if (nullptr == SourceInfo.SourceRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	SourceInfo.SourceRenderer->SetSprite(Data.lock()->SourceName + std::string(".png"));
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
			MsgBoxAssert("�������� �ʴ� �������Դϴ�.");
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
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return;
	}

	UI_Inventory::MainInventory->PopItem(SourceInfo.ScrName, SourceInfo.NeedCount);

	if (nullptr == ProcessManager)
	{
		MsgBoxAssert("���� �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	ProcessManager->CreatedProductName = ProductInfo.ProductName;

	Off();
}
