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
		{ L"여기 있던 마녀는 어디로 갔을까?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"이미 오래전이지 않을까?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"어디선가 잘먹고 잘 살고 있겠지." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
	};

	SetConversationData(Datas);
}