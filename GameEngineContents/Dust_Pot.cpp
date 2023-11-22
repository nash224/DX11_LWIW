#include "PreCompile.h"
#include "Dust_Pot.h"

#include "PlayLevel.h"
#include "AlertManager.h"

#include "ContentsEvent.h"
#include "AlchemyPot.h"

Dust_Pot::Dust_Pot()
{
	
}

Dust_Pot::~Dust_Pot()
{
}


void Dust_Pot::Start()
{
	Dust::Start();

	CreateAndSetCollision(ECOLLISION::Entity, float4(140.0f), float4::ZERO, ColType::SPHERE2D);
	SetTopic();
}

void Dust_Pot::Update(float _Delta)
{
	Dust::Update(_Delta);
}

void Dust_Pot::Release()
{
	Dust::Release();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dust_Pot::SetTopic()
{
	std::vector<ConversationData> Datas =
	{
		{ L"와, 이거 좋은 솥 아냐?" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"'푸른 벼락 공방'에서 만든 거 같은데." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"옛날 방식인 거 같다." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"학교에선 매번 싸구려 솥만 썼었는데 드디어!" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"조제하는 방법은 기억하지?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"당연하지." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"정확하게 가공된 재료와 불 세기, 국자 젓기가 모두 합쳐져야" , ECONVERSATIONENTITY::Ellie , 10},
		{ L"비~로소~" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"비~로소~ 올바른 물약이 만들어진단다." , ECONVERSATIONENTITY::Ellie , 10},
		{ L"재료만 있으면 물약은 만들 수 있겠어." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"가공 도구는 영 상태가 안좋지만 말야." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"마침 버려진 재료가 좀 있으니까." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"도감을 열어서 재료를 확인하고, 나쁜 풀 퇴치 물약을 만들어 볼까?" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"도감은 D 키를 눌러 확인할 수 있어." , ECONVERSATIONENTITY::Ellie , 1},
	};

	SetConversationData(Datas);
	Dust::SetStartEvent(std::bind(&Dust_Pot::StartEvent, this));
	Dust::SetEndEvnet(std::bind(&Dust_Pot::QuestAccept, this));
}

void Dust_Pot::StartEvent()
{
	AlchemyPot::RepairPot();
}

void Dust_Pot::QuestAccept()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Craft_Potion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("퀘스트가 존재하지 않습니다.");
		return;
	}

	Quest.lock()->QuestAccept();
}