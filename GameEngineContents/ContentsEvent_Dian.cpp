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
	if (nullptr != PlayLevel::s_TimeManager)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> AureaQuest = ContentsEvent::FindQuest("Repair_Extractor");
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

void ContentsEvent::Crow_Meet::CompleteInternal()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		EventDay = PlayLevel::s_TimeManager->GetDayCount();
	}
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

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Dian_BadWeedPotion");
	}
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
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ����", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->PopData("Dian_BadWeedPotion");
	}

	UI_Inventory::PushItem("Item_Etc_12");
	UI_Inventory::UnlockSlot();

	ContentsEvent::ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = true;
}


void ContentsEvent::Dian_Cracker::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ���� ������", EALERTTYPE::QuestAccept));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Dian_Cracker_Recipe");
	}
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
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("���� ���� ������", EALERTTYPE::QuestClear));
	}

	if (nullptr != UI_Hub_MainBoard::s_QuestManager)
	{
		UI_Hub_MainBoard::s_QuestManager->RegisterData("Craft_Cracker_Potion");
		UI_Hub_MainBoard::s_QuestManager->PopData("Dian_Cracker_Recipe");
	}
}
