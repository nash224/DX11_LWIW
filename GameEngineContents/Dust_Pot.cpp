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
		{ L"��, �̰� ���� �� �Ƴ�?" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"'Ǫ�� ���� ����'���� ���� �� ������." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"���� ����� �� ����." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�б����� �Ź� �α��� �ܸ� ����µ� ����!" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"�����ϴ� ����� �������?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�翬����." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"��Ȯ�ϰ� ������ ���� �� ����, ���� ���Ⱑ ��� ��������" , ECONVERSATIONENTITY::Ellie , 10},
		{ L"��~�μ�~" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��~�μ�~ �ùٸ� ������ ��������ܴ�." , ECONVERSATIONENTITY::Ellie , 10},
		{ L"��Ḹ ������ ������ ���� �� �ְھ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���� ������ �� ���°� �������� ����." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��ħ ������ ��ᰡ �� �����ϱ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"������ ��� ��Ḧ Ȯ���ϰ�, ���� Ǯ ��ġ ������ ����� ����?" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"������ D Ű�� ���� Ȯ���� �� �־�." , ECONVERSATIONENTITY::Ellie , 1},
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
		MsgBoxAssert("����Ʈ�� �������� �ʽ��ϴ�.");
		return;
	}

	Quest.lock()->QuestAccept();
}