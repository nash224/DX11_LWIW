#include "PreCompile.h"
#include "Juicer.h"

Juicer::Juicer() 
{
}

Juicer::~Juicer() 
{
}


void Juicer::Start()
{
	StaticEntity::Start();

	InitJuicer();
}

void Juicer::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Juicer::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Juicer::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Juicer::InitJuicer()
{
	CreateRendererAndAnimation();
	CreateInteractiveCollision();
}

void Juicer::CreateRendererAndAnimation()
{
	m_Juicer = CreateComponent<GameEngineSpriteRenderer>(16);
	if (nullptr == m_Juicer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Juicer->CreateAnimation("Broken", "DownFloor_Juicer_Idle_Broken.png");
	m_Juicer->CreateAnimation("Idle", "DownFloor_Juicer_0.png", 5.0f, 1, 1);
	m_Juicer->CreateAnimation("Juicy", "DownFloor_Juicer_0.png", 0.1f, 2, 9);
	m_Juicer->AutoSpriteSizeOn();

	m_Juicer->ChangeAnimation("Juicy");



	ChangeState(EJUICERSTATE::Idle);
}


void Juicer::CreateInteractiveCollision()
{
	m_InteractiveCol = CreateComponent<GameEngineCollision>(ECOLLISION::Entity);
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_InteractiveCol->SetCollisionType(ColType::SPHERE2D);
	m_InteractiveCol->Transform.SetWorldScale({ 150.0f , 150.0f });
}


void Juicer::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EJUICERSTATE::None:
	{
		MsgBoxAssert("None으로 세팅했습니다.");
		return;
	}
	break;
	case EJUICERSTATE::Idle:
		UpdateIdle(_Delta);
		break;
	case EJUICERSTATE::Juicy:
		UpdateJuicy(_Delta);
		break;
	default:
		break;
	}
}

void Juicer::ChangeState(EJUICERSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EJUICERSTATE::Idle:
			StartIdle();
			break;
		case EJUICERSTATE::Juicy:
			StartJuicy();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void Juicer::ChangeJuicerCompositionAnimation(std::string_view _StateName)
{
	std::string AnimationName = "";
	AnimationName += _StateName.data();

	if (nullptr == m_Juicer)
	{
		MsgBoxAssert("믿기지 않겠지만 렌더러가 존재하지 않습니다.");
		return;
	}

	m_Juicer->ChangeAnimation(AnimationName);
}


void Juicer::StartIdle()
{
	ChangeJuicerCompositionAnimation("Idle");
}

void Juicer::UpdateIdle(float _Delta)
{
	if (true == IsReach)
	{
		if (true == GameEngineInput::IsDown('Z'))
		{
			ChangeState(EJUICERSTATE::Juicy);
			return;
		}
	}
}

void Juicer::StartJuicy()
{
	ChangeJuicerCompositionAnimation("Juicy");
}

void Juicer::UpdateJuicy(float _Delta)
{

}