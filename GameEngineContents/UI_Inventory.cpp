#include "PreCompile.h"
#include "UI_Inventory.h"


#include "UI_DropManager.h"
#include "UI_Dispensation.h"

// 데이터 배열은 1차원 배열로 설정합니다.
void Inventory::Init()
{
	size_t Amount = Max_XSlot * Max_YSlot;

	InventoryData.resize(Amount);
}


// 아이템을 데이터에 넣습니다. 
// 인벤토리에 동일한 이름의 아이템이 있으면 아이템의 수를 더하고, 아이템이 없으면 빈 슬롯에 넣습니다.
void Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	size_t LockNumber = Max_XSlot * InventoryParent->UnlockSlotY;

	int Value = IsContain(_ItemName);
	// 데이터에 없으면
	if (0 == Value)
	{
		// 빈자리가 있으면 빈자리를 찾아서
		for (size_t i = 0; i < LockNumber; i++)
		{
			// 넣습니다.
			if ("" == InventoryData[i].SourceName)
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = static_cast<int>(i);
				break;
			}

			// 인벤토리가 다 찼다는 의미로 PopUp UI를 요청합니다.
			if (i == LockNumber - 1)
			{
				// PopUp UI
				return;
			}
		}
	}
	else
	{
		Value = Find(_ItemName);
		// 있으면
		InventoryData[Value].ItemCount += _Count;
	}

	InventoryParent->DisplayItem(static_cast<size_t>(Value), _ItemName);
}

// 아이템을 지정수만큼 뺍니다.
void Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
 	int SlotNumber = Find(_ItemName);
	InventoryData[SlotNumber].ItemCount -= _Count;
	if (0 == InventoryData[SlotNumber].ItemCount)
	{
		ClearData(SlotNumber);
	}
	
}

// 빈슬롯이 있는지 검사합니다.
bool Inventory::CheckEmptySlot(std::string_view _ItemName)
{
	int UnlockSlotCount = UI_Inventory::UnlockSlotY * Max_YSlot;

	for (size_t i = 0; i < UnlockSlotCount; i++)
	{
		if (0 == InventoryData[i].ItemCount)
		{
			return true;
		}
	}

	if (0 != IsContain(_ItemName))
	{
		return true;
	}

	return false;
}

// 데이터에 동일한 이름을 가진 아이템이 있는지 검사합니다.
int Inventory::IsContain(std::string_view _ItemName)
{
	std::string ItemName = _ItemName.data();
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		if (ItemName == InventoryData[y].SourceName)
		{
			return InventoryData[y].ItemCount;
		}
	}

	return 0;
}

// 해당 슬롯에 아이템이 있는지 확인합니다.
int Inventory::IsContain(unsigned int _X, unsigned int _Y)
{
	int MaxSlot = Max_XSlot;
	unsigned int Value  = _Y * MaxSlot + _X;
	if ("" != InventoryData[Value].SourceName)
	{
		return InventoryData[Value].ItemCount;
	}

	return 0;
}

InventoryInfo& Inventory::ReturnInventoryInfo(unsigned int _X, unsigned int _Y)
{
	unsigned int Value = _Y * Max_XSlot + _X;
	return InventoryData[Value];
}


int Inventory::Find(std::string_view _ItemName)
{
	for (size_t i = 0; i < InventoryData.size(); i++)
	{
		if (_ItemName == InventoryData[i].SourceName)
		{
			return static_cast<int>(i);
		}
	}

	MsgBoxAssert("데이터에서 아이템을 찾지 못했습니다.");
	return -1;
}



void Inventory::ClearData(const unsigned int _X, const unsigned int _Y)
{
	if (0 == IsContain(_X, _Y))
	{
		MsgBoxAssert("존재하지 않는 슬롯을 지울려고 했습니다.");
		return;
	}

	if (true == InventoryData.empty())
	{
		MsgBoxAssert("데이터에 아무것도 들어있지 않습니다.");
		return;
	}

	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("부모를 모릅니다. 설정하세요");
		return;
	}

	int MaxSlot = Max_XSlot;

	int Value = _Y * MaxSlot + _X;

	InventoryData[Value].SourceName = "";
	InventoryData[Value].ItemCount = 0;

	InventoryParent->EraseSlotImg(_X, _Y);
}


void Inventory::ClearData(const unsigned int _SlotNumber)
{
	InventoryData[_SlotNumber].SourceName = "";
	InventoryData[_SlotNumber].ItemCount = 0;

	int MaxSlot = Max_XSlot;
	int XSlot = _SlotNumber % MaxSlot;
	int YSlot = _SlotNumber / MaxSlot;

	InventoryParent->EraseSlotImg(XSlot, YSlot);
}

// 인벤토리를 갱신합니다.
void Inventory::RenewInventory()
{
	if (nullptr == InventoryParent)
	{
		MsgBoxAssert("부모를 설정하지 않고 이미지를 띄울 수 없습니다.");
		return;
	}

	for (size_t i = 0; i < InventoryData.size(); i++)
	{
		std::string_view FileName = InventoryData[i].SourceName;
		if ("" != FileName)
		{
			InventoryParent->DisplayItem(i, FileName);
		}
	}
}



std::shared_ptr<Inventory> UI_Inventory::Data = nullptr;
UI_Inventory* UI_Inventory::MainInventory = nullptr;
unsigned int UI_Inventory::UnlockSlotY = 0;
UI_Inventory::UI_Inventory() 
{
}

UI_Inventory::~UI_Inventory() 
{
}


void UI_Inventory::Start()
{
	UI_ToggleActor::Start();
}

void UI_Inventory::Update(float _Delta)
{
	if (this != MainInventory)
	{
		OnLevelStart();
	}

	m_InventoryState.Update(_Delta);
}

void UI_Inventory::Release()
{
	Data = nullptr;
	MainInventory = nullptr;

	m_DropManager = nullptr;
	m_InventoryBase = nullptr;
	m_CursorComposition.Cursor = nullptr;
	m_CursorComposition.CursorOutline = nullptr;
	m_CursorComposition.NameTooltip = nullptr;

	InventorySlotArray.clear();
}

void UI_Inventory::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Inventory::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 인벤토리 배열과 데이터 배열을 생성합니다.
// 단, 데이터 배열은 한번만 생성됩니다.
void UI_Inventory::Init()
{
	if (nullptr == Data)
	{
		CreateData();

		UnlockSlotY = 2;
	}


	// 렌더 배열 만들고
	CreateBase();
	CreateSlotArray();
	CreateCursor();
	StateSetting();

	// 아이템 획득 알림창 매니저입니다.
	CreateNoticeDropManager();

	ExternUISetting();

	LockSlot(UnlockSlotY);
	Transform.AddLocalPosition({ -288.0f , 28.0f });

	// 부모 설정 후, 그립니다.
	OnLevelStart();
}

// Base Create
void UI_Inventory::CreateBase()
{
	m_InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Base);
	if (nullptr == m_InventoryBase)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_InventoryBase->SetSprite("Inventory_Base.png");
	float4 BasePosition = { 0.0f , 0.0f , GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Base) };
	m_InventoryBase->Transform.AddLocalPosition(BasePosition);
}

// 렌더 2차원 배열을 생성합니다.
void UI_Inventory::CreateSlotArray()
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("Inventory_Empty_Slot.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	m_GridScale = Texture->GetScale();

	InventorySlotArray.resize(Max_YSlot);
	for (size_t y = 0; y < InventorySlotArray.size(); y++)
	{
		InventorySlotArray[y].resize(Max_XSlot);
		for (size_t x = 0; x < Max_XSlot; x++)
		{
			float4 Pos = CalculateIndexToPos(x, y);

			std::shared_ptr<GameEngineUIRenderer> Empty = CreateComponent<GameEngineUIRenderer>();
			Empty->SetSprite("Inventory_Empty_Slot.png");
			Pos.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Attachment);
			Empty->Transform.SetLocalPosition(Pos);


			InventorySlotArray[y][x].SlotEmpty = Empty;

			std::shared_ptr<GameEngineUIRenderer> Slot = CreateComponent<GameEngineUIRenderer>();
			Pos.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Icon);
			Slot->Transform.SetLocalPosition(Pos);
			Slot->Off();

			InventorySlotArray[y][x].Slot = Slot;
		}
	}
}


void UI_Inventory::StateSetting()
{
	CreateStateParameter NormalPara;
	NormalPara.Start = [&](GameEngineState* _Parent) {m_Mode = EINVENTORYMODE::Normal; };
	NormalPara.Stay = std::bind(&UI_Inventory::UpdateInventory, this, std::placeholders::_1, std::placeholders::_2);
	m_InventoryState.CreateState(EINVENTORYMODE::Normal, NormalPara);

	CreateStateParameter DispensationPara;
	DispensationPara.Start = [&](GameEngineState* _Parent) {IsJustOpen = true , m_Mode = EINVENTORYMODE::Dispensation; };
	DispensationPara.Stay = std::bind(&UI_Inventory::UpdateDispensation, this, std::placeholders::_1, std::placeholders::_2);
	m_InventoryState.CreateState(EINVENTORYMODE::Dispensation, DispensationPara);

	m_InventoryState.ChangeState(EINVENTORYMODE::Normal);
}


void UI_Inventory::CreateCursor()
{
	if (nullptr == GameEngineSprite::Find("Inventory_Cursor.png"))
	{
		GameEngineSprite::CreateCut("Inventory_Cursor.png", 2, 1);
	}

	std::shared_ptr<GameEngineUIRenderer> CurSor = CreateComponent<GameEngineUIRenderer>();
	CurSor->CreateAnimation("Cursor", "Inventory_Cursor.png", CursorInter);
	CurSor->ChangeAnimation("Cursor");
	CurSor->AutoSpriteSizeOn();
	m_CursorComposition.Cursor = CurSor;

	std::shared_ptr<GameEngineUIRenderer> CurSorOutLine = CreateComponent<GameEngineUIRenderer>();
	CurSorOutLine->SetSprite("Inventory_CursorOutline.png");
	m_CursorComposition.CursorOutline = CurSorOutLine;

	std::shared_ptr<GameEngineUIRenderer> NameTooltip = CreateComponent<GameEngineUIRenderer>();
	NameTooltip->SetSprite("Inventory_NameTooltip.png");
	NameTooltip->Off();
	m_CursorComposition.NameTooltip = NameTooltip;
	

	CursorThis(0, 0);
}


void UI_Inventory::CreateNoticeDropManager()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_DropManager = CurLevel->CreateActor<UI_DropManager>(EUPDATEORDER::UIMagnaer);
	if (nullptr == m_DropManager)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_DropManager->Init();
}

// 전역으로 한번만 실행됩니다.
void UI_Inventory::CreateData()
{
#ifdef _DEBUG
	static bool InitCheck = false;
	if (true == InitCheck)
	{
		MsgBoxAssert("데이터를 2번 생성하려 했습니다.");
		return;
	}

	InitCheck = true;

#endif // DEBUG


	Data = std::make_shared<Inventory>();
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터를 생성하지 못했습니다.");
		return;
	}

	Data->InventoryParent = this;

	Data->Init();
}

void UI_Inventory::ExternUISetting()
{
	SelectItem.resize(3);

	for (size_t i = 0; i < SelectItem.size(); i++)
	{
		SelectItem[i].Cursor = CreateComponent<GameEngineUIRenderer>();
		SelectItem[i].Cursor->SetSprite("Inventory_SelectCursor.png");
		SelectItem[i].Cursor->Off();
	}
}



/////////////////////////////////////////////////////////////////////////////////////

// UnlockSlot을 넣어주면 사용하지 못하는 슬롯에 잠금장치 이미지가 생성됩니다.
void UI_Inventory::LockSlot(const unsigned int _Y)
{
	for (size_t y = _Y; y < InventorySlotArray.size(); y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("존재하지 않는 슬롯을 참조하려고 했습니다.");
				return;
			}

			Slot->SetSprite("Inventory_SlotLock.png");
			Slot->On();
		}
	}
}



// 아이템을 넣어달라고 UI를 통해 Data에 요청합니다.
void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count/* = 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터에 접근하려 했습니다.");
		return;
	}

	// 빈슬롯이 있는지 검사하고
	if (false == Data->CheckEmptySlot(_ItemName))
	{
		// UI Dont Empty Slot Alert!!
		OutputDebugStringA("빈슬롯이 없습니다.");
		return;
	}

	Data->PushItem(_ItemName, _Count);

	// 알림 시스템이기 때문에 터트리진 않습니다.
	if (nullptr != MainInventory && nullptr != MainInventory->m_DropManager)
	{
		MainInventory->m_DropManager->NoticeItemDrop(_ItemName);
	}
}

void UI_Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	int ItemCount = Data->IsContain(_ItemName);

	if (ItemCount < static_cast<int>(_Count))
	{
		MsgBoxAssert("사용하려는 아이템의 수보다 적습니다. ");
		return;
	}

	Data->PopItem(_ItemName, _Count);
}

bool UI_Inventory::IsEmptySlot(std::string_view _ItemName)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return false;
	}


	return Data->CheckEmptySlot(_ItemName);
}

// 슬롯 줄 잠금해제
void UI_Inventory::UnlockSlot(const unsigned int _Count /*= 1*/)
{
	unsigned int PrevUnlockSlotY = UnlockSlotY;

	UnlockSlotY += _Count;

	if (UnlockSlotY > Max_YSlot)
	{
		UnlockSlotY = Max_YSlot;
	}

	if (PrevUnlockSlotY == UnlockSlotY)
	{
		return;
	}

	for (size_t y = PrevUnlockSlotY; y < UnlockSlotY; y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			if (nullptr == Slot)
			{
				MsgBoxAssert("존재하지 않는 슬롯에 접근하려 했습니다.");
				return;
			}

			Slot->Off();
		}
	}
}


void UI_Inventory::UsingOtherComponent(EINVENTORYMODE _Mode)
{
	m_InventoryState.ChangeState(_Mode);
}

int UI_Inventory::ReturnItemCount(std::string_view _ItemName)
{
	return Data->IsContain(_ItemName);
}



// 같은 부모로 설정해두면 이전레벨에 렌더링 될수있음으로 레벨이 바뀔때 부모를 바꿉니다. 
void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않는데 데이터의 부모를 바꾸려고 했습니다.");
		return;
	}

	Data->InventoryParent = this;
}

// 아이템을 띄웁니다.
void UI_Inventory::DisplayItem(const size_t _SlotNumber, std::string_view _FileName)
{
	size_t Number = _SlotNumber;
	size_t SlotX = Number % Max_XSlot;
	size_t SlotY = Number / Max_XSlot;

	std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[SlotY][SlotX].Slot;
	if (nullptr == Slot)
	{
		MsgBoxAssert("생성되지 않았거나 존재하지 않는 슬롯입니다.");
		return;
	}

	Slot->SetSprite(_FileName.data() + std::string(".png"));
	Slot->On();
}

// 인벤토리를 갱신하라고 요청받습니다.
void UI_Inventory::RenewInventory()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터에 접근하려 했습니다.");
		return;
	}

	Data->RenewInventory();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// 자식에서 해주고 싶은 행동을 수행합니다.
void UI_Inventory::OpenChild()
{
	CursorThis(0, 0);
}

void UI_Inventory::CloseChild()
{
	if (EINVENTORYMODE::Dispensation == m_Mode)
	{
		UnSelectAll();
	}

	m_InventoryState.ChangeState(EINVENTORYMODE::Normal);
}


// 좌표의 위치를 계산해줍니다.
float4 UI_Inventory::CalculateIndexToPos(const size_t _x, const size_t _y)
{
	if (false == IsFirstPosCalculated)
	{
		float4 HGridScale = m_GridScale.Half();
		FirstGridPosition.X = -((GridSpacing / 2.0f) + HGridScale.X) * ((static_cast<float>(Max_XSlot / 2) - 0.5f) * 2.0f);
		FirstGridPosition.Y = ((GridSpacing / 2.0f) + HGridScale.Y) * ((static_cast<float>(Max_YSlot / 2) - 0.5f) * 2.0f);

		IsFirstPosCalculated = true;
	}

	float4 TargetDistance = { static_cast<float>(_x) * (GridSpacing + m_GridScale.X) , -static_cast<float>(_y) * (GridSpacing + m_GridScale.Y) };
	float4 ReturnValue = FirstGridPosition + TargetDistance;
	return ReturnValue;
}


void UI_Inventory::CursorThis(const unsigned int _X, const unsigned int _Y)
{
	if (nullptr == m_CursorComposition.Cursor)
	{
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	float4 CursorPosition = CalculateIndexToPos(_X, _Y);
	CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor) };
	

	m_CursorComposition.Cursor->Transform.SetLocalPosition(CursorPosition);
	

	if (nullptr == m_CursorComposition.CursorOutline)
	{
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::CursorOutLine) };
	m_CursorComposition.CursorOutline->Transform.SetLocalPosition(CalculateIndexToPos(_X, _Y));

	if (nullptr == m_CursorComposition.NameTooltip)
	{
		MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
		return;
	}
	 
	// 데이터가 있으면
	if (0 != Data->IsContain(_X, _Y))
	{
		CursorPosition = CalculateIndexToPos(_X, _Y) + NameTagPositionBaseOnSlotCenter;
		CursorPosition = { CursorPosition.X , CursorPosition.Y, GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor) };
		m_CursorComposition.NameTooltip->Transform.SetLocalPosition(CursorPosition);
		m_CursorComposition.NameTooltip->On();
	}
	else
	{
		m_CursorComposition.NameTooltip->Off();
	}


	m_CurrentSlotX = _X;
	m_CurrentSlotY = _Y;
}

void UI_Inventory::ClearSlot(const unsigned int _X, const unsigned int _Y)
{
	if (this != Data->InventoryParent)
	{
		MsgBoxAssert("지정된 부모가 아닙니다. 확인해세요");
		return;
	}

	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	Data->ClearData(_X, _Y);
}

void UI_Inventory::EraseSlotImg(const int _X, const int _Y)
{
	if (nullptr == InventorySlotArray[_Y][_X].Slot)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	InventorySlotArray[_Y][_X].Slot->SetSprite("Inventory_None.png");
	CursorThis(_X, _Y);
}

void UI_Inventory::ClearAllSlotImg()
{
	for (size_t y = 0; y < UnlockSlotY; y++)
	{
		for (size_t x = 0; x < Max_XSlot; x++)
		{
			EraseSlotImg(static_cast<int>(x), static_cast<int>(y));
		}
	}
}

void UI_Inventory::OnLevelStart()
{
	// 레벨이 바뀔때마다 갱신해줍니다.
	ChangeDataParent();
	ClearAllSlotImg();
	RenewInventory();
	MainInventory = this;
	m_CurrentSlotX = 0;
	m_CurrentSlotY = 0;
	CursorThis(m_CurrentSlotX, m_CurrentSlotY);

	Close();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::UpdateInventory(float _Delta, GameEngineState* _Parent)
{
	UI_ToggleActor::Update(_Delta);

	DectedCloseInventory();
	UpdateCursor();

	// 임시코드
	if (true == GameEngineInput::IsPress(VK_CONTROL, this))
	{
		if (true == GameEngineInput::IsDown('3', this))
		{
			ClearSlot(m_CurrentSlotX, m_CurrentSlotY);
		}
	}

	OpenCheck = false;
}

void UI_Inventory::DectedCloseInventory()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('S', this))
		{
			Close();
			return;
		}
	}
}

bool UI_Inventory::UpdateCursor()
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		MoveCursor(-1, 0);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		MoveCursor(1, 0);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		MoveCursor(0, -1);
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		MoveCursor(0, 1);
		return true;
	}

	return false;
}

void UI_Inventory::MoveCursor(const int _X, const int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	m_CurrentSlotX += _X;
	m_CurrentSlotY += _Y;

	if (-1 == m_CurrentSlotX)
	{
		m_CurrentSlotX = Max_XSlot - 1;
	}
	if (Max_XSlot == m_CurrentSlotX)
	{
		m_CurrentSlotX = 0;
	}

	if (-1 == m_CurrentSlotY)
	{
		m_CurrentSlotY = UnlockSlotY - 1;
	}
	if (UnlockSlotY == m_CurrentSlotY)
	{
		m_CurrentSlotY = 0;
	}

	CursorThis(m_CurrentSlotX, m_CurrentSlotY);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Inventory::UpdateDispensation(float _Delta, GameEngineState* _Parent)
{
	if (true == IsJustOpen)
	{
		IsJustOpen = false;
		return;
	}

	if (true == UpdateCursor())
	{
		return;
	}

	if (true == UpdateDispensationSelect())
	{
		return;
	}
}


bool UI_Inventory::UpdateDispensationSelect()
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		int SelectNumber = IsSelect();
		if (-1 == SelectNumber)
		{
			DispensationSelectThis();
		}
		else
		{
			DispensationUnSelectThis(SelectNumber);
		}

		return true;
	}

	return false;
}


// -1이면 선택되지 않았습니다.
int UI_Inventory::IsSelect()
{
	for (size_t i = 0; i < SelectItem.size(); i++)
	{
		if ("" != SelectItem[i].ItemName)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

void UI_Inventory::DispensationSelectThis()
{
	int EmptySlotNumber = IsEmptySelectSlot();

	if (-1 != EmptySlotNumber)
	{
		if (nullptr == Data)
		{
			MsgBoxAssert("데이터가 존재하지 않습니다.");
			return;
		}

		InventoryInfo& InventoryData = Data->ReturnInventoryInfo(m_CurrentSlotX, m_CurrentSlotY);

		// 저장된 아이템이 없으면 
		if ("" != InventoryData.SourceName)
		{
			// 인벤토리에서 연금 페이지로 선택됐다고 알립니다.
			if (nullptr == UI_Dispensation::MainDispensation)
			{
				MsgBoxAssert("메인 연금 페이지를 모릅니다.");
				return;
			}

			if (false == UI_Dispensation::MainDispensation->SelectThis(InventoryData.SourceName, InventoryData.ItemCount))
			{
				MsgBoxAssert("연금 페이지에 남는 슬롯이 없는데 추가하려했습니다. 안전장치로 터트립니다. ");
				return;
			}
			

			SelectItem[EmptySlotNumber].ItemName = InventoryData.SourceName;
			SelectItem[EmptySlotNumber].SelectCount = m_CurrentSlotX * m_CurrentSlotY;

			float4 CursorPosition = CalculateIndexToPos(m_CurrentSlotX, m_CurrentSlotY);
			CursorPosition.Z = GlobalUtils::CalculateDepth(EUI_RENDERORDERDEPTH::Cursor);
			SelectItem[EmptySlotNumber].Cursor->Transform.SetLocalPosition(CursorPosition);
			SelectItem[EmptySlotNumber].Cursor->On();
		}
	}
}

// 슬롯이 3개가 넘어가지 않도록 합니다.
// 빈 슬롯이 없으면 -1 을 반환합니다.
int UI_Inventory::IsEmptySelectSlot()
{
	for (size_t i = 0; i < SelectItem.size(); i++)
	{
		if ("" == SelectItem[i].ItemName)
		{
			return static_cast<int>(i);
		}
	}

	return -1;
}

void UI_Inventory::DispensationUnSelectThis(int _SlotNumber)
{
	if (nullptr == UI_Dispensation::MainDispensation)
	{
		MsgBoxAssert("메인 연금 페이지를 모릅니다.");
		return;
	}

	UI_Dispensation::MainDispensation->UnSelectThis(SelectItem[_SlotNumber].ItemName);

	SelectItem[_SlotNumber].ItemName = "";
	SelectItem[_SlotNumber].Cursor->Off();
	SelectItem[_SlotNumber].SelectCount = -1;
}

void UI_Inventory::UnSelectAll()
{
	for (int i = 0; i < SelectItem.size(); i++)
	{
		if ("" != SelectItem[i].ItemName)
		{
			DispensationUnSelectThis(i);
		}
	}
}