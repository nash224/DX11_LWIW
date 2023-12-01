#include "PreCompile.h"
#include "CraftPotionEvent.h"

CraftPotionEvent::CraftPotionEvent()
{
}

CraftPotionEvent::~CraftPotionEvent()
{
}


void CraftPotionEvent::Update(float _Delta)
{
	SingleEvent::Update(_Delta);
}


void CraftPotionEvent::Release()
{
	SingleEvent::Release();
}

void CraftPotionEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void CraftPotionEvent::ConversationSetting()
{
	Topic FindTopic;

	FindTopic.Data.reserve(64);
	FindTopic.Data =
	{
		{ L"좋아, 나쁜 풀 퇴치 물약 완성!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"'제거' 물약이야." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"아무튼 완성!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"일단 밖으로 나가자." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"재료가 더 없으니까 조심해서 써야 돼." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"알았어, 걱정마." , ECONVERSATIONENTITY::Ellie , 1},
	};

	FindTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(ECRAFTPOTIONTOPIC::Find, FindTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(ECRAFTPOTIONTOPIC::Find, [&]()
		{
			ConversationDone();
		});
}