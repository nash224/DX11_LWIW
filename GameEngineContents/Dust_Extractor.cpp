#include "PreCompile.h"
#include "Dust_Extractor.h"

#include "ContentsEvent.h"

Dust_Extractor::Dust_Extractor()
{
}

Dust_Extractor::~Dust_Extractor()
{
}


void Dust_Extractor::Start()
{
	Dust::Start();
	Dust::SetDustScaleRatio(1.5f);

	SetTopic();
}

void Dust_Extractor::Update(float _Delta)
{
	Dust::Update(_Delta);
}

void Dust_Extractor::Release()
{
	Dust::Release();
}

void Dust_Extractor::SetTopic()
{
	std::vector<ConversationData> Datas =
	{ 
		{ L"착즙기다! 나 이거 알아." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"학교에서 지겹도록 썼었지. 좀 더 작은거였지만." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"쓰긴 힘들겠는데? 밑에 유리병 좀 봐." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"아, 정말이네. 깨져있어." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"친절한 두꺼비라도 한 마리 필요하곘는데." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"이걸 쓰려면 유리병을 먼저 구해야겠네." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"최소한 착즙기는 고쳐야 물약을 만들 수 있어." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	SetConversationData(Datas);

	Dust::SetEndEvnet(std::bind(&Dust_Extractor::QuestAccept, this));
}

void Dust_Extractor::QuestAccept()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Repair_Extractor");
	if (true == Quest.expired())
	{
		MsgBoxAssert("퀘스트가 존재하지 않습니다.");
		return;
	}

	Quest.lock()->QuestAccept();
}