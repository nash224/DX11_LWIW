#include "PreCompile.h"
#include "UI_Hub_MainBoard.h"



void UI_Hub_MainBoard::QuestManager::RegisterData(std::string_view _QuestName)
{
	if (true == IsQuestRegister(_QuestName))
	{
		return;
	}

	QuestContainer.push_back(_QuestName.data());
}

void UI_Hub_MainBoard::QuestManager::PopData(std::string_view _QuestName)
{
	ClearContainer.push_back(_QuestName.data());
	QuestContainer.remove(_QuestName.data());
}

bool UI_Hub_MainBoard::QuestManager::IsQuestRegister(std::string_view _QuestName)
{
	bool ReturnValue = false;

	for (std::string QuestName : ClearContainer)
	{
		if (QuestName == _QuestName)
		{
			ReturnValue = true;
			return false;
		}
	}

	for (std::string QuestName : QuestContainer)
	{
		if (QuestName == _QuestName)
		{
			ReturnValue = true;
			return false;
		}
	}

	return ReturnValue;
}

std::unique_ptr<UI_Hub_MainBoard::QuestManager> UI_Hub_MainBoard::s_QuestManager;
UI_Hub_MainBoard::UI_Hub_MainBoard() 
{
}

UI_Hub_MainBoard::~UI_Hub_MainBoard() 
{
}


void UI_Hub_MainBoard::Start()
{
	GameEngineInput::AddInputObject(this);
}

void UI_Hub_MainBoard::Update(float _Delta)
{
}

void UI_Hub_MainBoard::Release()
{

	s_QuestManager = nullptr;
}

void UI_Hub_MainBoard::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void UI_Hub_MainBoard::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_Hub_MainBoard::Init()
{
	if (nullptr == s_QuestManager)
	{
		InitQuestManager();
	}
}


void UI_Hub_MainBoard::InitQuestManager()
{
	s_QuestManager = std::make_unique<QuestManager>();
}


void UI_Hub_MainBoard::RegisterQuest(std::string_view _QuestName)
{
	if (nullptr == s_QuestManager)
	{
		MsgBoxAssert("매니저가 존재하지 않습니다.");
		return;
	}

	s_QuestManager->RegisterData(_QuestName);
	CreateQuestUnit(_QuestName);
}

void UI_Hub_MainBoard::CreateQuestUnit(std::string_view _QuestName)
{
	std::shared_ptr<QuestData> Data = QuestData::Find(_QuestName);
	if (nullptr == Data)
	{
		MsgBoxAssert("데이터가 존재하지 않습니다.");
		return;
	}

	std::shared_ptr<UI_Hub_MainBoard::QuestUnit> Unit = std::make_shared<UI_Hub_MainBoard::QuestUnit>();
	Unit->Parent = this;
	Unit->Data = Data;
	Unit->Init();

	UnitList.push_back(Unit);
}

void UI_Hub_MainBoard::QuestUnit::Init()
{

}

void UI_Hub_MainBoard::PopQuest(std::string_view _QuestName)
{
	if (nullptr == s_QuestManager)
	{
		MsgBoxAssert("매니저가 존재하지 않습니다.");
		return;
	}

	s_QuestManager->PopData(_QuestName);
}

void UI_Hub_MainBoard::FindQuest(std::string_view _QuestName)
{

}