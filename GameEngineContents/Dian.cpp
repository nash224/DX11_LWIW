#include "PreCompile.h"
#include "Dian.h"

Dian::Dian() 
{
}

Dian::~Dian() 
{
}


void Dian::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);

	ConversationSetting();
	StateSetting();
}

void Dian::StateSetting()
{
	CreateStateParameter NormalState;
	NormalState.Stay = std::bind(&Dian::NormalUpdate, this, std::placeholders::_1, std::placeholders::_2);

	State.CreateState(EDIANSTATE::Normal, NormalState);
	State.ChangeState(EDIANSTATE::Normal);
}

void Dian::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	State.Update(_Delta);
}

void Dian::Release()
{
	NPCEntity::Release();
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Dian::ConversationSetting()
{
	Topic CrowTopic;
	CrowTopic.EntitySpriteName = CrowTopic.Crow_Expression_Sprite_Name;

	CrowTopic.Data.reserve(64);
	CrowTopic.Data =
	{
		{ L"���" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"����! ���" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���� �߾�?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"���� ����ݾ�." , ECONVERSATIONENTITY::Virgil , 4, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"��, ���� ��Ϳ�����." , ECONVERSATIONENTITY::Ellie , 3},
		{ L"���డ ���ƿԴ�! ���డ ���ƿԴ�!" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���� ���� ó���Դµ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���డ ���ƿԴ�!" , ECONVERSATIONENTITY::NPC , 1, CrowTopic.Color_RED},
		{ L"���� �׷��� �� ������ �ʳ�." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"���� ����! ��� ���� ����! ���� īŻ�α�." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"���� īŻ�α�!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"�� �� �� �Ẹ�� �;���." , ECONVERSATIONENTITY::Ellie, 6 },
		{ L"���� ����ϸ� ������ �帳�ϴ�. ���" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"���� īŻ�α׸� �̿��ϼ���. ���� īŻ�α׸� �̿��ϼ���." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"������ �ش�! ���ݸ� �ش�!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"��� ����" , ECONVERSATIONENTITY::NPC, 1, CrowTopic.Color_RED},
		{ L"�ٸ��� ������? �ֹ��ǰ? ��ũ ������?" , ECONVERSATIONENTITY::Virgil, 1 , CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"�Ͽ�ư ���� īŻ�α״� �ʿ���." , ECONVERSATIONENTITY::Ellie, 2},
		{ L"��� �����Ŷ� ��������." , ECONVERSATIONENTITY::Virgil, 1, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"��ᳪ ���� ������ ���� �͵� �� �� �־�." , ECONVERSATIONENTITY::Virgil, 1, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"���� �ϴ� �������." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"�����մϴ�. ��� �����մϴ�. ���� �湮! ���� �湮!" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"��� ���� �湮" , ECONVERSATIONENTITY::NPC, 1 , CrowTopic.Color_RED },
		{ L"����?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"���� ��! ���� ��! ��� �ð�" , ECONVERSATIONENTITY::NPC, 0 },
		{ L"���� ���" , ECONVERSATIONENTITY::NPC, 1, CrowTopic.Color_RED },
		{ L"�̷��� ���ڱ�?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"���� ��ʹ� �׷��� ���� �� ���ϴ� ���� �ƴ���." , ECONVERSATIONENTITY::Virgil, 1 ,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"��, �׷� �ϴ��� ��� �ֺ��� Ž�� �غ���?" , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"���� īŻ�α״� ���� ���� �𸣴ϱ� ����" , ECONVERSATIONENTITY::Virgil, 5,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan },
		{ L"�ֺ��� �ѷ�����." , ECONVERSATIONENTITY::Virgil, 5,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan },
	};

	CrowTopic.Data.shrink_to_fit();
	m_ConversationInfo.CreateTopic(EDIANTOPICTYPE::Crow, CrowTopic);


	Topic HelloTopic;
	HelloTopic.EntitySpriteName = HelloTopic.Dian_Expression_Sprite_Name;

	HelloTopic.Data.reserve(64);
	HelloTopic.Data =
	{
		{ L"�ȳ��ϼ���" , ECONVERSATIONENTITY::NPC , 2},
		{ L"����" , ECONVERSATIONENTITY::Virgil },
		{ L"�ݰ����ϴٴϴٴϴٴϴٴ� �ٴϴٴ� �ٴϴٴϴٴϴٴٴϴٴϴ�" , ECONVERSATIONENTITY::Virgil },
		{ L"�ݰ����ϴٴϴٴϴٴϴٴ� �ٴϴٴ� �ٴϴٴϴٴϴٴٴϴٴϴ� �ٴϴٴϴٴٴϴٴϴ�" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::NPC , 2},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 3},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::NPC , 2},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"����" , ECONVERSATIONENTITY::Virgil }
	};

	HelloTopic.Data.shrink_to_fit();
	m_ConversationInfo.CreateTopic(EDIANTOPICTYPE::Hello, HelloTopic);
}


void Dian::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void Dian::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Dian_idle.png"))
	{
		GameEngineSprite::CreateCut("Dian_idle.png", 3, 3);
	}

	static constexpr const int RendererOrder = 0;

	m_Body = CreateComponent<GameEngineSpriteRenderer>(RendererOrder);
	m_Body->Transform.SetLocalPosition({0.0f, RendererYCorrection });
	m_Body->CreateAnimation("Idle", "Dian_idle.png", 0.15f, 3, 7, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->ChangeAnimation("Idle");
	

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RendererOrder);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererYCorrection, ShadowDepth });
	m_Shadow->SetSprite("Dian_idle.png", 0);
}





void Dian::NormalUpdate(float _DeltaTime, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		NPCEntity::InteractWithEllie(EDIANTOPICTYPE::Crow);
	}
}