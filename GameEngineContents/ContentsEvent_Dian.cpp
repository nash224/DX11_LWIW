#include "PreCompile.h"
#include "ContentsEvent.h"


#include "PlayLevel.h"
#include "TimeManager.h"

#include "UI_Alert_Quest.h"
#include "PlayLevel.h"
#include "AlertManager.h"
#include "FadeObject.h"


bool ContentsEvent::Crow_Meet::CheckPrerequisiteQuest()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> AureaQuest = ContentsEvent::FindQuest("Aurea_Cure");
		if (true == AureaQuest.expired())
		{
			MsgBoxAssert("»ý¼ºÇÏÁö ¾ÊÀº Äù½ºÆ®ÀÔ´Ï´Ù.");
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

bool ContentsEvent::Dian_Cracker::CheckPrerequisiteQuest()
{
	return false;
}

void ContentsEvent::Dian_Cracker::QuestComplete()
{
	isQuestCompleted = true;
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("ºÒ²É³îÀÌ Æ÷¼Ç Ä«Å»·Î±×", EALERTTYPE::QuestClear));
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("ºÒ²É³îÀÌ Æ÷¼Ç Á¦Á¶", EALERTTYPE::QuestAccept));
}



void ContentsEvent::Dian_BadWeedPotion::QuestAccept()
{
	isQuestAccepted = true;
}

bool ContentsEvent::Dian_BadWeedPotion::CheckPrerequisiteQuest()
{
	return !isQuestCompleted;
}

void ContentsEvent::Dian_BadWeedPotion::QuestComplete()
{
	isQuestCompleted = true;
}