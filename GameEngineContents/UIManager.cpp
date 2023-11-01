#include "PreCompile.h"
#include "UIManager.h"



#include "UI_Inventory.h"
#include "UI_Dictionary.h"
#include "UI_InterativeMark.h"
#include "UI_Conversation.h"
#include "UI_Hub.h"

#include "Ellie.h"


UIManager* UIManager::MainUIManager = nullptr;
UIManager::UIManager() 
{
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
	UpdateInputToOpenUIComponent();
}

void UIManager::LevelStart(class GameEngineLevel* _NextLevel)
{
	MainUIManager = this;
}

void UIManager::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void UIManager::Init()
{
	MainUIManager = this;

	if (nullptr == GameEngineSprite::Find("Photo.png"))
	{
		std::vector<GameEngineDirectory> Dirs = GlobalUtils::GetAllDirInPath("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite");
		for (GameEngineDirectory& Dir : Dirs)
		{
			std::vector <GameEngineFile> Files = Dir.GetAllFile();
			for (GameEngineFile& pFile : Files)
			{
				GameEngineSprite::CreateSingle(pFile.GetFileName());
			}
		}
	}

	if (nullptr == GameEngineSound::FindSound("SFX_InventoryDrop_01.wav"))
	{
		std::vector<GameEngineDirectory> Dirs = GlobalUtils::GetAllDirInPath("Resources\\Sound\\UI");
		for (GameEngineDirectory& Dir : Dirs)
		{
			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (GameEngineFile& pFile : Files)
			{
				GameEngineSound::SoundLoad(pFile.GetStringPath());
			}
		}
	}

	

	m_Hub = GetLevel()->CreateActor<UI_Hub>(EUPDATEORDER::UIComponent);
	m_Hub->Init();

	m_Dictionary = GetLevel()->CreateActor<UI_Dictionary>(EUPDATEORDER::UIComponent);
	m_Dictionary->Init();

	m_Inventory = GetLevel()->CreateActor<UI_Inventory>(EUPDATEORDER::UIComponent);
	m_Inventory->Init();

	m_InteractiveMark = GetLevel()->CreateActor<UI_InterativeMark>(EUPDATEORDER::UIComponent);
	m_InteractiveMark->Init();

	m_ConversationUI = GetLevel()->CreateActor<UI_Conversation>(EUPDATEORDER::UIComponent);
	m_ConversationUI->Init();


	Reset();
}


/////////////////////////////////////////////////////////////////////////////////////

void UIManager::OpenInventory(EINVENTORYMODE _Mode)
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return;
	}

	m_Inventory->Open();
	m_Inventory->UsingOtherComponent(_Mode);
	UseUIComponent();
}

void UIManager::CloseInventory()
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return;
	}

	m_Inventory->Close();
	DoneUIComponent();
}


void UIManager::UseUIComponent()
{
	m_Hub->Close();
	IsOtherComponentUsed = true;
	SetEllieControl(false);
}

void UIManager::DoneUIComponent()
{
	m_Hub->Open();
	IsOtherComponentUsed = false;

	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("���������ʴ� �ٸ��� �̿��Ϸ� �߽��ϴ�.");
		return;
	}

	Ellie::MainEllie->FinishWork();

	SetEllieControl(true);
}


void UIManager::Reset()
{
	if (nullptr != m_Hub)
	{
		m_Hub->Open();
	}

	if (nullptr != m_Dictionary)
	{
		m_Dictionary->Close();
	}

	if (nullptr != m_Inventory)
	{
		m_Inventory->Close();
	}

	IsActiveComponent = false;

	SetEllieControl(true);
}


/////////////////////////////////////////////////////////////////////////////////////

// UI������Ʈ�� ������ ���� �����ϰ�, �����Ǹ� HUB�� �����ϴ�.
void UIManager::DectectOpenUIComponent()
{
	if (true == IsActiveComponent)
	{
		if (nullptr == m_Dictionary)
		{
			MsgBoxAssert("������ �������� �ʰ� ����Ϸ� �߽��ϴ�.");
			return;
		}

		if (nullptr == m_Inventory)
		{
			MsgBoxAssert("�κ��丮�� �������� �ʰ� ����Ϸ� �߽��ϴ�.");
			return;
		}

		if (false == m_Dictionary->IsOpen && false == m_Inventory->IsOpen)
		{
			SwitchOpenHub = true;									// ��긦 �� �� �ֽ��ϴ�.
			IsActiveComponent = false;							// ���� ������Ʈ�� �۵������� �����ϴ� �����Դϴ�.
			HubPreServeCheck = false;								// ��긦 ���� �ʰ� ������Ʈ�� ���� �����մϴ�.
		}
	}

	if (true == SwitchOpenHub)
	{
		if (nullptr == m_Hub)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
			return;
		}

		m_Hub->Open();
		SetEllieControl(true);

		SwitchOpenHub = false;
	}
}

// Ư�� ������Ʈ�� ŵ�ϴ�.
void UIManager::UpdateInputToOpenUIComponent()
{
	if (false == IsActiveComponent && false == IsOtherComponentUsed)
	{
		if (true == GameEngineInput::IsDown('D', this))
		{
			if (nullptr == m_Dictionary)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
				return;
			}

			m_Dictionary->Open();
			SetEllieControl(false);
			IsActiveComponent = true;
		}

		if (true == GameEngineInput::IsDown('S', this))
		{
			if (nullptr == m_Inventory)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
				return;
			}

			m_Inventory->Open();
			SetEllieControl(false);
			HubPreServeCheck = true;
			IsActiveComponent = true;
		}

		if (false == HubPreServeCheck && true == IsActiveComponent)
		{
			if (nullptr == m_Hub)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
				return;
			}

			m_Hub->Close();
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UIManager::SetEllieControl(bool _Value)
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("�ٸ��� ����ִ��� �𸨴ϴ�. Ȥ�� �˰� ��Ű���?");
		return;
	}

	_Value ? Ellie::MainEllie->OnControl() : Ellie::MainEllie->OffControl();
}
