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
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestAccept));
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
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("물약 검증", EALERTTYPE::QuestClear));
	}

	UI_Inventory::MainInventory->UnlockSlot();
	ContentsEvent::ToolData[static_cast<int>(ETOOLTYPE::Dragonfly)] = true;
}


void ContentsEvent::Dian_Cracker::AcceptInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("불꽃놀이 포션 레시피", EALERTTYPE::QuestAccept));
	}
}

bool ContentsEvent::Dian_Cracker::QuestClearPrerequisite()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		if (true == UI_Inventory::MainInventory->IsItem("NutritionPotion"))
		{
			return true;
		}
	}

	return false;
}

void ContentsEvent::Dian_Cracker::CompleteInternal()
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		PlayLevel::s_AlertManager->RegisterAlert(AlertData("불꽃놀이 포션 레시피", EALERTTYPE::QuestClear));
	}
}
