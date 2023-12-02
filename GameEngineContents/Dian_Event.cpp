#include "PreCompile.h"
#include "Dian.h"

#include "ContentsEvent.h"
#include "UI_Inventory.h"


bool Dian::CheckWitchCatalogueEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Dian_Catalogue");
	if (nullptr == Quest)
	{
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
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
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
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
			MsgBoxAssert("�������� �ʴ� ����Ʈ ���������� ����Ʈ�� Ŭ�����Ϸ� �߽��ϴ�.");
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
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
		return false;
	}

	if (false == BadWeedPotionQuest->isQuestComplete())
	{
		return false;
	}

	const std::shared_ptr<ContentsEvent::QuestUnitBase>& CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
	if (nullptr == CrackerQuest)
	{
		MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
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
			MsgBoxAssert("�������� �ʴ� ����Ʈ ���������� ����Ʈ�� Ŭ�����Ϸ� �߽��ϴ�.");
			return false;
		}

		UI_Inventory::PopItem("NutritionPotion", 1);

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCrackerRecipe);
		return true;
	}

	return false;
}