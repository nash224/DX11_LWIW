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
		{ L"폭죽 물약 완성!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"드디어 이걸 내 손으로 만들었어!" , ECONVERSATIONENTITY::Ellie , 6},
		{ L"조심해서 다뤄. 괜히 행정부에서 관리하는 게 아니니까." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"그럼 그럼. 다치는 사람이 나오면 안 되니까." , ECONVERSATIONENTITY::Ellie , 10},
		{ L"폭죽 물약을 가지고 밖으로 나가자." , ECONVERSATIONENTITY::Ellie , 10},
	};

	FinallyTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(ECRAFTTOPIC::Finally, FinallyTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(ECRAFTTOPIC::Finally, [&]()
		{
			ConversationDone();
		});
}