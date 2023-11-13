#include "PreCompile.h"
#include "Dust_Extractor.h"

Dust_Extractor::Dust_Extractor()
{
}

Dust_Extractor::~Dust_Extractor()
{
}


void Dust_Extractor::Start()
{
	Dust::Start();

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

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

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
}