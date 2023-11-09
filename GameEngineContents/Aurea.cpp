#include "PreCompile.h"
#include "Aurea.h"


#include "ContentsEvent.h"
#include "AureaFindEvent.h"



EAUREASTATE Aurea::CurState = EAUREASTATE::Normal;
Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 180.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void Aurea::Update(float _Delta)
{
	NPCEntity::Update(_Delta);
}

void Aurea::Release()
{
	NPCEntity::Release();
}

void Aurea::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Aurea::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Aurea::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
	ConversationSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}

	AureaRenderer  = CreateComponent<GameEngineSpriteRenderer>();
	AureaRenderer ->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	AureaRenderer ->AutoSpriteSizeOn();
	AureaRenderer ->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	AureaRenderer ->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererCorrection , GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)});
	m_Shadow->SetSprite("Aurea_idle.png", 1);
}

void Aurea::StateSetting()
{

}


void Aurea::StartCurse(GameEngineState* _Parent)
{

}

void Aurea::StartNormal(GameEngineState* _Parent)
{

}


void Aurea::UpdateCurse(float _Delta, GameEngineState* _Parent)
{
	/*CheckAureaCurseEvent();*/

	if (true == IsEnalbeActive)
	{
		NPCEntity::InteractWithEllie(EAUREATOPICTYPE::Curse);
	}
}

void Aurea::UpdateNormal(float _Delta, GameEngineState* _Parent)
{

}



void Aurea::CheckAureaCurseEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest(EQUESTTYPE::Aurea_Find);
	if (nullptr == Quest)
	{
		MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
		return;
	}

	if (false == Quest->isQuestComplete())
	{
		ShowFindAureaEvent();
		Quest->QuestComplete();
	}
}

void Aurea::ShowFindAureaEvent()
{
	std::shared_ptr<AureaFindEvent> Event = GetLevel()->CreateActor<AureaFindEvent>(EUPDATEORDER::Event);
	Event->AureaPtr = this;
	Event->Init();
}


void Aurea::ConversationSetting()
{
	Topic CurseTopic;
	CurseTopic.EntitySpriteName = CurseTopic.Expression_Aurea_Sprite_Name;

	CurseTopic.Data.reserve(64);
	CurseTopic.Data =
	{
		{ L"�ȳ��ϼ���, Ȥ�� ���� �ֹ��̼���?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��, ���� �ڿ��̿���." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"��?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"������ �ʹ� �Ƹ����� �ʳ���? �޻� ���� Ǫ�� ����..." , ECONVERSATIONENTITY::NPC , 1},
		{ L"��...��..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���� �Ƹ��ٿ� �ڿ��̿���." , ECONVERSATIONENTITY::NPC , 1},
		{ L"�ڿ��� ������ �����Ͻó� ����." , ECONVERSATIONENTITY::Ellie, 1},
		{ L"�̷��� �Ƹ��ٿ� �ڿ��� ������� ���� �� ����." , ECONVERSATIONENTITY::NPC , 1},
		{ L"��, �׷� ���߿� �ٽ� �ðԿ�." , ECONVERSATIONENTITY::Ellie, 1},
		{ L"�� ���� �ϴ� �Ʒ��� ������ �ڿ��� ��������!" , ECONVERSATIONENTITY::NPC , 1},
	};

	CurseTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::Curse, CurseTopic);

	NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::Curse, [&]()
		{
			NPCConversation.StartConversation(EAUREATOPICTYPE::CurseAfter);
		});

	Topic CurseAfterTopic;

	CurseAfterTopic.Data.reserve(64);
	CurseAfterTopic.Data =
	{
		{ L"���� �ڿ��� �����ϴ� ����ΰ� ��." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"��ȭ�� �� �� ������?" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"������ �����ؾ� ���� ������?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"�ܼ��� ������ �ƴ� �� ������" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"�� ���� ���簡 ���� ���̾�.", ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"���ֶ� �ɷȴٴ� �ž�?", ECONVERSATIONENTITY::Ellie , 1},
		{ L"�ڿ��� �����ϴ� ���� �� �� �ִ� ����?", ECONVERSATIONENTITY::Ellie , 5},
		{ L"�ڿ��������� ����? ���� �ȵ��� ����." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"������� �̻��� ����� �����ϱ�." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"���ָ� ������ �� �ִ� �������� ������ �⺻ �������� ���� �ٵ�...", ECONVERSATIONENTITY::Ellie , 9},
		{ L"��, �ٵ� ���� ���� ������ �� ���ݾ�.", ECONVERSATIONENTITY::Ellie , 1},
		{ L"ä���� �� �����ؾ� ������ ���� �� �ִµ� ��¼��?", ECONVERSATIONENTITY::Ellie , 9},
		{ L"�Ʊ� �۾��ǿ��� ��Ḧ �� �� �ֿ��ݾ�." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"�� ������ �������� ���� ������ ���� �� ��������." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"�׸��� �� ���� �þ�?" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"����? ����?" , ECONVERSATIONENTITY::Ellie, 1},
		{ L"����� ���������� �� �´� �������� ��� �־�." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"���?" , ECONVERSATIONENTITY::Ellie, 9},
		{ L"��, �����̳�." , ECONVERSATIONENTITY::Ellie, 7},
		{ L"����, �׷� �������� ������ ���� ���ָ� Ǯ������." , ECONVERSATIONENTITY::Ellie, 10},
		{ L"�׸��� �������� �� �������� �޴°���." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"�׷� ����." , ECONVERSATIONENTITY::Ellie, 5},
		{ L"�켱 �������� ���� ���� ������ Ȯ���غ���." , ECONVERSATIONENTITY::Ellie, 1},
	};

	CurseTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseAfter, CurseAfterTopic);

	NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseAfter, 19,[&]()
		{
			// �ڿ��������� ����
		});


	Topic CursedNaturalTopic;
	CursedNaturalTopic.EntitySpriteName = CursedNaturalTopic.Expression_Aurea_Sprite_Name;

	CursedNaturalTopic.Data.reserve(1);
	CursedNaturalTopic.Data =
	{
		{ L"��... �ڿ��̿�.." , ECONVERSATIONENTITY::NPC , 1},
	};

	CursedNaturalTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::CursedNatural, CursedNaturalTopic);
}
