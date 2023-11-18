#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "UI_Inventory.h"

#include "Extractor.h"



bool ContentsEvent::Letter_Read::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}

bool ContentsEvent::House_Dust::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}




bool ContentsEvent::Craft_Potion::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}

void ContentsEvent::Craft_Potion::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("Æ÷¼Ç Á¦ÀÛ", EALERTTYPE::QuestAccept));
	}
}

void ContentsEvent::Craft_Potion::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("Æ÷¼Ç Á¦ÀÛ", EALERTTYPE::QuestClear));
	}
}


bool ContentsEvent::Repair_Extractor::QuestClearPrerequisite()
{
	if (false == isQuestAccepted)
	{
		return false;
	}

	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("Item_Etc_10"))
		{
			return true;
		}
	}

	return false;
}

void ContentsEvent::Repair_Extractor::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("ÂøÁó±â ¼ö¸®", EALERTTYPE::QuestAccept));
	}

	Extractor::ActiveInteractiveCollision();
}

void ContentsEvent::Repair_Extractor::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("ÂøÁó±â ¼ö¸®", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Inventory::MainInventory)
	{
		UI_Inventory::MainInventory->PopItem("Item_Etc_10", 1);
	}
}


bool ContentsEvent::Craft_Cracker_Potion::QuestClearPrerequisite()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("FirecrackerPotion"))
		{
			return true;
		}
	}

	return false;
}