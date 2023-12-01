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

void SingleEvent::Release()
{
	EventConveration.Release();
}

void SingleEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void SingleEvent::Init()
{
	ConversationSetting();
	StateSetting();
}


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