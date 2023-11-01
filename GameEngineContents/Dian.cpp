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
	Topic HelloTopic;
	HelloTopic.EntitySpriteName = HelloTopic.Dian_Expression_Sprite_Name;

	HelloTopic.Data.reserve(64);
	HelloTopic.Data =
	{
		{ L"안녕하세요. 다이엔 상점에 오신걸 환영합니다." , ECONVERSATIONENTITY::NPC , 2},
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
	NPCConversation.CreateTopic(EDIANTOPICTYPE::Hello, HelloTopic);
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
		NPCEntity::InteractWithEllie(EDIANTOPICTYPE::Hello);
	}
}