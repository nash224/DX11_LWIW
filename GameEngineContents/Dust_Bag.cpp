#include "PreCompile.h"
#include "Dust_Bag.h"

Dust_Bag::Dust_Bag() 
{
}

Dust_Bag::~Dust_Bag() 
{
}


void Dust_Bag::Start()
{
	Dust::Start();

	SetTopic();
}

void Dust_Bag::Update(float _Delta)
{
	Dust::Update(_Delta);
}

void Dust_Bag::Release()
{
	Dust::Release();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dust_Bag::SetTopic()
{
	std::vector<ConversationData> Datas =
	{
		{ L"���� �ִ� ����� ���� ������?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"�̹� ���������� ������?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��𼱰� �߸԰� �� ��� �ְ���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	SetConversationData(Datas);
}