#include "PreCompile.h"
#include "ContentsEvent.h"

#include "PlayLevel.h"
#include "TimeManager.h"
#include "AlertManager.h"

#include "UI_Inventory.h"
#include "UI_Alert_Quest.h"


bool ContentsEvent::Crow_Meet::QuestClearPrerequisite()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> AureaQuest = ContentsEvent::FindQuest("Aurea_Cure");
		if (true == AureaQuest.expired())
		{
			MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
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


bool ContentsEvent::Dian_Catalogue::QuestClearPrerequisite()
{
	return !isQuestCompleted;
}


void ContentsEvent::Dian_BadWeedPotion::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ����", EALERTTYPE::QuestAccept));
	}
}

bool ContentsEvent::Dian_BadWeedPotion::QuestClearPrerequisite()
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

void ContentsEvent::Dian_BadWeedPotion::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ����", EALERTTYPE::QuestClear));
	}

	isQuestCompleted = true;
}


bool ContentsEvent::Dian_Cracker::QuestClearPrerequisite()
{
	return false;
}

void ContentsEvent::Dian_Cracker::CompleteInternal()
{
	isQuestCompleted = true;
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� īŻ�α�", EALERTTYPE::QuestClear));
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� ����", EALERTTYPE::QuestAccept));
}
