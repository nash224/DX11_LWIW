#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "UI_Inventory.h"

#include "Extractor.h"



bool ContentsEvent::Letter_Read::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}

bool ContentsEvent::House_Dust::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}




bool ContentsEvent::Craft_Potion::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}

void ContentsEvent::Craft_Potion::QuestAccept()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("Æ÷¼Ç Á¦ÀÛ", EALERTTYPE::QuestAccept));
	}

	isQuestAccepted = true;
}

void ContentsEvent::Craft_Potion::QuestComplete()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("Æ÷¼Ç Á¦ÀÛ", EALERTTYPE::QuestClear));
	}

	isQuestCompleted = true;
}


bool ContentsEvent::Repair_Extractor::CheckPrerequisiteQuest()
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

void ContentsEvent::Repair_Extractor::QuestAccept()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("ÂøÁó±â ¼ö¸®", EALERTTYPE::QuestAccept));
	}

	Extractor::ActiveInteractiveCollision();

	isQuestAccepted = true;
}

void ContentsEvent::Repair_Extractor::QuestComplete()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("ÂøÁó±â ¼ö¸®", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Inventory::MainInventory)
	{
		UI_Inventory::MainInventory->PopItem("Item_Etc_10", 1);
	}

	isQuestCompleted = true;
}