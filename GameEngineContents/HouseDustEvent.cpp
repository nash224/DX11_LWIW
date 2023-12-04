#include "PreCompile.h"
#include "HouseDustEvent.h"

HouseDustEvent::HouseDustEvent() 
{
}

HouseDustEvent::~HouseDustEvent() 
{
}


void HouseDustEvent::Update(float _Delta)
{
	SingleEvent::Update(_Delta);
}

void HouseDustEvent::Release()
{
	SingleEvent::Release();
}

void HouseDustEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void HouseDustEvent::ConversationSetting()
{
	Topic LookDustTopic;
	LookDustTopic.Elli_StartIndex = 3;

	LookDustTopic.Data.reserve(64);
	LookDustTopic.Data =
	{
		{ L"���� �� ��, ����. ����Ʈ ��ũ��!" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�� ���� û�� �ؾ� �Ǵ� ������ �Ź��ٸ� �ܶ� ���̴µ�." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"�� ���� �ٷ� �� ���̾�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"û���ϸ鼭 ������ �� ã�ƺ���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	LookDustTopic.Data.shrink_to_fit();
	SingleEvent::EventConveration.CreateTopic(EHOUSEDUSTTOPIC::LookDust, LookDustTopic);

	SingleEvent::EventConveration.SetConversationEndEvent(EHOUSEDUSTTOPIC::LookDust, [&]()
		{
			ConversationDone();
		});
}