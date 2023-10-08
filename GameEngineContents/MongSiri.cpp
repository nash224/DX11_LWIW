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
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Mongsiri_Idle.png", 0.2f, 4, 5);
	m_Body->ChangeAnimation("Idle");
	m_Body->AutoSpriteSizeOn();

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::ObjectShadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->CreateAnimation("Shadow_Idle", "Mongsiri_Idle.png", 0.2f, 1, 3);
	m_Shadow->ChangeAnimation("Shadow_Idle");
	m_Shadow->AutoSpriteSizeOn();
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