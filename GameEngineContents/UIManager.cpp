#include "PreCompile.h"
#include "UIManager.h"

#include "UI_Inventory.h"
#include "UI_Dictionary.h"
#include "UI_InterativeMark.h"
#include "UI_Conversation.h"
#include "UI_Hub.h"

#include "Ellie.h"


UIManager::UIManager() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_Open_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Common");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("Photo.png"))
	{
		std::vector<GameEngineDirectory> Dirs = FileLoadFunction::GetAllDirInPath("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite");
		for (GameEngineDirectory& Dir : Dirs)
		{
			std::vector <GameEngineFile> Files = Dir.GetAllFile();
			for (GameEngineFile& pFile : Files)
			{
				GameEngineSprite::CreateSingle(pFile.GetFileName());
			}
		}
	}
}

UIManager::~UIManager() 
{
}


void UIManager::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UIManager::Update(float _Delta)
{
	DectectOpenUIComponent();
	InputUpdate();
}


void UIManager::Init()
{
	HubPtr = GetLevel()->CreateActor<UI_Hub>(EUPDATEORDER::UIComponent);
	HubPtr->Init();

	DictionaryPtr = GetLevel()->CreateActor<UI_Dictionary>(EUPDATEORDER::UIComponent);
	DictionaryPtr->Init();

	InventoryPtr = GetLevel()->CreateActor<UI_Inventory>(EUPDATEORDER::UIComponent);
	InventoryPtr->Init();

	InteractiveMarkPtr = GetLevel()->CreateActor<UI_InterativeMark>(EUPDATEORDER::UIComponent);
	InteractiveMarkPtr->Init();

	UIConversationPtr = GetLevel()->CreateActor<UI_Conversation>(EUPDATEORDER::UIComponent);
	UIConversationPtr->Init();

	Reset();
}



void UIManager::OpenInventory(EINVENTORYMODE _Mode)
{
	if (nullptr == InventoryPtr)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return;
	}

	InventoryPtr->Open();
	InventoryPtr->UsingOtherComponent(_Mode);
	UseUIComponent();
}

void UIManager::CloseInventory()
{
	if (nullptr == InventoryPtr)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return;
	}

	InventoryPtr->Close();
	DoneUIComponent();
}


void UIManager::UseUIComponent()
{
	HubPtr->Close();
	SetEllieControl(false);
}

void UIManager::DoneUIComponent()
{
	HubPtr->Open();
 	SetEllieControl(true);
}

std::shared_ptr<class UI_Conversation> UIManager::GetConversationPtr() const
{
	if (nullptr == UIConversationPtr)
	{
		MsgBoxAssert("대화 UI가 존재하지 않습니다.");
		return nullptr;
	}

	return UIConversationPtr;
}

std::shared_ptr<class UI_Inventory> UIManager::GetInventoryPtr() const
{
	if (nullptr == InventoryPtr)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return nullptr;
	}

	return InventoryPtr;
}

std::shared_ptr<class UI_InterativeMark> UIManager::GetMarkPtr() const
{
	if (nullptr == InteractiveMarkPtr)
	{
		MsgBoxAssert("표식이 존재하지 않습니다.");
		return nullptr;
	}

	return InteractiveMarkPtr;
}


void UIManager::Reset()
{
	if (nullptr != HubPtr)
	{
		HubPtr->Open();
	}

	if (nullptr != DictionaryPtr)
	{
		DictionaryPtr->Close();
	}

	if (nullptr != InventoryPtr)
	{
		InventoryPtr->Close();
	}

	IsActiveComponent = false;

	SetEllieControl(true);
}



// UI컴포넌트가 꺼지는 것을 감지하고, 감지되면 HUB가 켜집니다.
void UIManager::DectectOpenUIComponent()
{
	if (true == IsActiveComponent)
	{
		if (nullptr == DictionaryPtr || nullptr == InventoryPtr)
		{
			MsgBoxAssert("존재하지 않는 액터를 참조하려 했습니다.");
			return;
		}

		if (false == DictionaryPtr->IsOpen && false == InventoryPtr->IsOpen)
		{
			SwitchOpenHub = true;									// 허브를 열 수 있습니다.
			IsActiveComponent = false;							// 현재 컴포넌트가 작동중인지 추적하는 변수입니다.
			HubPreServeCheck = false;								// 허브를 닫지 않고 컴포넌트를 열지 결정합니다.
		}
	}

	if (true == SwitchOpenHub)
	{
		if (nullptr == HubPtr)
		{
			MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
			return;
		}

		HubPtr->Open();
		SetEllieControl(true);

		SwitchOpenHub = false;
	}
}

// 특정 UI를 킵니다.
void UIManager::InputUpdate()
{
	if (false == IsActiveComponent)
	{
		if (true == GameEngineInput::IsDown('D', this))
		{
			if (nullptr == DictionaryPtr)
			{
				MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
				return;
			}

			DictionaryPtr->Open();
			SetEllieControl(false);
			IsActiveComponent = true;
		}

		if (true == GameEngineInput::IsDown('S', this))
		{
			OpenInventory(EINVENTORYMODE::Normal);
			SetEllieControl(false);
			HubPreServeCheck = true;
			IsActiveComponent = true;
		}

		if (false == HubPreServeCheck && true == IsActiveComponent)
		{
			if (nullptr == HubPtr)
			{
				MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
				return;
			}

			HubPtr->Close();
		}
	}
}


void UIManager::SetEllieControl(bool _Value)
{
	const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr();

	if (nullptr != PlayerPtr)
	{
		_Value ? PlayerPtr->OnControl() : PlayerPtr->OffControl();
	}
}
