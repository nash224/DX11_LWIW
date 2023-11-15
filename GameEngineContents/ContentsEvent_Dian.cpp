#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "TimeManager.h"
#include "AlertManager.h"

#include "UI_Inventory.h"
#include "UI_Alert_Quest.h"


bool ContentsEvent::Crow_Meet::CheckPrerequisiteQuest()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> AureaQuest = ContentsEvent::FindQuest("Aurea_Cure");
		if (true == AureaQuest.expired())
		{
			MsgBoxAssert("생성하지 않은 퀘스트입니다.");
			return false;
		}

		bool isQuestComplete = AureaQuest.lock()->isQuestComplete();

		if (PlayLevel::s_TimeManager->GetHour() >= 11 && true == isQuestComplete)
		{
			return true;
		}
	}
	
	return false;
}


bool ContentsEvent::Dian_Catalogue::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}


void ContentsEvent::Dian_BadWeedPotion::QuestAccept()
{
	if (true == isQuestAccepted)
	{
		return;
	}

	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestAccept));
	}

	isQuestAccepted = true;
}

bool ContentsEvent::Dian_BadWeedPotion::CheckPrerequisiteQuest()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("BadGrassPotion"))
		{
			return true;
		}
	}

	return false;
}

void ContentsEvent::Dian_BadWeedPotion::QuestComplete()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestClear));
	}

	isQuestCompleted = true;
}


bool ContentsEvent::Dian_Cracker::CheckPrerequisiteQuest()
{
	return false;
}

void ContentsEvent::Dian_Cracker::QuestComplete()
{
	isQuestCompleted = true;
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("불꽃놀이 포션 카탈로그", EALERTTYPE::QuestClear));
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("불꽃놀이 포션 제조", EALERTTYPE::QuestAccept));
}
