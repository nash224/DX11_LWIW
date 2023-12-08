#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "TimeManager.h"
#include "AlertManager.h"

#include "UI_Inventory.h"
#include "UI_Alert_Quest.h"
#include "UI_Hub_MainBoard.h"


bool ContentsEvent::Crow_Meet::QuestClearPrerequisite()
{
	if (nullptr != PlayLevel::GetTimeManager())
	{
		const std::shared_ptr<ContentsEvent::QuestUnitBase>& AureaQuest = ContentsEvent::FindQuest("Repair_Extractor");
		if (nullptr == AureaQuest)
		{
			MsgBoxAssert("생성하지 않은 퀘스트입니다.");
			return false;
		}

		bool isQuestComplete = AureaQuest->isQuestComplete();

		if (PlayLevel::GetTimeManager()->GetHour() >= 11 && true == isQuestComplete)
		{
			return true;
		}
	}
	
	return false;
}

void ContentsEvent::Crow_Meet::CompleteInternal()
{
	if (nullptr != PlayLevel::GetTimeManager())
	{
		EventDay = PlayLevel::GetTimeManager()->GetDayCount();
	}
}

bool ContentsEvent::Dian_Catalogue::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}

void ContentsEvent::Dian_BadWeedPotion::AcceptInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestAccept));
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("Dian_BadWeedPotion");
}

bool ContentsEvent::Dian_BadWeedPotion::QuestClearPrerequisite()
{
	if (true == UI_Inventory::IsItem("BadGrassPotion"))
	{
		return true;
	}

	return false;
}

void ContentsEvent::Dian_BadWeedPotion::CompleteInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestClear));
	UI_Hub_MainBoard::GetQuestManager()->PopData("Dian_BadWeedPotion");

	UI_Inventory::PushItem("Item_Etc_12");
	UI_Inventory::UnlockSlot();

	ContentsEvent::ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = true;
}


void ContentsEvent::Dian_Cracker::AcceptInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("폭죽 포션 레시피", EALERTTYPE::QuestAccept));
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("Dian_Cracker_Recipe");
}

bool ContentsEvent::Dian_Cracker::QuestClearPrerequisite()
{
	if (true == UI_Inventory::IsItem("NutritionPotion"))
	{
		return true;
	}

	return false;
}

void ContentsEvent::Dian_Cracker::CompleteInternal()
{
	PlayLevel::GetAlertManager()->RegisterAlert(AlertData("폭죽 포션 레시피", EALERTTYPE::QuestClear));
	UI_Hub_MainBoard::GetQuestManager()->PopData("Dian_Cracker_Recipe");
	UI_Hub_MainBoard::GetQuestManager()->RegisterData("Craft_Cracker_Potion");
}
