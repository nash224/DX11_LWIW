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
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_Hub = CurLevel->CreateActor<UI_Hub>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Hub)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Hub->Init();

	m_Dictionary = CurLevel->CreateActor<UI_Dictionary>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Dictionary)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Dictionary->Init();


	m_Inventory = CurLevel->CreateActor<UI_Inventory>(EUPDATEORDER::UIComponent);
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Inventory->Init();


	m_InteractiveMark = CurLevel->CreateActor<UI_InterativeMark>(EUPDATEORDER::UIComponent);
	if (nullptr == m_InteractiveMark)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_InteractiveMark->Init();


	Reset();
}



void UIManager::OpenInventory()
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
		return;
	}

	m_Inventory->Open();
}

void UIManager::CloseInventory()
{
	if (nullptr == m_Inventory)
	{
		MsgBoxAssert("인벤토리가 존재하지 않습니다.");
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

// UI컴포넌트가 꺼지는 것을 감지하고, 감지되면 HUB가 켜집니다.
void UIManager::CheckForOpenUIComponent()
{
	if (true == m_IsActiveComponent)
	{
		if (nullptr == m_Dictionary)
		{
			MsgBoxAssert("사전을 생성하지 않고 사용하려 했습니다.");
			return;
		}

		if (nullptr == m_Inventory)
		{
			MsgBoxAssert("인벤토리을 생성하지 않고 사용하려 했습니다.");
			return;
		}

		if (false == m_Dictionary->IsOpen && false == m_Inventory->IsOpen)
		{
			m_SwitchOpenHub = true;									// 허브를 열 수 있습니다.
			m_IsActiveComponent = false;							// 현재 컴포넌트가 작동중인지 추적하는 변수입니다.
			m_IsHubPreServe = false;								// 허브를 닫지 않고 컴포넌트를 열지 결정합니다.
		}
	}

	if (true == m_SwitchOpenHub)
	{
		if (nullptr == m_Hub)
		{
			MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
			return;
		}

		m_Hub->Open();
		SetEllieControl(true);

		m_SwitchOpenHub = false;
	}
}

// 특정 컴포넌트를 킵니다.
void UIManager::UpdateUIComponentOpenInput()
{
	if (false == m_IsActiveComponent)
	{
		if (true == GameEngineInput::IsDown('D', this))
		{
			if (nullptr == m_Dictionary)
			{
				MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
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
				MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
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
				MsgBoxAssert("존재하지 않는 액터를 사용하려 했습니다.");
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
		MsgBoxAssert("앨리가 어디있는지 모릅니다. 혹시 알고 계신가요?");
		return;
	}

	_Value ? Ellie::MainEllie->OnControl() : Ellie::MainEllie->OffControl();
}
