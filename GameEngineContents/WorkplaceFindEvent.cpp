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

void WorkplaceFindEvent::Release()
{
	SingleEvent::Release();
}

void WorkplaceFindEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void WorkplaceFindEvent::ConversationSetting()
{
	Topic FindTopic;

	FindTopic.Data.reserve(64);
	FindTopic.Data =
	{
		{ L"��, ���� �̰� ��." , ECONVERSATIONENTITY::Ellie , 8},
		{ L"�������� �� ����. ������ �������� ������ ���� �� ���� �ž�." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"û�Ҵ� �ؾ߰�����." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"��...�� û�Ҵ�..." , ECONVERSATIONENTITY::Ellie , 4},
	};

	FindTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(EWORKPLACEFINDTOPIC::Find, FindTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(EWORKPLACEFINDTOPIC::Find, [&]()
		{
			ConversationDone();
		});
}