#include "PreCompile.h"
#include "Dust_Elevator.h"

#include "UpperLift.h"
#include "BaseLift.h"


Dust_Elevator::Dust_Elevator() 
{
}

Dust_Elevator::~Dust_Elevator() 
{
}


void Dust_Elevator::Start()
{
	Dust::Start();

	SetTopic();
}

void Dust_Elevator::Update(float _Delta)
{
	Dust::Update(_Delta);
}

void Dust_Elevator::Release()
{
	Dust::Release();
}

void Dust_Elevator::SetTopic()
{
	std::vector<ConversationData> Datas =
	{
		{ L"저쪽에도 먼지가 남았잖아, 엘리." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"반찬은 남기지 마렴, 엘리." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"교장실에는 들어오면 안 된다고 했지, 엘리." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"그렇게 좀 하지 그랬어." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"오, 이거 마녀 승강기잖아!" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"이래서 선생님 말은 들어야 되는 거야." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"빨리 내려가 보자." , ECONVERSATIONENTITY::Ellie , 5},
	};

	SetConversationData(Datas);
	SetEndEvnet(std::bind(&Dust_Elevator::ActiveUpperLift, this));
}

void Dust_Elevator::ActiveUpperLift()
{
	if (false == BaseLift::MainLiftPtr.expired())
	{
		BaseLift::MainLiftPtr.lock()->EnableEv();
	}
}