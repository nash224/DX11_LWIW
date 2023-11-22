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
//		{ L"���� �� ��, ����. ����Ʈ ��ũ��!" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
//		{ L"�� ���� û�� �ؾ� �Ǵ� ������ �Ź��ٸ� �ܶ� ���̴µ�." , ECONVERSATIONENTITY::Ellie , 4},
//		{ L"�� ���� �ٷ� �� ���̾�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
//		{ L"û���ϸ鼭 ������ �� ã�ƺ���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
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