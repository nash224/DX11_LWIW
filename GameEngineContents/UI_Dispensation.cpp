#include "PreCompile.h"
#include "UI_Dispensation.h"

#include "UIManager.h"
#include "UI_Inventory.h"

#include "ProductRecipeData.h"

#include "AlchemyPot.h"
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
	GameEngineInput::AddInputObject(this);
}

void UI_Dispensation::Update(float _Delta)
{
	UpdateKey();
}

void UI_Dispensation::Release()
{
	Base = nullptr;
	Frame = nullptr;
	EmptySlot = nullptr;
	fire_icon_1 = nullptr;
	fire_icon_2 = nullptr;
	Fire_Gauge = nullptr;
	Fire_Gauge_Pin = nullptr;
	Direction_None = nullptr;
	Direction_CounterClockwise = nullptr;
	Direction_Clockwise = nullptr;
	AlchemyPotPtr = nullptr;

	DispensationSlot.clear();
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

	Base = CreateComponent<GameEngineUIRenderer>();
	Base->Transform.SetLocalPosition(float4(0.0f, 10.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base)));
	Base->SetSprite("Dispensation_Base.png");

	Frame = CreateComponent<GameEngineUIRenderer>();
	Frame->Transform.SetLocalPosition(float4(0.0f, 20.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	Frame->SetSprite("dispensation_partsb.png");

	EmptySlot = CreateComponent<GameEngineUIRenderer>();
	EmptySlot->Transform.SetLocalPosition(float4(0.0f, 149.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment)));
	EmptySlot->SetSprite("dispensation_itemslot_set.png");

	fire_icon_1 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_1->Transform.SetLocalPosition(float4(-88.0f, 8.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_1->SetSprite("dispensation_fire_icon_1.png");

	fire_icon_2 = CreateComponent<GameEngineUIRenderer>();
	fire_icon_2->Transform.SetLocalPosition(float4(88.0f, 8.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Frame)));
	fire_icon_2->SetSprite("dispensation_fire_icon_2.png");

	Fire_Gauge = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge->Transform.SetLocalPosition(float4(0.0f, 57.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment)));
	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", static_cast<int>(CurFire));

	Fire_Gauge_Pin = CreateComponent<GameEngineUIRenderer>();
	Fire_Gauge_Pin->Transform.SetLocalPosition(float4(0.0f, 30.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component)));
	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", static_cast<int>(CurFire));

	Direction_None = CreateComponent<GameEngineUIRenderer>();
	Direction_None->Transform.SetLocalPosition(float4(0.0f, -62.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_None->SetSprite("Dispensation_Direction_None_Check.png");

	Direction_CounterClockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_CounterClockwise->Transform.SetLocalPosition(float4(-72.0f, -62.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	Direction_Clockwise = CreateComponent<GameEngineUIRenderer>();
	Direction_Clockwise->Transform.SetLocalPosition(float4(72.0f, -62.0f, DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component)));
	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");


	std::vector<ButtonInfoParameter> Paras =
	{
		{ EBUTTONTYPE::Z, "재료 선택"},
		{ EBUTTONTYPE::QW, "불 조절"},
		{ EBUTTONTYPE::ER, "국자 젓기"},
		{ EBUTTONTYPE::X, "닫기"},
		{ EBUTTONTYPE::C, "조제 시작"},
	};

	UIGuide.SetGuideInfo(this, Paras);
	UIGuide.On();

	DispensationSlot.resize(3);

	for (int i = 0; i < DispensationSlot.size(); i++)
	{
		float4 Position = float4(-72.0f + (72.0f * i), 149.0f);
		Position.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Component);

		DispensationSlot[i].ItemImg = CreateComponent<GameEngineUIRenderer>();
		DispensationSlot[i].ItemImg->Transform.SetLocalPosition(Position);
		DispensationSlot[i].ItemImg->Off();
	}
}


/////////////////////////////////////////////////////////////////////////////////////

void UI_Dispensation::Open()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	UIManager::MainUIManager->OpenInventory(EINVENTORYMODE::Dispensation);

	On();
}

void UI_Dispensation::Close()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	UIManager::MainUIManager->CloseInventory();

	Off();

	Reset();
}

// 연금탭을 초기화시킵니다.
void UI_Dispensation::Reset()
{
	if (nullptr != Fire_Gauge && nullptr != Fire_Gauge_Pin)
	{
		CurFire = EBREWING_FIRE::Three;
		Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", static_cast<int>(CurFire));
		Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", static_cast<int>(CurFire));
	}

	ChangeAllDirectionReset();
	CurStir = EBREWING_DIRECTION::StirNone;
	Direction_None->SetSprite("Dispensation_Direction_None_Check.png");

	ClearSlotInfo();

	MainDispensation = this;
}

bool UI_Dispensation::SelectThis(std::string_view _ItemName, int _ItemCount)
{
	int EmptySlotNumber = ReturnEmptySlot();

	DispensationSlotInfo* SlotInfo = FindSlot(_ItemName);
	if (-1 != EmptySlotNumber && nullptr == SlotInfo)
	{
		DispensationSlot[EmptySlotNumber].ItemName = _ItemName;
		DispensationSlot[EmptySlotNumber].ItemCount = _ItemCount;

		if (nullptr == DispensationSlot[EmptySlotNumber].ItemImg)
		{
			MsgBoxAssert("렌더러를 생성하지 않고 사용하려 했습니다.");
			return false;
		}
		DispensationSlot[EmptySlotNumber].ItemImg->SetSprite(_ItemName.data() + std::string(".png"));
		DispensationSlot[EmptySlotNumber].ItemImg->On();

		return true;
	}

	MsgBoxAssert("지정한 슬롯에 아이템을 넣지 못했습니다.");
	return false;
}

int UI_Dispensation::ReturnEmptySlot()
{
	for (int i = 0; i < DispensationSlot.size(); i++)
	{
		if (true == DispensationSlot[i].ItemName.empty())
		{
			return i;
		}
	}

	return -1;
}

DispensationSlotInfo* UI_Dispensation::FindSlot(std::string_view _ItemName)
{
	for (size_t i = 0; i < DispensationSlot.size(); i++)
	{
		DispensationSlotInfo& Info = DispensationSlot[i];
		if (Info.ItemName == _ItemName)
		{
			return &Info;
		}
	}

	return nullptr;
}

bool UI_Dispensation::UnSelectThis(std::string_view _ItemName)
{
	DispensationSlotInfo* Info = FindSlot(_ItemName);
	if (nullptr == Info)
	{
		return false;
	}

	Info->ItemName = "";
	Info->ItemCount = 0;
	if (nullptr == Info->ItemImg)
	{
		MsgBoxAssert("존재하지 않는 렌더러를 참조하려 했습니다.");
		return false;
	}

	Info->ItemImg->Off();

	return true;
}

void UI_Dispensation::ClearSlotInfo()
{
	for (size_t i = 0; i < DispensationSlot.size(); i++)
	{
		DispensationSlot[i].ItemCount = 0;
		DispensationSlot[i].ItemName = "";
		DispensationSlot[i].ItemImg->Off();
	}
}


void UI_Dispensation::Dispensation()
{
	const std::vector<ProductRecipeData::MaterialInfo> infoArray =
	{
		{DispensationSlot[0].ItemName, DispensationSlot[0].ItemCount },
		{DispensationSlot[1].ItemName, DispensationSlot[1].ItemCount},
		{DispensationSlot[2].ItemName, DispensationSlot[2].ItemCount}
	};
	const ProductRecipeData CurRecipeData = ProductRecipeData{ infoArray, EBREWING_DIFFICULTY::Normal, CurStir, CurFire};

	if (true == CheckDispensation(CurRecipeData))
	{
		for (size_t i = 0; i < DispensationSlot.size(); i++)
		{
			PopDispensationMaterial(DispensationSlot[i].ItemName);
		}
	}
	else
	{
		CreatedProductName.clear();
	}

	AlchemyPotPtr->DispensatePotion(CreatedProductName);

	Off();

	if (nullptr == UI_Inventory::MainInventory)
	{
		MsgBoxAssert("인벤토리를 모릅니다.");
		return;
	}

	UI_Inventory::MainInventory->Off();
}

bool UI_Dispensation::CheckDispensation(const ProductRecipeData& _Data)
{
	std::map<std::string, std::shared_ptr<ProductRecipeData>>& NameData = ProductRecipeData::GetAllData();
	for (std::pair<std::string, std::shared_ptr<ProductRecipeData>> Data : NameData)
	{
		std::shared_ptr<ProductRecipeData> Recpie = Data.second;
		if (_Data == Recpie.get())
		{
			CreatedProductName = Recpie->ProductName;
			return true;
		}
	}

	return false;
}

// 연금된 아이템을 제거합니다.
void UI_Dispensation::PopDispensationMaterial(std::string_view _ItemName)
{
	if (false == _ItemName.empty())
	{
		if (nullptr == UI_Inventory::MainInventory)
		{
			MsgBoxAssert("인벤토리가 존재하지 않습니다.");
			return;
		}

		const std::uint32_t _ItemCount = ProductRecipeData::GetNeedMaterialCount(CreatedProductName, _ItemName);

		UI_Inventory::MainInventory->PopItem(_ItemName, _ItemCount);
	}
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
		PrevStirOption();
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		NextStirOption();
		return;
	}
}


// 불 강도 낮추기
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
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

// 불 강도 높이기
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
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Fire_Gauge->SetSprite("Dispensation_Fire_Gauge.png", iFire);

	if (nullptr == Fire_Gauge_Pin)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Fire_Gauge_Pin->SetSprite("dispensation_fire_gauge_pin.png", iFire);

	CurFire = static_cast<EBREWING_FIRE>(iFire);
}

// 이전방향
void UI_Dispensation::PrevStirOption()
{
	if (EBREWING_DIRECTION::StirLeft == CurStir)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurStir)
	{
		Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise_Check.png");
		CurStir = EBREWING_DIRECTION::StirLeft;
	}

	if (EBREWING_DIRECTION::StirRight == CurStir)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurStir = EBREWING_DIRECTION::StirNone;
	}
}

// 다음 방향
void UI_Dispensation::NextStirOption()
{
	if (EBREWING_DIRECTION::StirRight == CurStir)
	{
		return;
	}

	ChangeAllDirectionReset();

	if (EBREWING_DIRECTION::StirNone == CurStir)
	{
		Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise_Check.png");
		CurStir = EBREWING_DIRECTION::StirRight;
	}

	if (EBREWING_DIRECTION::StirLeft == CurStir)
	{
		Direction_None->SetSprite("Dispensation_Direction_None_Check.png");
		CurStir = EBREWING_DIRECTION::StirNone;
	}
}


// 선택하지 않은 휘젓기 스프라이트 이름이 
void UI_Dispensation::ChangeAllDirectionReset()
{
	if (nullptr == Direction_None)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Direction_None->SetSprite("Dispensation_Direction_None.png");

	if (nullptr == Direction_CounterClockwise)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Direction_CounterClockwise->SetSprite("Dispensation_Direction_CounterClockwise.png");

	if (nullptr == Direction_Clockwise)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Direction_Clockwise->SetSprite("Dispensation_Direction_Clockwise.png");
}