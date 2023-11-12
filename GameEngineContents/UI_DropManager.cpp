#include "PreCompile.h"
#include "UI_DropManager.h"

#include "UI_Drop.h"


UI_DropManager* UI_DropManager::DropManager = nullptr;;
UI_DropManager::UI_DropManager() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_InventoryDrop_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\UI\\Inventory");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

UI_DropManager::~UI_DropManager() 
{
}



void UI_DropManager::Release()
{
	UI_SystemNoticeList.clear();
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
	std::shared_ptr<UI_Drop> SystemNotice = GetLevel()->CreateActor<UI_Drop>();
	SystemNotice->Init(_ItemName);
	SystemNotice->ManagerPtr = this;

	for (std::shared_ptr<UI_Drop> Ptr : UI_SystemNoticeList)
	{
		Ptr->MoveUnderLine();
	}
	
	UI_SystemNoticeList.push_back(SystemNotice);

	GlobalUtils::PlaySFX("SFX_Getltem_01.wav");
}


std::list<std::shared_ptr<UI_Drop>>& UI_DropManager::GetSystemNoticeList() 
{
	return UI_SystemNoticeList;
}