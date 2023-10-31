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
		{ L"까악" , ECONVERSATIONENTITY::NPC , 1},
		{ L"까마귀?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"마녀! 까악" , ECONVERSATIONENTITY::NPC , 1},
		{ L"말을 했어?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"마녀 까마귀잖아." , ECONVERSATIONENTITY::Virgil , 4, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"아, 마녀 까마귀였구나." , ECONVERSATIONENTITY::Ellie , 3},
		{ L"마녀가 돌아왔다! 마녀가 돌아왔다!" , ECONVERSATIONENTITY::NPC , 1},
		{ L"나는 여기 처음왔는데." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"마녀가 돌아왔다!" , ECONVERSATIONENTITY::NPC , 1, CrowTopic.Color_RED},
		{ L"말이 그렇게 잘 통하진 않네." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"서비스 제공! 까악 서비스 제공! 마녀 카탈로그." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"마녀 카탈로그!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"꼭 한 번 써보고 싶었어." , ECONVERSATIONENTITY::Ellie, 6 },
		{ L"지금 등록하면 선물을 드립니다. 까악" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"마녀 카탈로그를 이용하세요. 마녀 카탈로그를 이용하세요." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"선물도 준대! 지금만 준대!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"까악 선물" , ECONVERSATIONENTITY::NPC, 1, CrowTopic.Color_RED},
		{ L"다목적 접착제? 주방용품? 포크 숟가락?" , ECONVERSATIONENTITY::Virgil, 1 , CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"하여튼 마녀 카탈로그는 필요해." , ECONVERSATIONENTITY::Ellie, 2},
		{ L"잠깐 있을거라도 좋긴하지." , ECONVERSATIONENTITY::Virgil, 1, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"재료나 물약 제조법 같은 것도 살 수 있어." , ECONVERSATIONENTITY::Virgil, 1, CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"좋아 일단 등록하자." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"감사합니다. 까악 감사합니다. 직원 방문! 직원 방문!" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"까악 직원 방문" , ECONVERSATIONENTITY::NPC, 1 , CrowTopic.Color_RED },
		{ L"언제?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"업무 끝! 업무 끝! 퇴근 시간" , ECONVERSATIONENTITY::NPC, 0 },
		{ L"정시 퇴근" , ECONVERSATIONENTITY::NPC, 1, CrowTopic.Color_RED },
		{ L"이렇게 갑자기?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"마녀 까마귀는 그렇게 말이 잘 통하는 편은 아니지." , ECONVERSATIONENTITY::Virgil, 1 ,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan},
		{ L"음, 그럼 일단은 계속 주변을 탐색 해볼까?" , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"마녀 카탈로그는 언제 올지 모르니까 말야" , ECONVERSATIONENTITY::Virgil, 5,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan },
		{ L"주변을 둘러보자." , ECONVERSATIONENTITY::Virgil, 5,CrowTopic.Color_BLACK, CrowTopic.Font_JejuHanlasan },
	};

	CrowTopic.Data.shrink_to_fit();
	m_ConversationInfo.CreateTopic(EDIANTOPICTYPE::Crow, CrowTopic);


	Topic HelloTopic;
	HelloTopic.EntitySpriteName = HelloTopic.Dian_Expression_Sprite_Name;

	HelloTopic.Data.reserve(64);
	HelloTopic.Data =
	{
		{ L"안녕하세요" , ECONVERSATIONENTITY::NPC , 2},
		{ L"ㅎㅇ" , ECONVERSATIONENTITY::Virgil },
		{ L"반갑습니다니다니다니다니 다니다니 다니다니다니다다니다니다" , ECONVERSATIONENTITY::Virgil },
		{ L"반갑습니다니다니다니다니 다니다니 다니다니다니다다니다니다 다니다니다다니다니다" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"반갑습니다" , ECONVERSATIONENTITY::NPC , 2},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 3},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"반갑습니다" , ECONVERSATIONENTITY::NPC , 2},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"ㅎㅇ" , ECONVERSATIONENTITY::Virgil }
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