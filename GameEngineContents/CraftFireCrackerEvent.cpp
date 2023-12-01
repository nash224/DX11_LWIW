#include "PreCompile.h"
#include "CraftFireCrackerEvent.h"

CraftFireCrackerEvent::CraftFireCrackerEvent() 
{
}

CraftFireCrackerEvent::~CraftFireCrackerEvent() 
{
}


void CraftFireCrackerEvent::Update(float _Delta)
{
	SingleEvent::Update(_Delta);
}

void CraftFireCrackerEvent::Release()
{
	SingleEvent::Release();
}

void CraftFireCrackerEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void CraftFireCrackerEvent::ConversationSetting()
{
	Topic FinallyTopic;

	FinallyTopic.Data.reserve(64);
	FinallyTopic.Data =
	{
		{ L"���� ���� �ϼ�!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"���� �̰� �� ������ �������!" , ECONVERSATIONENTITY::Ellie , 6},
		{ L"�����ؼ� �ٷ�. ���� �����ο��� �����ϴ� �� �ƴϴϱ�." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"�׷� �׷�. ��ġ�� ����� ������ �� �Ǵϱ�." , ECONVERSATIONENTITY::Ellie , 10},
		{ L"���� ������ ������ ������ ������." , ECONVERSATIONENTITY::Ellie , 10},
	};

	FinallyTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(ECRAFTTOPIC::Finally, FinallyTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(ECRAFTTOPIC::Finally, [&]()
		{
			ConversationDone();
		});
}