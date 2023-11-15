#include "PreCompile.h"
#include "Dian.h"

#include "ContentsEvent.h"


bool Dian::CheckWitchCatalogueEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_Catalogue");
	if (true == Quest.expired())
	{
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
		return false;
	}

	if (false == Quest.lock()->isQuestComplete())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::WitchCatalogue);

		Quest.lock()->QuestComplete();
		return true;
	}

	return false;
}

bool Dian::CheckPotionVerificationEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
		return false;
	}

	if (false == Quest.lock()->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::PotionVerification);

		Quest.lock()->QuestComplete();
		return true;
	}
	else if (true == Quest.lock()->CheckPrerequisiteQuest())
	{

	}

	return false;
}

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