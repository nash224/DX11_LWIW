#include "PreCompile.h"
#include "UI_ProcessManager.h"

#include "UIManager.h"
#include "UI_ProcessList.h"

UI_ProcessManager::UI_ProcessManager()
{
}

UI_ProcessManager::~UI_ProcessManager()
{
}


void UI_ProcessManager::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_ProcessManager::Update(float _Delta)
{
}

void UI_ProcessManager::Release()
{
	ProcessListWindow = nullptr;
	ProcessWindow = nullptr;
}

void UI_ProcessManager::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void UI_ProcessManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void UI_ProcessManager::Init()
{
	RendererSetting();
	OtherProcessSetting();

	Off();
}


void UI_ProcessManager::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Process_Base.png"))
	{
		std::vector<GameEngineFile> Files = GlobalUtils::GetAllFileInPath("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite\\UI_Process");
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}
}

void UI_ProcessManager::OtherProcessSetting()
{
	ProcessWindow = GetLevel()->CreateActor<UI_Process>(EUPDATEORDER::UIComponent);
	ProcessWindow->Init();
}

void UI_ProcessManager::Open()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	UIManager::MainUIManager->UseUIComponent();

	if (nullptr != ProcessListWindow)
	{
		ProcessListWindow->On();
	}

	On();
}

void UI_ProcessManager::Close()
{
	if (nullptr == UIManager::MainUIManager)
	{
		MsgBoxAssert("UI 매니저가 존재하지 않습니다.");
		return;
	}

	UIManager::MainUIManager->DoneUIComponent();


	if (nullptr != ProcessListWindow)
	{
		ProcessListWindow->Off();
	}

	if (nullptr != ProcessWindow)
	{
		ProcessWindow->Off();
	}

	Off();
}


void UI_Process::Init()
{

}