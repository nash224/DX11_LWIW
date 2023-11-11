#include "PreCompile.h"
#include "Aurea.h"

#include "ContentsEvent.h"
#include "AureaFindEvent.h"




void Aurea::CheckAureaCurseEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest("Aurea_Find");
	if (nullptr == Quest)
	{
		MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
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