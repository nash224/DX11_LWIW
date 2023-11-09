#include "PreCompile.h"
#include "ContentsEvent.h"


#include "PlayLevel.h"
#include "TimeManager.h"

#include "UI_Alert_Quest.h"
#include "PlayLevel.h"
#include "AlertManager.h"


bool ContentsEvent::Crow_Meet::CheckPrerequisiteQuest()
{
	if (nullptr == PlayLevel::s_TimeManager)
	{
		MsgBoxAssert("Ÿ�ӸŴ����� �������� �ʽ��ϴ�.");
		return false;
	}

	if (PlayLevel::s_TimeManager->GetHour() >= 11)
	{
		return true;
	}

	return false;
}

bool ContentsEvent::Dian_Quest_1::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& CrowQuest = ContentsEvent::FindQuest(EEVENTTYPE::Crow_Meet);
	if (nullptr == CrowQuest)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}

	if (true == CrowQuest->isQuestComplete())
	{
		return true;
	}

	return true;
}

bool ContentsEvent::Dian_Quest_2::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest1 = ContentsEvent::FindQuest(EEVENTTYPE::Dian_Quest_1);
	if (nullptr == Quest1)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}
	
	if (true == Quest1->isQuestComplete())
	{
		return true;
	}

	return false;
}

bool ContentsEvent::Dian_Quest_3::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest2 = ContentsEvent::FindQuest(EEVENTTYPE::Dian_Quest_2);
	if (nullptr == Quest2)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}

	if (true == Quest2->isQuestComplete())
	{
		return true;
	}

	return false;
}

bool ContentsEvent::Dian_Quest_4::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest3 = ContentsEvent::FindQuest(EEVENTTYPE::Dian_Quest_3);
	if (nullptr == Quest3)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}

	if (true == Quest3->isQuestComplete())
	{
		if (nullptr != PlayLevel::s_AlertManager)
		{
			PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� īŻ�α�", EALERTTYPE::QuestClear));
			PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� ����", EALERTTYPE::QuestAccept));
		}

		return true;
	}

	return false;
}

bool ContentsEvent::Dian_Quest_5::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest4 = ContentsEvent::FindQuest(EEVENTTYPE::Dian_Quest_4);
	if (nullptr == Quest4)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}

	if (true == Quest4->isQuestComplete())
	{
		return true;
	}

	return false;
}
