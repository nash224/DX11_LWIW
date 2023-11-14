#include "PreCompile.h"
#include "Aurea.h"

#include "ContentsEvent.h"
#include "AureaFindEvent.h"
#include "UI_Inventory.h"

void Aurea::CheckAureaCurseEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Aurea_Find");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->isQuestComplete())
	{
		ShowFindAureaEvent();
		Quest->QuestComplete();
	}
}

void Aurea::ShowFindAureaEvent()
{
	std::shared_ptr<AureaFindEvent> Event = GetLevel()->CreateActor<AureaFindEvent>(EUPDATEORDER::Event);
	Event->AureaPtr = this;
	Event->Init();
}


void Aurea::CheckAureaCurseConversation()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성하지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::Curse);
	}
	else
	{
		if (nullptr != UI_Inventory::MainInventory)
		{
			if (true == UI_Inventory::MainInventory->IsItem("UncurseCandy"))
			{
				UI_Inventory::MainInventory->PopItem("UncurseCandy", 1);

				NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CurseCure);
				return;
			}
		}
		
		NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CursedNatural);
	}
}