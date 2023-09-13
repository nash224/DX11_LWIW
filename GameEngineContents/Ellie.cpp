#include "PreCompile.h"
#include "Ellie.h"

Ellie::Ellie() 
{
}

Ellie::~Ellie() 
{
}



void Ellie::Start()
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Ellie);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("컴포넌트를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle_UP", "Ellie_Basic_Idle", 20, 23);
	m_Body->CreateAnimation("Idle_LEFTUP", "Ellie_Basic_Idle", 16, 19);
	m_Body->CreateAnimation("Idle_LEFT", "Ellie_Basic_Idle", 4, 7);
	m_Body->CreateAnimation("Idle_LEFTDOWN", "Ellie_Basic_Idle", 4, 7);
	m_Body->CreateAnimation("Idle_DOWN", "Ellie_Basic_Idle", 8, 11);
	m_Body->CreateAnimation("Idle_RIGHTUP", "Ellie_Basic_Idle", 24, 27);
	m_Body->CreateAnimation("Idle_RIGHT", "Ellie_Basic_Idle", 12, 15);
	m_Body->CreateAnimation("Idle_RIGHTDOWN", "Ellie_Basic_Idle", 12, 15);
}

void Ellie::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void Ellie::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Ellie::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Ellie::Init()
{
	m_State = EELLIE_STATE::Idle;
	
}


/////////////////////////////////////////////////////////////////////////////////////


void Ellie::StateUpdate(float _Delta)
{
	switch (m_State)
	{
	case EELLIE_STATE::None:
	{
		MsgBoxAssert("지정해주지 않은 행동으로 업데이트 하려고 했습니다.");
		return;
	}
		break;
	case EELLIE_STATE::Idle:									UpdateIdle(_Delta);							break;
	case EELLIE_STATE::Walk:									UpdateWalk(_Delta);							break;
	case EELLIE_STATE::Run:										UpdateRun(_Delta);							break;
	default:
		break;
	}
}


void Ellie::ChangeState(EELLIE_STATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EELLIE_STATE::None:
		{
			MsgBoxAssert("행동을 지정해주지 않았습니다.");
			return;
		}
			break;
		case EELLIE_STATE::Idle:							StartIdle();						break;
		case EELLIE_STATE::Walk:							StartWalk();						break;
		case EELLIE_STATE::Run:								StartRun();							break;
		default:
			break;
		}

		m_State = _State;
	}
	else
	{
		MsgBoxAssert("같은 행동으로 바꾸려고 했습니다.");
		return;
	}	
}

void Ellie::ChangeAnimationByDirection(const std::string& _StateName, bool _Force /*= false*/, unsigned int _Index /*= 0*/)
{
	std::string SpriteName = "";
	SpriteName += _StateName;
	
	switch (m_Dir)
	{
	case EDIRECTION::UP:
		SpriteName += "UP";
		break;
	case EDIRECTION::LEFTUP:
		SpriteName += "LEFTUP";
		break;
	case EDIRECTION::LEFT:
		SpriteName += "LEFT";
		break;
	case EDIRECTION::LEFTDOWN:
		SpriteName += "LEFTDOWN";
		break;
	case EDIRECTION::DOWN:
		SpriteName += "DOWN";
		break;
	case EDIRECTION::RIGHTDOWN:
		SpriteName += "RIGHTDOWN";
		break;
	case EDIRECTION::RIGHT:
		SpriteName += "RIGHT";
		break;
	case EDIRECTION::RIGHTUP:
		SpriteName += "RIGHTUP";
		break;
	default:
		break;
	}

	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다."); 
		return;
	}

	m_Body->ChangeAnimation(SpriteName, _Force, _Index);
}
