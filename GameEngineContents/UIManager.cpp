#include "PreCompile.h"
#include "UIManager.h"



#include "UI_Inventory.h"
#include "UI_Dictionary.h"
#include "UI_InterativeMark.h"
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
	CheckForOpenUIComponent();
	UpdateUIComponentOpenInput();
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
		for (size_t i = 0; i < Dirs.size(); i++)
		{
			GameEngineDirectory Dir = Dirs[i];
			std::vector <GameEngineFile> Files = Dir.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile pFile = Files[i];
				GameEngineSprite::CreateSingle(pFile.GetFileName());
			}
		}
	}


	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_Hub = CurLevel->CreateActor<UI_Hub>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Hub)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Hub->Init();

	m_Dictionary = CurLevel->CreateActor<UI_Dictionary>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Dictionary)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Dictionary->Init();


	m_Inventory = CurLevel->CreateActor<UI_Inventory>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_Inventory->Init();


	m_InteractiveMark = CurLevel->CreateActor<UI_InterativeMark>(EUPDATEORDER::UIComponent);
	if (nullptr == m_InteractiveMark)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	m_InteractiveMark->Init();


	Reset();
}



void UIManager::OpenInventory()
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return;
	}

	m_Inventory->Open();
}

void UIManager::CloseInventory()
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("�κ��丮�� �������� �ʽ��ϴ�.");
		return;
	}

	m_Inventory->Close();
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

	m_IsActiveComponent = false;

	SetEllieControl(true);
}


/////////////////////////////////////////////////////////////////////////////////////

// UI������Ʈ�� ������ ���� �����ϰ�, �����Ǹ� HUB�� �����ϴ�.
void UIManager::CheckForOpenUIComponent()
{
	if (true == m_IsActiveComponent)
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
			m_SwitchOpenHub = true;									// ��긦 �� �� �ֽ��ϴ�.
			m_IsActiveComponent = false;							// ���� ������Ʈ�� �۵������� �����ϴ� �����Դϴ�.
			m_IsHubPreServe = false;								// ��긦 ���� �ʰ� ������Ʈ�� ���� �����մϴ�.
		}
	}

	if (true == m_SwitchOpenHub)
	{
		if (nullptr == m_Hub)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
			return;
		}

		m_Hub->Open();
		SetEllieControl(true);

		m_SwitchOpenHub = false;
	}
}

// Ư�� ������Ʈ�� ŵ�ϴ�.
void UIManager::UpdateUIComponentOpenInput()
{
	if (false == m_IsActiveComponent)
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
			m_IsActiveComponent = true;
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
			m_IsHubPreServe = true;
			m_IsActiveComponent = true;
		}

		if (false == m_IsHubPreServe && true == m_IsActiveComponent)
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
