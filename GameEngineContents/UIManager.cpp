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
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("��ȭ UI�� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	return UIConversationPtr;
}

std::shared_ptr<class UI_Inventory> UIManager::GetInventoryPtr() const
{
	if (nullptr == InventoryPtr)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	return InventoryPtr;
}

std::shared_ptr<class UI_InterativeMark> UIManager::GetMarkPtr() const
{
	if (nullptr == InteractiveMarkPtr)
	{
		MsgBoxAssert("ǥ���� �������� �ʽ��ϴ�.");
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



// UI������Ʈ�� ������ ���� �����ϰ�, �����Ǹ� HUB�� �����ϴ�.
void UIManager::DectectOpenUIComponent()
{
	if (true == IsActiveComponent)
	{
		if (nullptr == DictionaryPtr || nullptr == InventoryPtr)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� �����Ϸ� �߽��ϴ�.");
			return;
		}

		if (false == DictionaryPtr->IsOpen && false == InventoryPtr->IsOpen)
		{
			SwitchOpenHub = true;									// ��긦 �� �� �ֽ��ϴ�.
			IsActiveComponent = false;							// ���� ������Ʈ�� �۵������� �����ϴ� �����Դϴ�.
			HubPreServeCheck = false;								// ��긦 ���� �ʰ� ������Ʈ�� ���� �����մϴ�.
		}
	}

	if (true == SwitchOpenHub)
	{
		if (nullptr == HubPtr)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
			return;
		}

		HubPtr->Open();
		SetEllieControl(true);

		SwitchOpenHub = false;
	}
}

// Ư�� UI�� ŵ�ϴ�.
void UIManager::InputUpdate()
{
	if (false == IsActiveComponent)
	{
		if (true == GameEngineInput::IsDown('D', this))
		{
			if (nullptr == DictionaryPtr)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
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
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
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
