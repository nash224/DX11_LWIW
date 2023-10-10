#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"

MongSiri::MongSiri() 
{
}

MongSiri::~MongSiri() 
{
}


void MongSiri::Start()
{
	DynamicEntity::Start();

	m_CollectionMethod = ECOLLECTION_METHOD::MongSiri;
	m_CollectionTool = ETOOLTYPE::Gloves;
}

void MongSiri::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void MongSiri::Release()
{
	DynamicEntity::Release();
}

void MongSiri::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void MongSiri::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void MongSiri::Init()
{
	CreateAndSetRenderer();
	CreateAndSetCollision(ECOLLISION::Entity, { 50, 50 }, float4::ZERO, ColType::SPHERE2D);
}

void MongSiri::CreateAndSetRenderer()
{
	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::ObjectShadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Mongsiri_Idle.png", 0.2f, 4, 6);
	m_Body->SetFrameEvent("Idle", 5, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Idle.png", 1);
		});

	m_Body->CreateAnimation("Idle_Back", "Mongsiri_Idle.png", 0.2f, 7, 9);
	m_Body->CreateAnimation("Jump", "Mongsiri_Jump.png", 0.1f, 5, 14);
	m_Body->SetFrameEvent("Jump", 5, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	m_Body->SetFrameEvent("Jump", 6, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	m_Body->SetFrameEvent("Jump", 7, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	m_Body->SetFrameEvent("Jump", 8, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	m_Body->SetFrameEvent("Jump", 13, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Jump_Back", "Mongsiri_Jump.png", 0.1f, 15, 24);
	m_Body->SetFrameEvent("Jump_Back", 15, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	m_Body->SetFrameEvent("Jump_Back", 16, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	m_Body->SetFrameEvent("Jump_Back", 17, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	m_Body->SetFrameEvent("Jump_Back", 18, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	m_Body->SetFrameEvent("Jump_Back", 23, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Look", "Mongsiri_Idle.png", 0.05f, 4, 5);
	m_Body->SetStartEvent("Look", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Look_Back", "Mongsiri_Idle.png", 0.2f, 6, 7);
	m_Body->SetStartEvent("Look_Back", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Idle.png", 1);
		});

	m_Body->CreateAnimation("Collected", "Mongsiri_Collected.png", 0.2f, 3, 9);
	m_Body->SetStartEvent("Collected", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Collected.png", 1);
		});
	m_Body->SetEndEvent("Collected", [=](GameEngineSpriteRenderer*)
		{
			m_Body->ChangeAnimation("CollectedA");
		});

	m_Body->CreateAnimation("CollectedA", "Mongsiri_CollectedA.png", 0.05f);


	m_Body->CreateAnimation("Disappear", "Mongsiri_Disappear.png", 0.2f, 10, 33);

	m_Body->ChangeAnimation("Collected");
	m_Body->AutoSpriteSizeOn();
}


/////////////////////////////////////////////////////////////////////////////////////

void MongSiri::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EMONGSIRISTATE::Idle:								StartIdle();					break;
	case EMONGSIRISTATE::Jump:								StartJump();					break;
	case EMONGSIRISTATE::Look:								StartLook();					break;
	case EMONGSIRISTATE::Escape:							StartEscape();					break;
	case EMONGSIRISTATE::None:																break;
		break;
	default:
		break;
	}
}

void MongSiri::ChangeState(EMONGSIRISTATE _State)
{
	if (m_State != _State)
	{
		switch (_State)
		{
		case EMONGSIRISTATE::Idle:							UpdateIdle();					break;
		case EMONGSIRISTATE::Jump:							UpdateJump();					break;
		case EMONGSIRISTATE::Look:							UpdateLook();					break;
		case EMONGSIRISTATE::Escape:						UpdateEscape();					break;
		case EMONGSIRISTATE::None:															break;
		default:
			break;
		}

		m_State = _State;
	}
}