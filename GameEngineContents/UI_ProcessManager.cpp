#include "PreCompile.h"
#include "UI_ProcessManager.h"

#include "UIManager.h"
#include "UI_ProcessList.h"
#include "UI_ProcessB.h"

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

// 렌더러 세팅
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

// 가공창 1,2 세팅
void UI_ProcessManager::OtherProcessSetting()
{
	ProcessListWindow = GetLevel()->CreateActor<UI_ProcessList>(EUPDATEORDER::UIComponent);
	ProcessListWindow->Init();
	ProcessListWindow->ProcessManagerPtr = this;

	ProcessWindow = GetLevel()->CreateActor<UI_ProcessB>(EUPDATEORDER::UIComponent);
	ProcessWindow->Init();
	ProcessWindow->ProcessManager = this;
}

// 열기
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
		ProcessListWindow->Open();
	}

	On();
}

// 닫기
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
		ProcessListWindow->Close();
	}

	if (nullptr != ProcessWindow)
	{
		ProcessWindow->Close();
	}

	Off();
}


void UI_ProcessManager::OpenProcessWindow(std::string_view ProductName, int _ScrCount)
{
	ProcessListWindow->Close();
	ProcessWindow->Open(ProductName, _ScrCount);
}

void UI_ProcessManager::OpenListWindow()
{
	ProcessWindow->Close();
	ProcessListWindow->Open();
}