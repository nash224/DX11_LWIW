#include "PreCompile.h"
#include "Dian.h"
//
//
//
//void Dian::CheckDianCurseEvent()
//{
//	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Dian_Find");
//	if (nullptr == Quest)
//	{
//		MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
//		return;
//	}
//
//	if (false == Quest->isQuestComplete())
//	{
//		ShowFindDianEvent();
//		Quest->QuestComplete();
//	}
//}
//
//void Dian::ShowFindDianEvent()
//{
//	std::shared_ptr<DianFindEvent> Event = GetLevel()->CreateActor<DianFindEvent>(EUPDATEORDER::Event);
//	Event->DianPtr = this;
//	Event->Init();
//}
//
//
//void Dian::CheckDianCurseConversation()
//{
//	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_Cure");
//	if (true == Quest.expired())
//	{
//		MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
//		return;
//	}
//
//	if (false == Quest.lock()->IsQuestAccepted())
//	{
//		NPCEntity::ConverseWithEllie(EDianTOPICTYPE::Curse);
//	}
//	else
//	{
//		if (nullptr != UI_Inventory::MainInventory)
//		{
//			if (true == UI_Inventory::MainInventory->IsItem("UncurseCandy"))
//			{
//				UI_Inventory::MainInventory->PopItem("UncurseCandy", 1);
//
//				NPCEntity::ConverseWithEllie(EDianTOPICTYPE::CurseCure);
//				return;
//			}
//		}
//
//		NPCEntity::ConverseWithEllie(EDianTOPICTYPE::CursedNatural);
//	}
//}