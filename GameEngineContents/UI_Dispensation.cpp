#include "PreCompile.h"
#include "UI_Dispensation.h"

#include "UIManager.h"
#include "UI_Inventory.h"

#include "ProductRecipeData.h"

#include "Ellie.h"


UI_Dispensation* UI_Dispensation::MainDispensation = nullptr;
UI_Dispensation::UI_Dispensation() 
{
}

UI_Dispensation::~UI_Dispensation() 
{
}


void UI_Dispensation::Start()
{
	UI_ToggleActor::Start();

	GameEngineInput::AddInputObject(this);
}

void UI_Dispensation::Update(float _Delta)
{
	UI_ToggleActor::Update(_Delta);

	UpdateKey();
}

void UI_Dispensation::Release()
{
	m_Base = nullptr;
	m_Frame = nullptr;
	m_Empty_Slot = nullptr;
	fire_icon_1 = nullptr;
	fire_icon_2 = nullptr;
	Fire_Gauge = nullptr;
	Fire_Gauge_Pin = nullptr;
	Direction_None = nullptr;
	Direction_CounterClockwise = nullptr;
	Direction_Clockwise = nullptr;

	m_DispensationSlotInfo.clear();
}

void UI_Dispensation::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainDispensation = this;
}

void UI_Dispensation::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_Dispensation::Init()
{
	RendererSetting();

	MainDispensation = this;
	
	Off();
}


void UI_Dispensation::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Dispensation_Fire_Gauge.png"))
	{
		GameEngineSprite::CreateCut("Dispensation_Fire_Gauge.png", 5, 1);
		GameEngineSprite::CreateCut("dispensation_fire_gauge_pin.png", 5, 1);
	}

	m_Base = CreateComponent<GameEngineUIRenderer>();
	m_Base->Transform.SetLocalPosition(float4(0.0f, 10.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base)));
	m_Base->SetSprite("Dispensation_Base.png");

	m_Frame = CreateComponent<GameEngineUIRenderer>();
	m_Frame->Transform.SetLocalPosition(float4(0.0f, 20.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	m_Frame->SetSprite("dispensation_partsb.png");

	m_Empty_Slot = CreateComponent<GameEngineUIRenderer>();
	m_Empty_Slot->Transform.SetLocalPosition(float4(0.0f, 149.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	m_Empty_Slot->SetSprite("dispensation_itemslot_set.png");

	fire_icon_1 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_1->Transform.SetLocalPosition(float4(-88.0f, 8.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_1->SetSprite("dispensation_fire_icon_1.png");

	fire_icon_2 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_2->Transform.SetLocalPosition(float4(88.0f, 8.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_2->SetSprite("dispensation_fire_icon_2.png");

	Fire_Gauge = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge->Transform.SetLocalPosition(float4(0.0f, 57.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment)));
	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", static_cast<int>(CurFire));
	
	Fire_Gauge_Pin = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge_Pin->Transform.SetLocalPosition(float4(0.0f, 30.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", static_cast<int>(CurFire));

	Direction_None = CreateComponent<GameEngineUIRenderer>();
	Direction_None->Transform.SetLocalPosition(float4(0.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_None->SetSprite("Dispensation_Direction_None_Check.png");

	Direction_CounterClockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_CounterClockwise->Transform.SetLocalPosition(float4(-72.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	Direction_Clockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_Clockwise->Transform.SetLocalPosition(float4(72.0f, -62.0f, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");


	m_DispensationSlotInfo.resize(3);

	for (int i = 0; i < m_DispensationSlotInfo.size(); i++)
	{
		float4 Position = float4(-72.0f + (72.0f * i), 149.0f);
		Position.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Component);

		m_DispensationSlotInfo[i].ItemImg = CreateComponent<GameEngineUIRenderer>();
		m_DispensationSlotInfo[i].ItemImg->Transform.SetLocalPosition(Position);
		m_DispensationSlotInfo[i].ItemImg->Off();
	}
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Dispensation::Open()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->OpenInventory(EINVENTORYMODE::Dispensation);
	
	On();
}

void UI_Dispensation::Close()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	UIManager::MainUIManager->CloseInventory();

	Off();

	Reset();
}

// �������� �ʱ�ȭ��ŵ�ϴ�.
void UI_Dispensation::Reset()
{
	if (nullptr != Fire_Gauge && nullptr != Fire_Gauge_Pin)
	{
		CurFire = EBREWING_FIRE::Three;
		Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", static_cast<int>(CurFire));
		Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", static_cast<int>(CurFire));
	}

	ChangeAllDirectionReset();
	CurDirection = EBREWING_DIRECTION::StirNone;
	Direction_None->SetSprite("Dispensation_Direction_None_Check.png");

	ClearSlotInfo();

	MainDispensation = this;
}

// �κ��丮���� ������ �������ݴϴ�.
bool UI_Dispensation::SelectThis(std::string_view _ItemName, int _ItemCount)
{
	// �� ���� Ȯ���ϰ�
	int EmptySlotNumber = IsEmptySlot();

	// ������ ������ �̸��� �ִ��� Ȯ���ؼ�
	DispensationSlotInfo* SlotInfo = Find(_ItemName);
	if (-1 != EmptySlotNumber && nullptr == SlotInfo)
	{
		// ������ �ֽ��ϴ�.
		m_DispensationSlotInfo[EmptySlotNumber].ItemName = _ItemName;
		m_DispensationSlotInfo[EmptySlotNumber].ItemCount = _ItemCount;

		if (nullptr == m_DispensationSlotInfo[EmptySlotNumber].ItemImg)
		{
			MsgBoxAssert("�������� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
			return false;
		}
		m_DispensationSlotInfo[EmptySlotNumber].ItemImg->SetSprite(_ItemName.data() + std::string(".png"));
		m_DispensationSlotInfo[EmptySlotNumber].ItemImg->On();

		return true;
	}

	MsgBoxAssert("������ ���Կ� �������� ���� ���߽��ϴ�.");
	return false;
}

// ���� ������ ������ -1�� ��ȯ�մϴ�.
int UI_Dispensation::IsEmptySlot()
{
	for (int i = 0; i < m_DispensationSlotInfo.size(); i++)
	{
		if ("" == m_DispensationSlotInfo[i].ItemName)
		{
			return i;
		}
	}

	return -1;
}

DispensationSlotInfo* UI_Dispensation::Find(std::string_view _ItemName)
{
	for (size_t i = 0; i < m_DispensationSlotInfo.size(); i++)
	{
		DispensationSlotInfo& Info = m_DispensationSlotInfo[i];

		if ("" != Info.ItemName)
		{
			return &Info;
		}
	}

	return nullptr;
}

// ���õ� ������ ���ݴϴ�.
bool UI_Dispensation::UnSelectThis(std::string_view _ItemName)
{
	DispensationSlotInfo* Info = Find(_ItemName);
	if (nullptr == Info)
	{
		return false;
	}

	Info->ItemName = "";
	Info->ItemCount = 0;
	if (nullptr == Info->ItemImg)
	{
		MsgBoxAssert("�������� �ʴ� �������� �����Ϸ� �߽��ϴ�.");
		return false;
	}

	Info->ItemImg->Off();

	return true;
}

// ���� ������ �ʱ�ȭ�մϴ�.
void UI_Dispensation::ClearSlotInfo()
{
	for (size_t i = 0; i < m_DispensationSlotInfo.size(); i++)
	{
		m_DispensationSlotInfo[i].ItemCount = 0;
		m_DispensationSlotInfo[i].ItemName = "";
		m_DispensationSlotInfo[i].ItemImg->Off();
	}
}


// �����ǰ� ��ġ�ϸ� ������ �մϴ�.
void UI_Dispensation::Dispensation()
{
	// �ٸ� ����
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->WaitDone();
	}

	ProductRecipeData CurRecipeData = {"", "", EBREWING_DIFFICULTY::Normal, CurDirection, CurFire, 
		m_DispensationSlotInfo[0].ItemName, m_DispensationSlotInfo[0].ItemCount,
		m_DispensationSlotInfo[1].ItemName, m_DispensationSlotInfo[1].ItemCount,
		m_DispensationSlotInfo[2].ItemName, m_DispensationSlotInfo[2].ItemCount };

	// ���ݰ���� �б��Դϴ�
	if (false == CheckDispensation(CurRecipeData))
	{

	}
	else
	{
		//UI_Inventory::MainInventory->PopItem(m_ProcessBSourceInfo.ScrName, 2);

		//if (nullptr == ProcessManager)
		//{
		//	MsgBoxAssert("���� �Ŵ����� �������� �ʽ��ϴ�.");
		//	return;
		//}

		//ProcessManager->CreatedProductName = m_ProcessBProductInfo.ProductName;
	}



	Off();
}

// ��ġ�ϴ� �����ǰ� �ִ��� �˻��մϴ�.
bool UI_Dispensation::CheckDispensation(const ProductRecipeData& _Data)
{
	std::map<std::string, std::shared_ptr<ProductRecipeData>>& NameData = ProductRecipeData::GetAllData();
	for (std::pair<std::string, std::shared_ptr<ProductRecipeData>> Data : NameData)
	{
		std::shared_ptr<ProductRecipeData> Recpie = Data.second;
		if (_Data == Recpie.get())
		{
			return true;
		}
	}

	return false;
}


/////////////////////////////////////////////////////////////////////////////////////


void UI_Dispensation::UpdateKey()
{
	if (true == GameEngineInput::IsDown('C', this))
	{
		Dispensation();
		return;
	}

	if (true == GameEngineInput::IsDown('X', this))
	{
		Close();
		return;
	}

	if (true == GameEngineInput::IsDown('Q', this))
	{
		LowHit();
		return;
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		HighHit();
		return;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		PrevDirection();
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		NextDirection();
		return;
	}
}


// �� ���� ���߱�
void UI_Dispensation::LowHit()
{
	if (EBREWING_FIRE::One == CurFire)
	{
		return;
	}

	int iFire = static_cast<int>(CurFire);
	--iFire;
	
	if (nullptr == Fire_Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}
	
	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

// �� ���� ���̱�
void UI_Dispensation::HighHit()
{
	if (EBREWING_FIRE::Five == CurFire)
	{
		return;
	}


	int iFire = static_cast<int>(CurFire);
	++iFire;

	if (nullptr == Fire_Gauge)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

// ��������
void UI_Dispensation::PrevDirection()
{
	if (EBREWING_DIRECTION::StirLeft == CurDirection)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurDirection)
	{
		Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise_Check.png");
		CurDirection = EBREWING_DIRECTION::StirLeft;
	}

	if (EBREWING_DIRECTION::StirRight == CurDirection)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurDirection = EBREWING_DIRECTION::StirNone;
	}
}

// ���� ����
void UI_Dispensation::NextDirection()
{
	if (EBREWING_DIRECTION::StirRight == CurDirection)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurDirection)
	{
		Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise_Check.png");
		CurDirection = EBREWING_DIRECTION::StirRight;
	}

	if (EBREWING_DIRECTION::StirLeft == CurDirection)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurDirection = EBREWING_DIRECTION::StirNone;
	}
}


// �������� ���� ������ ��������Ʈ �̸��� 
void UI_Dispensation::ChangeAllDirectionReset()
{
	if (nullptr == Direction_None)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_None->SetSprite("Dispensation_Direction_None.png");

	if (nullptr == Direction_CounterClockwise)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	if (nullptr == Direction_Clockwise)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");
}