#include "PreCompile.h"
#include "Dian.h"

#include "ContentsEvent.h"
#include "UI_Inventory.h"


bool Dian::CheckWitchCatalogueEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Dian_Catalogue");
	if (nullptr == Quest)
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == Quest->isQuestComplete())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::WitchCatalogue);
		return true;
	}

	return false;
}

bool Dian::CheckPotionVerificationEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
	if (nullptr == Quest)
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == Quest->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::PotionVerification);
		return true;
	}
	else if (true == Quest->CheckPrerequisiteQuest())
	{
		if (false == UI_Inventory::IsItem("BadGrassPotion"))
		{
			MsgBoxAssert("존재하지 않는 퀘스트 아이템으로 퀘스트를 클리어하려 했습니다.");
			return false;
		}

		UI_Inventory::PopItem("BadGrassPotion", 1);

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::DragonFly);
		return true;
	}

	return false;
}

bool Dian::CheckDian_CrackerEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& BadWeedPotionQuest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
	if (nullptr == BadWeedPotionQuest)
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == BadWeedPotionQuest->isQuestComplete())
	{
		return false;
	}

	const std::shared_ptr<ContentsEvent::QuestUnitBase>& CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
	if (nullptr == CrackerQuest)
	{
		MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
		return false;
	}

	if (false == CrackerQuest->IsQuestAccepted())
	{
		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCracker);
		return true;
	}
	else if (true == CrackerQuest->CheckPrerequisiteQuest())
	{
		if (false == UI_Inventory::IsItem("NutritionPotion"))
		{
			MsgBoxAssert("존재하지 않는 퀘스트 아이템으로 퀘스트를 클리어하려 했습니다.");
			return false;
		}

		UI_Inventory::PopItem("NutritionPotion", 1);

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCrackerRecipe);
		return true;
	}

	return false;
}