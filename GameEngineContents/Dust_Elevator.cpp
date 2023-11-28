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
		{ L"���ʿ��� ������ �����ݾ�, ����." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"������ ������ ����, ����." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"����ǿ��� ������ �� �ȴٰ� ����, ����." , ECONVERSATIONENTITY::Ellie , 4},
		{ L"�׷��� �� ���� �׷���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��, �̰� ���� �°����ݾ�!" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"�̷��� ������ ���� ���� �Ǵ� �ž�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"���� ������ ����." , ECONVERSATIONENTITY::Ellie , 5},
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