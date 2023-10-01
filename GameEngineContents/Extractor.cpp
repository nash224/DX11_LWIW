#include "PreCompile.h"
#include "Extractor.h"

Extractor::Extractor() 
{
}

Extractor::~Extractor() 
{
}


void Extractor::Start()
{
	StaticEntity::Start();

	InitExtractor();
}

void Extractor::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void Extractor::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Extractor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Extractor::InitExtractor()
{
	CreateRendererAndAnimation();
}

void Extractor::CreateRendererAndAnimation()
{
	m_Extractor = CreateComponent<GameEngineSpriteRenderer>(16);
	if (nullptr == m_Extractor)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Extractor->CreateAnimation("Broken", "DownFloor_Extractor_Idle_Broken.png");
	m_Extractor->CreateAnimation("Idle", "DownFloor_Extractor_0.png", 5.0f, 1, 1);
	m_Extractor->CreateAnimation("Juicy", "DownFloor_Extractor_0.png", 0.1f, 2, 9);
	m_Extractor->AutoSpriteSizeOn();

	m_Extractor->ChangeAnimation("Juicy");



	ChangeState(EJUICERSTATE::Idle);
}


void Extractor::UpdateState(float _Delta)
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

void Extractor::ChangeState(EJUICERSTATE _State)
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

void Extractor::ChangeExtractorCompositionAnimation(std::string_view _StateName)
{
	std::string AnimationName = "";
	AnimationName += _StateName.data();

	if (nullptr == m_Extractor)
	{
		MsgBoxAssert("믿기지 않겠지만 렌더러가 존재하지 않습니다.");
		return;
	}

	m_Extractor->ChangeAnimation(AnimationName);
}


void Extractor::StartIdle()
{
	ChangeExtractorCompositionAnimation("Idle");
}

void Extractor::UpdateIdle(float _Delta)
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

void Extractor::StartJuicy()
{
	ChangeExtractorCompositionAnimation("Juicy");
}

void Extractor::UpdateJuicy(float _Delta)
{

}