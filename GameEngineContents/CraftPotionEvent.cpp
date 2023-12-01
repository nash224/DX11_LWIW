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
		{ L"����, ���� Ǯ ��ġ ���� �ϼ�!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"'����' �����̾�." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"�ƹ�ư �ϼ�!" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"�ϴ� ������ ������." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��ᰡ �� �����ϱ� �����ؼ� ��� ��." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"�˾Ҿ�, ������." , ECONVERSATIONENTITY::Ellie , 1},
	};

	FindTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(ECRAFTPOTIONTOPIC::Find, FindTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(ECRAFTPOTIONTOPIC::Find, [&]()
		{
			ConversationDone();
		});
}