#include "PreCompile.h"
#include "WorkplaceFindEvent.h"

WorkplaceFindEvent::WorkplaceFindEvent()
{
}

WorkplaceFindEvent::~WorkplaceFindEvent()
{
}


void WorkplaceFindEvent::Update(float _Delta)
{
	SingleEvent::Update(_Delta);
}

void WorkplaceFindEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void WorkplaceFindEvent::ConversationSetting()
{
	Topic FindTopic;

	FindTopic.Data.reserve(64);
	FindTopic.Data =
	{
		{ L"와, 버질 이것 봐." , ECONVERSATIONENTITY::Ellie , 8},
		{ L"조제실인 거 같네. 도구가 괜찮으면 물약을 만들 수 있을 거야." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
	};

	FindTopic.Data.shrink_to_fit();
	EventConveration.CreateTopic(EWORKPLACEFINDTOPIC::Find, FindTopic);

	EventConveration.SetConversationEndEvent(EWORKPLACEFINDTOPIC::Find, [&]()
		{
			State.ChangeState(ESINGLESTATE::Single);
		});
}