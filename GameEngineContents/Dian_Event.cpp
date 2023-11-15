#include "PreCompile.h"
#include "Dian.h"

#include "ContentsEvent.h"
#include "UI_Inventory.h"


bool Dian::CheckWitchCatalogueEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_Catalogue");
	if (true == Quest.expired())
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == Quest.lock()->isQuestComplete())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::WitchCatalogue);
		return true;
	}

	return false;
}

bool Dian::CheckPotionVerificationEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == Quest.lock()->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::PotionVerification);
		return true;
	}
	else if (true == Quest.lock()->CheckPrerequisiteQuest())
	{
		if (nullptr != UI_Inventory::MainInventory)
		{
			if (false == UI_Inventory::MainInventory->IsItem("BadGrassPotion"))
			{
				MsgBoxAssert("존재하지 않는 퀘스트 아이템으로 퀘스트를 클리어하려 했습니다.");
				return false;
			}

			UI_Inventory::MainInventory->PopItem("BadGrassPotion", 1);
		}

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::DragonFly);
		return true;
	}

	return false;
}

bool Dian::CheckDian_CrackerEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> BadWeedPotionQuest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
	if (true == BadWeedPotionQuest.expired())
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == BadWeedPotionQuest.lock()->isQuestComplete())
	{
		return false;
	}

	std::weak_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
	if (true == CrackerQuest.expired())
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == CrackerQuest.lock()->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCracker);
		return true;
	}
	else if (true == CrackerQuest.lock()->CheckPrerequisiteQuest())
	{
		if (nullptr != UI_Inventory::MainInventory)
		{
			if (false == UI_Inventory::MainInventory->IsItem("NutritionPotion"))
			{
				MsgBoxAssert("존재하지 않는 퀘스트 아이템으로 퀘스트를 클리어하려 했습니다.");
				return false;
			}

			UI_Inventory::MainInventory->PopItem("NutritionPotion", 1);
		}

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCrackerRecipe);
		return true;
	}

	return false;
}