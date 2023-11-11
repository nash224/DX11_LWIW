#include "PreCompile.h"
#include "ContentsEvent.h"


#include "PlayLevel.h"
#include "TimeManager.h"

#include "UI_Alert_Quest.h"
#include "PlayLevel.h"
#include "AlertManager.h"
#include "FadeObject.h"


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

bool ContentsEvent::Dian_Cracker::CheckPrerequisiteQuest()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest3 = ContentsEvent::FindQuest("Dian_Quest_3");
	if (nullptr == Quest3)
	{
		MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
		return false;
	}

	if (true == Quest3->isQuestComplete())
	{
		if (nullptr != PlayLevel::s_AlertManager)
		{
			
		}

		return true;
	}

	return false;
}

void ContentsEvent::Dian_Cracker::QuestComplete()
{
	isQuestCompleted = true;
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� īŻ�α�", EALERTTYPE::QuestClear));
	PlayLevel::s_AlertManager->RegisterAlert(AlertData("�Ҳɳ��� ���� ����", EALERTTYPE::QuestAccept));
}