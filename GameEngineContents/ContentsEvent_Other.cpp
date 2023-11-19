#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "UI_Inventory.h"

#include "Extractor.h"


void ContentsEvent::StartTraining::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("수습 시작", EALERTTYPE::QuestAccept));
	}
}

bool ContentsEvent::StartTraining::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}

void ContentsEvent::StartTraining::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("수습 시작", EALERTTYPE::QuestClear));
	}
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
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestAccept));
	}
}

void ContentsEvent::Craft_Potion::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestClear));
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
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestAccept));
	}

	Extractor::ActiveInteractiveCollision();
}

void ContentsEvent::Repair_Extractor::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestClear));
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