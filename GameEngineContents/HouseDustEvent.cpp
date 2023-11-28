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
	AboutHouseConveration.UpdateConversation(_Delta);
	State.Update(_Delta);
}

void HouseDustEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void HouseDustEvent::Init()
{
	ConversationSetting();
	StateSetting();
}

void HouseDustEvent::ConversationSetting()
{
	Topic LookDustTopic;
	LookDustTopic.Elli_First_Sprite_Index = 3;

	LookDustTopic.Data.reserve(64);
	LookDustTopic.Data =
	{
		{ L"저것 좀 봐, 엘리. 퀘스트 마크야!" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"내 눈엔 청소 해야 되는 먼지와 거미줄만 잔뜩 보이는데." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"내 말이 바로 그 말이야." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"청소하면서 쓸만한 걸 찾아보자." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	LookDustTopic.Data.shrink_to_fit();
	AboutHouseConveration.CreateTopic(EHOUSEDUSTTOPIC::LookDust, LookDustTopic);

	AboutHouseConveration.SetConversationEndEvent(EHOUSEDUSTTOPIC::LookDust, [&]()
		{
			State.ChangeState(EHOUSEDUSTSTATE::None);
		});
}

void HouseDustEvent::StateSetting()
{
	CreateStateParameter LookDustState;
	LookDustState.Start = std::bind(&HouseDustEvent::StartHouseDust, this, std::placeholders::_1);
	LookDustState.End = std::bind(&HouseDustEvent::EndHouseDust, this, std::placeholders::_1);
	State.CreateState(EHOUSEDUSTSTATE::LookDust, LookDustState);

	State.ChangeState(EHOUSEDUSTSTATE::LookDust);
}

void HouseDustEvent::StartHouseDust(GameEngineState* _Parent)
{
	AboutHouseConveration.StartConversation(EHOUSEDUSTTOPIC::LookDust);
}

void HouseDustEvent::EndHouseDust(GameEngineState* _Parent)
{
	Death();
}