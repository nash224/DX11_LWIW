#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"

#include "AlertManager.h"
#include "UI_Inventory.h"
#include "UI_Hub_MainBoard.h"


bool ContentsEvent::Aurea_Find::QuestClearPrerequisite()
{
	return true;
}



void ContentsEvent::Aurea_Cure::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("历林秦力 荤帕 力累", EALERTTYPE::QuestAccept));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Aurea_Cure");
	}
}

bool ContentsEvent::Aurea_Cure::QuestClearPrerequisite()
{
	if (true == UI_Inventory::IsItem("UncurseCandy"))
	{
		return true;
	}

	return false;
}

void ContentsEvent::Aurea_Cure::CompleteInternal()
{
	if (false == UI_Inventory::IsItem("Item_Etc_10"))
	{
		UI_Inventory::UnlockSlot();
		UI_Inventory::PushItem("Item_Etc_10", 1);
	}

	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("历林秦力 荤帕 力累", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->PopData("Aurea_Cure");
	}
}