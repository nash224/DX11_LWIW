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
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Aurea_Cure");
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성하지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::Curse);
	}
	else
	{
		if (true == UI_Inventory::IsItem("UncurseCandy"))
		{
			UI_Inventory::PopItem("UncurseCandy", 1);

			NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CurseCure);
			return;
		}
		
		NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CursedNatural);
	}
}