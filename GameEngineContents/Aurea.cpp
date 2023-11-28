#include "PreCompile.h"
#include "Aurea.h"

#include "ContentsEvent.h"

#include "UI_Inventory.h"

EAUREASTATE Aurea::CurState = EAUREASTATE::Curse;
Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 90.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	InteractiveActor::SetGearName("��ȭ�ϱ�");
}

void Aurea::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	State.Update(_Delta);
}

void Aurea::Release()
{
	NPCEntity::Release();

	AureaRenderer = nullptr;
	ShadowRenderer = nullptr;
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
	ApplyDepth();
	RendererSetting();
	ConversationSetting();
	StateSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}

	AureaRenderer = CreateComponent<GameEngineSpriteRenderer>();
	AureaRenderer->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	AureaRenderer->AutoSpriteSizeOn();
	AureaRenderer->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	AureaRenderer->ChangeAnimation("Idle");

	const float Depth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer->Transform.SetLocalPosition(float4{ 0.0f, RendererCorrection , Depth });
	ShadowRenderer->SetSprite("Aurea_idle.png", 1);
}

void Aurea::StateSetting()
{
	CreateStateParameter CurseState;
	CurseState.Start = std::bind(&Aurea::StartCurse, this, std::placeholders::_1);
	CurseState.Stay = std::bind(&Aurea::UpdateCurse, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EAUREASTATE::Curse, CurseState);

	CreateStateParameter NormalState;
	NormalState.Start = std::bind(&Aurea::StartNormal, this, std::placeholders::_1);
	NormalState.Stay = std::bind(&Aurea::UpdateNormal, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EAUREASTATE::Normal, NormalState);

	State.ChangeState(CurState);
}


void Aurea::StartCurse(GameEngineState* _Parent)
{
	CheckAureaCurseEvent();
}

void Aurea::StartNormal(GameEngineState* _Parent)
{

}


void Aurea::UpdateCurse(float _Delta, GameEngineState* _Parent)
{
	if (true == InteractiveActor::IsEnalbeActive)
	{
		CheckAureaCurseConversation();
	}
}

void Aurea::UpdateNormal(float _Delta, GameEngineState* _Parent)
{

}

void Aurea::ConversationSetting()
{
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
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::Curse, CurseTopic);

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::Curse, [&]()
			{
				NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CurseAfter);
			});
	}



	{
		Topic CurseAfterTopic;

		CurseAfterTopic.Data.reserve(64);
		CurseAfterTopic.Data =
		{
			{ L"���� �ڿ��� �����ϴ� ����ΰ� ��." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"��ȭ�� �� �� ������?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"������ �����ؾ� ���� ������?" , ECONVERSATIONENTITY::Ellie, 1 },
			{ L"�ܼ��� ������ �ƴ� �� ������" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"�� ���� ���簡 ���� ���̾�.", ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"���ֶ� �ɷȴٴ� �ž�?", ECONVERSATIONENTITY::Ellie , 1},
			{ L"�ڿ��� �����ϴ� ���� �� �� �ִ� ����?", ECONVERSATIONENTITY::Ellie , 5},
			{ L"�ڿ��������� ����? ���� �ȵ��� ����." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"������� �̻��� ����� �����ϱ�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"���ָ� ������ �� �ִ� �������� ������ �⺻ �������� ���� �ٵ�...", ECONVERSATIONENTITY::Ellie , 9},
			{ L"��, �ٵ� ���� ���� ������ �� ���ݾ�.", ECONVERSATIONENTITY::Ellie , 1},
			{ L"ä���� �� �����ؾ� ������ ���� �� �ִµ� ��¼��?", ECONVERSATIONENTITY::Ellie , 9},
			{ L"�Ʊ� �۾��ǿ��� ��Ḧ �� �� �ֿ��ݾ�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"�� ������ �������� ���� ������ ���� �� ��������." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"�׸��� �� ���� �þ�?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"����? ����?" , ECONVERSATIONENTITY::Ellie, 1},
			{ L"����� ���������� �� �´� �������� ��� �־�." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"���?" , ECONVERSATIONENTITY::Ellie, 9},
			{ L"��, �����̳�." , ECONVERSATIONENTITY::Ellie, 7},
			{ L"����, �׷� �������� ������ ���� ���ָ� Ǯ������." , ECONVERSATIONENTITY::Ellie, 10},
			{ L"�׸��� �������� �� �������� �޴°���." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"�׷� ����." , ECONVERSATIONENTITY::Ellie, 5},
			{ L"�켱 �������� ���� ���� ������ Ȯ���غ���." , ECONVERSATIONENTITY::Ellie, 1},
		};

		CurseAfterTopic.Data.shrink_to_fit();
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseAfter, CurseAfterTopic);

		NPCEntity::NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseAfter, 19, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestAccept();
			});

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::CurseAfter, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestAccept();
			});
	}



	{
		Topic CurseCureTopic;
		CurseCureTopic.EntitySpriteName = CurseCureTopic.Expression_Aurea_Sprite_Name;

		CurseCureTopic.Data.reserve(64);
		CurseCureTopic.Data =
		{
			{ L"�̰� �� �� ��ź��ðھ��?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, ��Ų� �ڿ��� �ູ��..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"��...��...?" , ECONVERSATIONENTITY::NPC, 0 },
			{ L"��, �ȳ��ϼ���" , ECONVERSATIONENTITY::Ellie , 5},
			{ L"���� ���� ����� ���ϰ� �־�?" , ECONVERSATIONENTITY::NPC, 0 },
			{ L"��, �׷� �� ���ƿ�" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, ���� ����. �ڿ��� ���̳� ��������." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"���� ���ֿ��� ���׿�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"���� ���ۿ��� ���� �� ������ �� ���� �����ߴµ�." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"�ʹ� �� ���� �� ������ ����� �׳� ����ĥ ���� ��� ����." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"�װ� �� �ڷδ� ��� ���� �ڿ��� �����ϴ� ���� ���ͼ�..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"�Ųٷε� ���غ���, �۷� ������� �� �ڿ��� �����ϴ� �� �ۿ� �� �� ��� �ʹ� �������." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"���� �ڿ��� ���̳� �Ծ����� ���ھ�." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"�׷��� �����ϰ� ���� ������ ���ֶ� �����̳׿�." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"��, ���� ����. �� �̸��� �ƿ췹�ƾ�." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"�� ���� ���غ��� �̸�����..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"���� ��������. ���� ���࿡��." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"Ȥ�� ���� �����ٸ��Ѱ� �ִ�? �Ʊ��� ������ �ϰ� �;�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"��, �׷� ��Ź.. �ϳ� ����� �ɱ��?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��Ź�� �ƴ϶� ������ ���̾�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"��� �ʿ���?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"������ �� �������� ����Ϸ��� �ϴϱ� �������� �μ��� �־." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"������ ��ǰ�� �����Ű���?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"� ������ ��ǰ�� �ʿ���?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"����⿡ ���� �������̶�, �ν��͸� ���� �ν��� �����̰� �ʿ��ؿ�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��ø�... �� �� ã�ƺ���." , ECONVERSATIONENTITY::NPC , 0},
			{ L"ã�ƿԾ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"�̰� �޾�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"�̰� �󸶿���?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, ������. �̰� �װ� �� ���ָ� Ǯ���� �䷹��." , ECONVERSATIONENTITY::NPC , 1},
			{ L"��, �����̴�." , ECONVERSATIONENTITY::Ellie, 5 },
			{ L"�ƽ����� �ν��Ϳ� �� �ν��� �����̴� ������ �ִ°� ����." , ECONVERSATIONENTITY::NPC , 1},
			{ L"������ ������ �� �� ì�ܿð�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"�� ���� ���� ����� ���� ������ ����." , ECONVERSATIONENTITY::NPC , 1},
			{ L"���ƿ�, �� �� ��Ź�帱�Կ�." , ECONVERSATIONENTITY::Ellie, 5 },
		};

		CurseCureTopic.Data.shrink_to_fit();
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseCure, CurseCureTopic);

		NPCEntity::NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseCure, 28, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestComplete();
			});

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::CurseCure, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("�������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestComplete();

				CurState = EAUREASTATE::Normal;
				State.ChangeState(EAUREASTATE::Normal);
			});
	}


	{
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
}
