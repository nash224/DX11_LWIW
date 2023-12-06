#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "UI_Inventory.h"

#include "Extractor.h"
#include "UI_Hub_MainBoard.h"


void ContentsEvent::StartTraining::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("수습 시작", EALERTTYPE::QuestAccept));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->PopData("FindLetter");
		UI_Hub_MainBoard::s_QuestManager->RegisterData("StartTraining");
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


bool ContentsEvent::FindWorkPlace::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}




bool ContentsEvent::Craft_Potion::QuestClearPrerequisite()
{
	if (true == UI_Inventory::IsItem("BadGrassPotion"))
	{
		return true;
	}

	return false;
}

void ContentsEvent::Craft_Potion::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestAccept));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Craft_Potion");
	}
}

void ContentsEvent::Craft_Potion::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->PopData("Craft_Potion");
	}
}


bool ContentsEvent::Repair_Extractor::QuestClearPrerequisite()
{
	if (false == isQuestAccepted)
	{
		return false;
	}

	if (true == UI_Inventory::IsItem("Item_Etc_10"))
	{
		return true;
	}

	return false;
}

void ContentsEvent::Repair_Extractor::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestAccept));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Repair_Extractor");
	}

	Extractor::ActiveInteractiveCollision();
}

void ContentsEvent::Repair_Extractor::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->PopData("Repair_Extractor");
	}

	UI_Inventory::PopItem("Item_Etc_10", 1);
}


bool ContentsEvent::Craft_Cracker_Potion::QuestClearPrerequisite()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = FindQuest("Dian_Cracker");
	if (nullptr == Quest)
	{
		MsgBoxAssert("존재하지 않는 퀘스트를 찾으려 했습니다.");
		return false;
	}

	if (false == Quest->isQuestComplete())
	{
		return false;
	}

	if (true == UI_Inventory::IsItem("FirecrackerPotion"))
	{
		if (nullptr != UI_Hub_MainBoard::s_QuestManager)
		{
			UI_Hub_MainBoard::s_QuestManager->PopData("Craft_Cracker_Potion");
			UI_Hub_MainBoard::s_QuestManager->RegisterData("Show_Cracker_Potion");
		}

		return true;
	}

	return false;
}

void ContentsEvent::Craft_Cracker_Potion::CompleteInternal()
{

}