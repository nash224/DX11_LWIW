#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "UI_Inventory.h"

#include "Extractor.h"
#include "UI_Hub_MainBoard.h"


void ContentsEvent::StartTraining::AcceptInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("수습 시작", EALERTTYPE::QuestAccept));
	UI_Hub_MainBoard::GetQuestManager()->PopData("FindLetter");
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("StartTraining");
}

bool ContentsEvent::StartTraining::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}

void ContentsEvent::StartTraining::CompleteInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("수습 시작", EALERTTYPE::QuestClear));
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
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestAccept));
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("Craft_Potion");
}

void ContentsEvent::Craft_Potion::CompleteInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("포션 제작", EALERTTYPE::QuestClear));
	UI_Hub_MainBoard::GetQuestManager()->PopData("Craft_Potion");
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
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestAccept));
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("Repair_Extractor");

	Extractor::ActiveInteractiveCollision();
}

void ContentsEvent::Repair_Extractor::CompleteInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("착즙기 수리", EALERTTYPE::QuestClear));
	UI_Hub_MainBoard::GetQuestManager()->PopData("Repair_Extractor");

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
		UI_Hub_MainBoard::GetQuestManager()->PopData("Craft_Cracker_Potion");
		UI_Hub_MainBoard::GetQuestManager()->RegisterData("Show_Cracker_Potion");

		return true;
	}

	return false;
}

void ContentsEvent::Craft_Cracker_Potion::CompleteInternal()
{

}