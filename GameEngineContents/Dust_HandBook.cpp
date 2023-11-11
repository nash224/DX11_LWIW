#include "PreCompile.h"
#include "Dust_HandBook.h"

Dust_HandBook::Dust_HandBook() 
{
}

Dust_HandBook::~Dust_HandBook() 
{
}


void Dust_HandBook::Start()
{
	Dust::Start();

	SetTopic();
}

void Dust_HandBook::Update(float _Delta)
{
	Dust::Update(_Delta);
}

void Dust_HandBook::Release()
{
	Dust::Release();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dust_HandBook::SetTopic()
{
	std::vector<ConversationData> Datas = 
	{
		{ L"��, ��ø�̾�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���߿� �� �� �ְڴµ�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	SetConversationData(Datas);
}