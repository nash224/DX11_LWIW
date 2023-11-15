#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"

#include "AlertManager.h"
#include "UI_Inventory.h"



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
}

bool ContentsEvent::Aurea_Cure::QuestClearPrerequisite()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("UncurseCandy"))
		{
			return true;
		}
	}

	return false;
}

void ContentsEvent::Aurea_Cure::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("历林秦力 荤帕 力累", EALERTTYPE::QuestClear));
	}
}