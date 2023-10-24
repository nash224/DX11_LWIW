#include "PreCompile.h"
#include "UI_DropManager.h"

#include "UI_Drop.h"


UI_DropManager* UI_DropManager::DropManager = nullptr;;
UI_DropManager::UI_DropManager() 
{
}

UI_DropManager::~UI_DropManager() 
{
}


void UI_DropManager::Start()
{
}

void UI_DropManager::Update(float _Delta)
{
}

void UI_DropManager::Release()
{
}

void UI_DropManager::LevelStart(class GameEngineLevel* _NextLevel)
{
	DropManager = this;
}

void UI_DropManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_SystemNoticeList.clear();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UI_DropManager::Init()
{
	DropManager = this;
}

void UI_DropManager::NoticeItemDrop(std::string_view _ItemName)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("현재 레벨을 불러오지 못했습니다.");
		return;
	}

	std::shared_ptr<UI_Drop> SystemNotice = CurLevel->CreateActor<UI_Drop>();
	if (nullptr == SystemNotice)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	SystemNotice->Init(_ItemName);
	SystemNotice->ManagerPtr = this;

	
	// 움직이게 하고
	for (std::shared_ptr<UI_Drop> Ptr : UI_SystemNoticeList)
	{
		Ptr->MoveUnderLine();
	}
	
	// 넣음
	UI_SystemNoticeList.push_back(SystemNotice);
}


std::list<std::shared_ptr<UI_Drop>>& UI_DropManager::GetSystemNoticeList() 
{
	return UI_SystemNoticeList;
}