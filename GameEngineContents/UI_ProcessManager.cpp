#include "PreCompile.h"
#include "UI_ProcessManager.h"

#include "IngredientData.h"

#include "UIManager.h"
#include "UI_Inventory.h"
#include "UI_ProcessList.h"
#include "UI_ProcessB.h"

#include "Ellie.h"



UI_ProcessManager* UI_ProcessManager::ProcessManager = nullptr;
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

void UI_ProcessManager::Release()
{
	ProcessListWindow = nullptr;
	ProcessWindow = nullptr;
}

void UI_ProcessManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void UI_ProcessManager::Init()
{
	ProcessManager = this;

	RendererSetting();
	OtherProcessSetting();

	Off();
}

// 렌더러 세팅
void UI_ProcessManager::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Process_Base.png"))
	{
		std::vector<GameEngineFile> Files = FileLoadFunction::GetAllFileInPath("Resources\\PlayContents\\PlayResourecs\\UI\\UI_Sprite\\UI_Process");
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


/////////////////////////////////////////////////////////////////////////////////////

// 열기
void UI_ProcessManager::Open()
{
	PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr()->UseUIComponent();

	if (nullptr != ProcessListWindow)
	{
		ProcessListWindow->Open();
	}

	On();
}

// 닫기
void UI_ProcessManager::Close()
{
	PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr()->DoneUIComponent();
	PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->FinishWork();

	if (nullptr != ProcessListWindow)
	{
		ProcessListWindow->Close();
	}

	if (nullptr != ProcessWindow)
	{
		ProcessWindow->Close();
	}

	Off();

	SFXFunction::PlaySFX("SFX_JucierClose_01.wav");
}


void UI_ProcessManager::OpenProcessWindow(std::string_view ProductName, int _ScrCount)
{
	if (nullptr ==ProcessListWindow)
	{
		MsgBoxAssert("가공 리스트 탭이 존재하지")
	}
	ProcessListWindow->Close();
	ProcessWindow->Open(ProductName, _ScrCount);

	SFXFunction::PlaySFX(GetOpenSoundFileName());
}

void UI_ProcessManager::OpenListWindow()
{
	ProcessWindow->Close();
	ProcessListWindow->Open();

	SFXFunction::PlaySFX(GetOpenSoundFileName());
}

std::string UI_ProcessManager::GetOpenSoundFileName()
{
	static int SoundChance = 0;
	++SoundChance;
	if (SoundChance % 2 == 0)
	{
		return "SFX_JucierOpen_01.wav";
	}

	return "SFX_JucierOpen_02.wav";
}

void UI_ProcessManager::JuicyDone()
{
	CreateJuicyItem();

	std::weak_ptr<IngredientData> Data = IngredientData::Find(CreatedProductName);
	if (true == Data.expired())
	{
		MsgBoxAssert("등록되지 않은 데이터입니다.");
		return;
	}
	
	const int ItemCount = UI_Inventory::ReturnItemCount(Data.lock()->SourceName);

	ProcessWindow->Open(CreatedProductName, ItemCount);
}

// 가공하고 나서 List 아이템 반영해야됨

// JuicyDone에서 널체크를 해줍니다.
void UI_ProcessManager::CreateJuicyItem()
{
	UI_Inventory::PushItem(CreatedProductName);
}