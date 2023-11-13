#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "AlertManager.h"



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
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ����", EALERTTYPE::QuestAccept));
	}

	isQuestAccepted = true;
}

void ContentsEvent::Craft_Potion::QuestComplete()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ����", EALERTTYPE::QuestClear));
	}

	isQuestCompleted = true;
}