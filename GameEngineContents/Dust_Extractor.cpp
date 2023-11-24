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
		{ L"������! �� �̰� �˾�." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"�б����� ���㵵�� �����. �� �� �����ſ�����." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���� ����ڴµ�? �ؿ� ������ �� ��." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��, �����̳�. �����־�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"ģ���� �β���� �� ���� �ʿ��ρٴµ�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�̰� ������ �������� ���� ���ؾ߰ڳ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"�ּ��� ������ ���ľ� ������ ���� �� �־�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	SetConversationData(Datas);

	Dust::SetEndEvnet(std::bind(&Dust_Extractor::QuestAccept, this));
}

void Dust_Extractor::QuestAccept()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Repair_Extractor");
	if (true == Quest.expired())
	{
		MsgBoxAssert("����Ʈ�� �������� �ʽ��ϴ�.");
		return;
	}

	Quest.lock()->QuestAccept();
}