#include "PreCompile.h"
#include "UI_Inventory.h"

#include "GlobalUtils.h"

#include "UI_DropManager.h"
#include "UI_Dispensation.h"

#include "ItemData.h"

// 데이터 배열은 1차원 배열로 설정합니다.
void Inventory::Init()
{
	size_t Amount = Max_XSlot * Max_YSlot;

	InventoryData.resize(Amount);
}


// 아이템을 데이터에 넣습니다. 
// 인벤토리에 동일한 이름의 아이템이 있으면 아이템의 수를 더하고, 아이템이 없으면 빈 슬롯에 넣습니다.
bool Inventory::PushItem(std::string_view _ItemName, unsigned int _Count)
{
	size_t LockNumber = Max_XSlot * static_cast<size_t>(InventoryParent->UnlockSlotY);

	int Value = ReturnSlotNumber(_ItemName);

	bool isNotContainItem = (-1 == Value);
	if (isNotContainItem)
	{
		// 빈자리가 있으면 빈자리를 찾아서
		for (size_t i = 0; i < LockNumber; i++)
		{
			if (true == InventoryData[i].SourceName.empty())
			{
				InventoryData[i].SourceName = _ItemName;
				InventoryData[i].ItemCount += _Count;
				Value = static_cast<int>(i);
				break;
			}

			bool IsNotEmptySlot = (i == LockNumber - 1);
			if (IsNotEmptySlot)
			{
				// 인벤토리가 다 찼다는 의미로 PopUp UI를 요청합니다.
				// PopUp UI
				return false;
			}
		}
	}
	else
	{
		InventoryData[Value].ItemCount += _Count;
	}

	InventoryParent->DisplayItem(static_cast<size_t>(Value), _ItemName, InventoryData[Value].ItemCount);

	return true;
}

// 아이템을 지정수만큼 뺍니다.
void Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
	InventoryInfo* SlotInfo = Find(_ItemName);
	bool isNotEnoughItem = (SlotInfo->ItemCount < static_cast<int>(_Count));
	if (isNotEnoughItem)
	{
		MsgBoxAssert("사용하려는 아이템의 수보다 적습니다. ");
		return;
	}

	SlotInfo->ItemCount -= _Count;

	bool isZeroCount = (SlotInfo->ItemCount <= 0);
	if (isZeroCount)
	{
		ClearData(ReturnSlotNumber(_ItemName));
	}
	else
	{
		InventoryParent->DisplayItem(static_cast<size_t>(ReturnSlotNumber(_ItemName)), _ItemName, SlotInfo->ItemCount);
	}
}

// 빈슬롯이 있는지 검사합니다.
bool Inventory::CheckEmptySlot(std::string_view _ItemName)
{
	int UnlockSlotCount = UI_Inventory::UnlockSlotY * Max_YSlot;

	if (true == IsContain(_ItemName))
	{
		return true;
	}

	for (size_t i = 0; i < UnlockSlotCount; i++)
	{
		if (0 == InventoryData[i].ItemCount)
		{
			return true;
		}
	}

	return false;
}

// 데이터에 동일한 이름을 가진 아이템이 있는지 검사합니다.
bool Inventory::IsContain(std::string_view _ItemName)
{
	std::string ItemName = _ItemName.data();
	for (size_t y = 0; y < InventoryData.size(); y++)
	{
		if (ItemName == InventoryData[y].SourceName)
		{
			return true;
		}
	}

	return false;
}

// 해당 슬롯에 아이템이 있는지 확인합니다.
bool Inventory::IsContain(unsigned int _X, unsigned int _Y)
{
	int MaxSlot = Max_XSlot;
	unsigned int Value = _Y * MaxSlot + _X;

	bool isContain = (false == InventoryData[Value].SourceName.empty());
	if (isContain)
	{
		return true;
	}

	return false;
}

// 인벤토리에 같은 이름을 가진 아이템의 슬롯넘버를 반환합니다.
// 없으면 -1이 반환됩니다.
int Inventory::ReturnSlotNumber(std::string_view _ItemName)
{
	for (int i = 0; i < InventoryData.size(); i++)
	{
		if (_ItemName == InventoryData[i].SourceName)
		{
			return i;
		}
	}

	return -1;
}

InventoryInfo& Inventory::ReturnInventoryInfo(unsigned int _X, unsigned int _Y)
{
	unsigned int Value = _Y * Max_XSlot + _X;
	return InventoryData[Value];
}


InventoryInfo* Inventory::Find(std::string_view _ItemName)
{
	for (size_t i = 0; i < InventoryData.size(); i++)
	{
		if (_ItemName == InventoryData[i].SourceName)
		{
			return &InventoryData[i];
		}
	}

	return nullptr;
}



void Inventory::ClearData(const unsigned int _X, const unsigned int _Y)
{
	if (false == IsContain(_X, _Y))
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
		if (false == InventoryData[i].SourceName.empty())
		{
			InventoryParent->DisplayItem(i, InventoryData[i].SourceName, InventoryData[i].ItemCount);
		}
	}
}



std::shared_ptr<Inventory> UI_Inventory::Data = nullptr;
UI_Inventory* UI_Inventory::MainInventory = nullptr;
unsigned int UI_Inventory::UnlockSlotY = 0;
UI_Inventory::UI_Inventory()
{
	if (nullptr == GameEngineSound::FindSound("SFX_Getltem_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Getltem");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
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
		OpenUpdate();
	}

	m_InventoryState.Update(_Delta);
}

void UI_Inventory::Release()
{
	Data = nullptr;
	MainInventory = nullptr;

	m_DropManager = nullptr;
	m_InventoryBase = nullptr;
	CursorInfo.Cursor = nullptr;
	CursorInfo.CursorOutline = nullptr;
	CursorInfo.NameTooltip = nullptr;
	CursorInfo.ItemFont = nullptr;

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


	CreateBase();
	CreateSlotArray();
	CreateCursor();
	StateSetting();

	// 아이템 획득 알림창 매니저입니다.
	CreateNoticeDropManager();

	ExternUISetting();

	LockSlot(UnlockSlotY);
	Transform.AddLocalPosition(INVENTORY_POSITION);

	OpenUpdate();
}

void UI_Inventory::CreateBase()
{
	float4 BasePosition = { 0.0f , 0.0f , GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base) };

	m_InventoryBase = CreateComponent<GameEngineUIRenderer>(EUI_RENDERORDERDEPTH::Base);
	m_InventoryBase->SetSprite("Inventory_Base.png");
	m_InventoryBase->Transform.AddLocalPosition(BasePosition);
}

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
			const float4& IndexPos = CalculateIndexToPos(x, y);

			const float FrameDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
			const float IconDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Icon);
			const float FontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

			const float4& ItemCountCorrection = float4(18.0f, -12.0f);

			const float4& FramePos = float4(IndexPos.X, IndexPos.Y, FrameDepth);
			const float4& IconPos = float4(IndexPos.X, IndexPos.Y, IconDepth);
			const float4& ItemCountPos = float4(IndexPos.X + ItemCountCorrection.X, IndexPos.Y + ItemCountCorrection.Y, FontDepth);

			const float fontSize = 8.0f;


			std::shared_ptr<GameEngineUIRenderer> Empty = CreateComponent<GameEngineUIRenderer>();
			Empty->SetSprite("Inventory_Empty_Slot.png");
			Empty->Transform.SetLocalPosition(FramePos);


			InventorySlotArray[y][x].SlotEmpty = Empty;

			std::shared_ptr<GameEngineUIRenderer> Slot = CreateComponent<GameEngineUIRenderer>();
			Slot->Transform.SetLocalPosition(IconPos);
			Slot->Off();
			InventorySlotArray[y][x].Slot = Slot;

			std::shared_ptr<GameEngineUIRenderer> ItemCount = CreateComponent<GameEngineUIRenderer>();
			ItemCount->Transform.SetLocalPosition(ItemCountPos);
			ItemCount->SetText(GlobalValue::Font_Sandoll, "", fontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_RIGHT);
			ItemCount->Off();

			InventorySlotArray[y][x].ItemCount = ItemCount;
		}
	}
}


void UI_Inventory::StateSetting()
{
	CreateStateParameter NormalPara;
	NormalPara.Start = [&](GameEngineState* _Parent) {InventoryMode = EINVENTORYMODE::Normal; };
	NormalPara.Stay = std::bind(&UI_Inventory::UpdateInventory, this, std::placeholders::_1, std::placeholders::_2);
	m_InventoryState.CreateState(EINVENTORYMODE::Normal, NormalPara);

	CreateStateParameter DispensationPara;
	DispensationPara.Start = [&](GameEngineState* _Parent) {IsJustOpen = true, InventoryMode = EINVENTORYMODE::Dispensation; };
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
	CursorInfo.Cursor = CurSor;

	std::shared_ptr<GameEngineUIRenderer> CurSorOutLine = CreateComponent<GameEngineUIRenderer>();
	CurSorOutLine->SetSprite("Inventory_CursorOutline.png");
	CursorInfo.CursorOutline = CurSorOutLine;

	std::shared_ptr<GameEngineUIRenderer> NameTooltip = CreateComponent<GameEngineUIRenderer>();
	NameTooltip->SetSprite("Inventory_NameTooltip.png");
	NameTooltip->GetImageTransform().SetLocalScale(float4(96.0f, 28.0f));
	NameTooltip->Off();
	CursorInfo.NameTooltip = NameTooltip;


	const float FontSize = 14.0f;

	std::shared_ptr<GameEngineUIRenderer> ItemFont = CreateComponent<GameEngineUIRenderer>();
	ItemFont->SetText(GlobalValue::Font_Sandoll, "", FontSize, float4::ZERO, FW1_TEXT_FLAG::FW1_CENTER);
	ItemFont->Off();
	CursorInfo.ItemFont = ItemFont;


	CursorThis(0, 0);
}


void UI_Inventory::CreateNoticeDropManager()
{
	m_DropManager = GetLevel()->CreateActor<UI_DropManager>(EUPDATEORDER::UIMagnaer);
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

void UI_Inventory::LockSlot(const unsigned int _Y)
{
	for (size_t y = _Y; y < InventorySlotArray.size(); y++)
	{
		for (size_t x = 0; x < InventorySlotArray[y].size(); x++)
		{
			std::shared_ptr<GameEngineUIRenderer> Slot = InventorySlotArray[y][x].Slot;
			Slot->SetSprite("Inventory_SlotLock.png");
			Slot->On();
		}
	}
}

void UI_Inventory::PushItem(std::string_view _ItemName, unsigned int _Count/* = 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("존재하지 않는 데이터에 접근하려 했습니다.");
		return;
	}

	if (false == Data->CheckEmptySlot(_ItemName))
	{
		// UI Dont Empty Slot Alert!!
		OutputDebugStringA("빈슬롯이 없습니다.");
		return;
	}


	if (Data->PushItem(_ItemName, _Count))
	{
		if (nullptr != UI_DropManager::DropManager)
		{
			UI_DropManager::DropManager->NoticeItemDrop(_ItemName);
		}
	}
}

void UI_Inventory::PopItem(std::string_view _ItemName, unsigned int _Count)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
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

bool UI_Inventory::IsItem(std::string_view _ItemName, unsigned int _ItemCount /*= 1*/)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return false;
	}

	InventoryInfo* FindItem = Data->Find(_ItemName);
	if (nullptr == FindItem)
	{
		return false;
	}

	if (FindItem->ItemCount >= _ItemCount)
	{
		return true;
	}

	return false;
}

void UI_Inventory::UnlockSlot(const unsigned int _Count /*= 1*/)
{
	unsigned int PrevUnlockSlotY = UnlockSlotY;

	UnlockSlotY += _Count;

	bool IsMaxSlot = (UnlockSlotY > Max_YSlot);
	if (IsMaxSlot)
	{
		UnlockSlotY = Max_YSlot;
	}

	bool isNotChangeSlot = (PrevUnlockSlotY == UnlockSlotY);
	if (isNotChangeSlot)
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
	InventoryInfo* SlotInfo = Data->Find(_ItemName);

	if (nullptr == SlotInfo)
	{
		return 0;
	}

	return SlotInfo->ItemCount;
}


void UI_Inventory::ChangeDataParent()
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않는데 데이터의 부모를 바꾸려고 했습니다.");
		return;
	}

	Data->InventoryParent = this;
}

void UI_Inventory::DisplayItem(const size_t _SlotNumber, std::string_view _FileName, unsigned int _Count)
{
	size_t Number = _SlotNumber;
	size_t SlotX = Number % Max_XSlot;
	size_t SlotY = Number / Max_XSlot;

	const InventorySlotInfo& SlotInfo = InventorySlotArray[SlotY][SlotX];
	std::weak_ptr<GameEngineUIRenderer> Slot = SlotInfo.Slot;
	if (Slot.expired())
	{
		MsgBoxAssert("생성되지 않았거나 존재하지 않는 슬롯입니다.");
		return;
	}

	Slot.lock()->SetSprite(_FileName.data() + std::string(".png"));
	Slot.lock()->On();

	std::weak_ptr<GameEngineUIRenderer> CountFont = SlotInfo.ItemCount;
	if (true == CountFont.expired())
	{
		MsgBoxAssert("생성되지 않았거나 존재하지 않는 슬롯입니다.");
		return;
	}

	CountFont.lock()->ChangeText(std::to_string(_Count));
	CountFont.lock()->On();
}

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
void UI_Inventory::OpenInternal()
{
	GlobalUtils::PlaySFX("SFX_Open_01.wav");
	CursorThis(0, 0);
}

void UI_Inventory::CloseInternal()
{
	if (EINVENTORYMODE::Dispensation == InventoryMode)
	{
		UnSelectAll();
	}

	m_InventoryState.ChangeState(EINVENTORYMODE::Normal);
}

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
	const float4& IndexPosition = CalculateIndexToPos(_X, _Y);


	const float CursorDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
	const float OutLineDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::CursorOutLine);

	const float4& CursorPosition = float4(IndexPosition.X, IndexPosition.Y, CursorDepth);
	const float4& OutlinePosition = float4(IndexPosition.X, IndexPosition.Y, OutLineDepth);


	{
		if (nullptr == CursorInfo.Cursor)
		{
			MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
			return;
		}

		CursorInfo.Cursor->Transform.SetLocalPosition(CursorPosition);
	}


	{
		if (nullptr == CursorInfo.CursorOutline)
		{
			MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
			return;
		}

		CursorInfo.CursorOutline->Transform.SetLocalPosition(OutlinePosition);
	}


	{
		if (nullptr == CursorInfo.NameTooltip)
		{
			MsgBoxAssert("커서를 생성하지 않고 사용하려 했습니다.");
			return;
		}

		if (true == Data->IsContain(_X, _Y))
		{
			const float TooltipDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
			const float ItemFontDepth = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Font);

			const float FontYCorrection = 6.0f;

			const float4& TooltipPosition = float4(IndexPosition.X, IndexPosition.Y + NameTagPosition.Y, TooltipDepth);
			const float4& FontPosition = float4(IndexPosition.X, IndexPosition.Y + NameTagPosition.Y + FontYCorrection, ItemFontDepth);


			CursorInfo.NameTooltip->Transform.SetLocalPosition(TooltipPosition);
			CursorInfo.NameTooltip->On();


			const InventoryInfo& ItemInfo = Data->ReturnInventoryInfo(_X, _Y);
			std::string KRItemName = ReturnItemKRName(ItemInfo.SourceName);

			CursorInfo.ItemFont->Transform.SetLocalPosition(FontPosition);
			CursorInfo.ItemFont->ChangeText(KRItemName);
			CursorInfo.ItemFont->On();
		}
		else
		{
			CursorInfo.NameTooltip->Off();
			CursorInfo.ItemFont->Off();
		}
	}

	m_CurrentSlotX = _X;
	m_CurrentSlotY = _Y;
}

void UI_Inventory::ClearSlot(const unsigned int _X, const unsigned int _Y)
{
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	Data->ClearData(_X, _Y);
}

void UI_Inventory::EraseSlotImg(const int _X, const int _Y)
{
	const InventorySlotInfo& SlotData = InventorySlotArray[_Y][_X];

	if (nullptr == SlotData.Slot || nullptr == SlotData.ItemCount)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	SlotData.Slot->SetSprite("Inventory_None.png");
	SlotData.ItemCount->Off();
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

void UI_Inventory::OpenUpdate()
{
	ChangeDataParent();
	ClearAllSlotImg();
	RenewInventory();
	MainInventory = this;
	m_CurrentSlotX = 0;
	m_CurrentSlotY = 0;
	CursorThis(m_CurrentSlotX, m_CurrentSlotY);
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

// 켜질때 입력을 무시합니다.
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
	GlobalUtils::PlaySFX("SFX_InventoryMove_01.wav");

	m_CurrentSlotX += _X;
	m_CurrentSlotY += _Y;

	bool isOverLeft = (-1 == m_CurrentSlotX);
	bool isOverRight = (Max_XSlot == m_CurrentSlotX);
	bool isOverUp = (-1 == m_CurrentSlotY);
	bool isOverDown = (UnlockSlotY == m_CurrentSlotY);


	if (isOverLeft)
	{
		m_CurrentSlotX = Max_XSlot - 1;
	}

	if (isOverRight)
	{
		m_CurrentSlotX = 0;
	}

	if (isOverUp)
	{
		m_CurrentSlotY = UnlockSlotY - 1;
	}

	if (isOverDown)
	{
		m_CurrentSlotY = 0;
	}

	CursorThis(m_CurrentSlotX, m_CurrentSlotY);
}

std::string UI_Inventory::ReturnItemKRName(std::string_view _ItemName)
{
	std::weak_ptr<ItemData> itemData = ItemData::Find(_ItemName);
	if (itemData.expired())
	{
		MsgBoxAssert("아이템이 데이터에 존재하지 않습니다.");
		return std::string();
	}

	return itemData.lock()->KoreanName;
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
		// 빈칸 클릭하면 리턴
		if (false == Data->IsContain(m_CurrentSlotX, m_CurrentSlotY))
		{
			return false;
		}


		int SelectNumber = ReturnSelectNumber(m_CurrentSlotX, m_CurrentSlotY);
		bool isUnSelect = (-1 == SelectNumber);

		if (isUnSelect)
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


int UI_Inventory::ReturnSelectNumber(int _XSlot, int _YSlot)
{
	InventoryInfo& InventoryData = Data->ReturnInventoryInfo(m_CurrentSlotX, m_CurrentSlotY);
	for (int i = 0; i < SelectItem.size(); i++)
	{
		if (SelectItem[i].ItemName == InventoryData.SourceName)
		{
			return i;
		}
	}

	return -1;
}

void UI_Inventory::DispensationSelectThis()
{
	int EmptySlotNumber = ReturnEmptySelectSlot();

	bool isEmptySlot = (-1 == EmptySlotNumber);
	if (isEmptySlot)
	{
		return;
	}

	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	InventoryInfo& InventoryData = Data->ReturnInventoryInfo(m_CurrentSlotX, m_CurrentSlotY);

	bool isIteminSelectedSlot = (false == InventoryData.SourceName.empty());
	if (isIteminSelectedSlot)
	{
		if (nullptr == UI_Dispensation::MainDispensation)
		{
			MsgBoxAssert("메인 연금 페이지를 모릅니다.");
			return;
		}

		if (false == UI_Dispensation::MainDispensation->SelectThis(InventoryData.SourceName, InventoryData.ItemCount))
		{
			MsgBoxAssert("연금 페이지에 남는 슬롯이 없는데 추가하려했습니다.");
			return;
		}


		SelectItem[EmptySlotNumber].ItemName = InventoryData.SourceName;
		SelectItem[EmptySlotNumber].SelectCount = m_CurrentSlotX * m_CurrentSlotY;

		float4 CursorPosition = CalculateIndexToPos(m_CurrentSlotX, m_CurrentSlotY);
		CursorPosition.Z = GlobalUtils::CalculateFixDepth(EUI_RENDERORDERDEPTH::Cursor);
		SelectItem[EmptySlotNumber].Cursor->Transform.SetLocalPosition(CursorPosition);
		SelectItem[EmptySlotNumber].Cursor->On();
	}
}

int UI_Inventory::ReturnEmptySelectSlot()
{
	for (size_t i = 0; i < SelectItem.size(); i++)
	{
		if (true == SelectItem[i].ItemName.empty())
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
		if (false == SelectItem[i].ItemName.empty())
		{
			DispensationUnSelectThis(i);
		}
	}
}