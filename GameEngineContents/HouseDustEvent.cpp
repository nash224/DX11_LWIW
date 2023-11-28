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
		{ L"���� �� ��, ����. ����Ʈ ��ũ��!" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�� ���� û�� �ؾ� �Ǵ� ������ �Ź��ٸ� �ܶ� ���̴µ�." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"�� ���� �ٷ� �� ���̾�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"û���ϸ鼭 ������ �� ã�ƺ���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
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