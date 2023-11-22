#include "PreCompile.h"
#include "SingleEvent.h"

SingleEvent::SingleEvent()
{
}

SingleEvent::~SingleEvent()
{
}


void SingleEvent::Update(float _Delta)
{
	EventConveration.UpdateConversation(_Delta);
	State.Update(_Delta);
}

void SingleEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SingleEvent::Init()
{
	ConversationSetting();
	StateSetting();
}

//
//void SingleEvent::ConversationSetting()
//{
//	Topic FindTopic;
//	FindTopic.Elli_First_Sprite_Index = 3;
//
//	FindTopic.Data.reserve(64);
//	FindTopic.Data =
//	{
//		{ L"저것 좀 봐, 엘리. 퀘스트 마크야!" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
//		{ L"내 눈엔 청소 해야 되는 먼지와 거미줄만 잔뜩 보이는데." , ECONVERSATIONENTITY::Ellie , 4},
//		{ L"내 말이 바로 그 말이야." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
//		{ L"청소하면서 쓸만한 걸 찾아보자." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
//	};
//
//	FindTopic.Data.shrink_to_fit();
//	EventConveration.CreateTopic(EWORKPLACEFINDTOPIC::Find, FindTopic);
//
//	EventConveration.SetConversationEndEvent(EWORKPLACEFINDTOPIC::Find, [&]()
//		{
//			State.ChangeState(EWORKPLACEFINDTOPIC::None);
//		});
//}

void SingleEvent::StateSetting()
{
	CreateStateParameter FindState;
	FindState.Start = std::bind(&SingleEvent::StartEvent, this, std::placeholders::_1);
	FindState.End = std::bind(&SingleEvent::EndEvent, this, std::placeholders::_1);
	State.CreateState(ESINGLESTATE::Single, FindState);

	State.ChangeState(ESINGLESTATE::Single);
}

void SingleEvent::StartEvent(GameEngineState* _Parent)
{
	EventConveration.StartConversation(ESINGLESTATE::Single);
}

void SingleEvent::EndEvent(GameEngineState* _Parent)
{
	Death();
}

void SingleEvent::ConversationDone()
{
	State.ChangeState(ESINGLESTATE::None);
}