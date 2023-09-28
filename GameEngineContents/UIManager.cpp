#include "PreCompile.h"
#include "UIManager.h"



#include "UI_Inventory.h"
#include "UI_Dictionary.h"
#include "UI_Hub.h"


GameEngineActor* UIManager::g_MainUIManager = nullptr;
UIManager::UIManager() 
{
}

UIManager::~UIManager() 
{
}


void UIManager::Start()
{

}

void UIManager::Update(float _Delta)
{
	CheckForOpenUIComponent();
	UpdateUIComponentOpenInput();
}

void UIManager::LevelStart(class GameEngineLevel* _NextLevel)
{
	g_MainUIManager = this;
}

void UIManager::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void UIManager::Init()
{
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



	Reset();
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

	m_IsActiveComponent = false;
}


/////////////////////////////////////////////////////////////////////////////////////

// UI������Ʈ�� ������ ���� �����ϰ�, HUB�� �����ϴ�.
void UIManager::CheckForOpenUIComponent()
{
	if (nullptr == m_Dictionary)
	{
		MsgBoxAssert("������ �������� �ʰ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	if (false == m_Dictionary->IsOpen)
	{
		if (nullptr == m_Hub)
		{
			MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.")
		}

		m_Hub->Open();

		m_IsActiveComponent = false;
	}
}

void UIManager::UpdateUIComponentOpenInput()
{
	if (false == m_IsActiveComponent)
	{
		if (true == GameEngineInput::IsDown('D'))
		{
			if (nullptr == m_Dictionary)
			{
				MsgBoxAssert("�������� �ʴ� ���͸� ����Ϸ� �߽��ϴ�.");
				return;
			}

			m_Dictionary->Open();
			m_IsActiveComponent = true;
		}

		if (true == m_IsActiveComponent)
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
