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

	{
		m_Body->CreateAnimation("Idle_LEFT", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		m_Body->CreateAnimation("Idle_LEFTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 4, 7);
		m_Body->CreateAnimation("Idle_DOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 8, 11);
		m_Body->CreateAnimation("Idle_RIGHT", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		m_Body->CreateAnimation("Idle_RIGHTDOWN", "Ellie_Basic_Idle.png", EllieIdleInter, 12, 15);
		m_Body->CreateAnimation("Idle_LEFTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 16, 19);
		m_Body->CreateAnimation("Idle_UP", "Ellie_Basic_Idle.png", EllieIdleInter, 20, 23);
		m_Body->CreateAnimation("Idle_RIGHTUP", "Ellie_Basic_Idle.png", EllieIdleInter, 24, 27);
	}

	{
		m_Body->CreateAnimation("Walk_LEFT", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		m_Body->CreateAnimation("Walk_LEFTDOWN", "Ellie_Basic_Walk.png", 0.1f, 34, 41);
		m_Body->CreateAnimation("Walk_DOWN", "Ellie_Basic_Walk.png", 0.1f, 42, 49);
		m_Body->CreateAnimation("Walk_RIGHT", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		m_Body->CreateAnimation("Walk_RIGHTDOWN", "Ellie_Basic_Walk.png", 0.1f, 54, 61);
		m_Body->CreateAnimation("Walk_LEFTUP", "Ellie_Basic_Walk.png", 0.1f, 66, 73);
		m_Body->CreateAnimation("Walk_UP", "Ellie_Basic_Walk.png", 0.1f, 78, 85);
		m_Body->CreateAnimation("Walk_RIGHTUP", "Ellie_Basic_Walk.png", 0.1f, 91, 98);
	}
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
	if (nullptr == m_Body)
	{
		MsgBoxAssert("존재하지 않은 액터를 사용하려 했습니다.");
		return;
	}

	m_Body->AutoSpriteSizeOn();

	ChangeState(EELLIE_STATE::Idle);
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
		case EELLIE_STATE::Idle:								StartIdle();						break;
		case EELLIE_STATE::Walk:								StartWalk();						break;
		case EELLIE_STATE::Run:									StartRun();							break;
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
		SpriteName += "_UP";
		break;
	case EDIRECTION::LEFTUP:
		SpriteName += "_LEFTUP";
		break;
	case EDIRECTION::LEFT:
		SpriteName += "_LEFT";
		break;
	case EDIRECTION::LEFTDOWN:
		SpriteName += "_LEFTDOWN";
		break;
	case EDIRECTION::DOWN:
		SpriteName += "_DOWN";
		break;
	case EDIRECTION::RIGHTDOWN:
		SpriteName += "_RIGHTDOWN";
		break;
	case EDIRECTION::RIGHT:
		SpriteName += "_RIGHT";
		break;
	case EDIRECTION::RIGHTUP:
		SpriteName += "_RIGHTUP";
		break;
	default:
		break;
	}

	m_RenderDir = m_Dir;

	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다."); 
		return;
	}

	m_Body->ChangeAnimation(SpriteName, _Force, _Index);
}


bool Ellie::DetectMovement()
{
	bool IsLeftDetect = DetectVerticalMovement();
	bool IsRightDetect = DetectHorizontalMovement();

	if (true == IsLeftDetect || true == IsRightDetect)
	{
		/*if (EHORIZONTAL_KEY_STATE::Center == m_HorizontalKey && EVERTICAL_KEY_STATE::Down == m_VerticalKey)
		{
			m_Dir = EDIRECTION::DOWN;
		}*/

		if (EHORIZONTAL_KEY_STATE::Center == m_HorizontalKey)
		{
			if (EVERTICAL_KEY_STATE::Down == m_VerticalKey)
			{
				m_Dir = EDIRECTION::DOWN;
			}
			else
			{
				m_Dir = EDIRECTION::UP;
			}
		}
		else if (EHORIZONTAL_KEY_STATE::Left == m_HorizontalKey)
		{
			if (EVERTICAL_KEY_STATE::Down == m_VerticalKey)
			{
				m_Dir = EDIRECTION::LEFTDOWN;
			}
			else if (EVERTICAL_KEY_STATE::Up == m_VerticalKey)
			{
				m_Dir = EDIRECTION::LEFTUP;
			}
			else
			{
				m_Dir = EDIRECTION::LEFT;
			}
		}
		else
		{
			if (EVERTICAL_KEY_STATE::Down == m_VerticalKey)
			{
				m_Dir = EDIRECTION::RIGHTDOWN;
			}
			else if (EVERTICAL_KEY_STATE::Up == m_VerticalKey)
			{
				m_Dir = EDIRECTION::RIGHTUP;
			}
			else
			{
				m_Dir = EDIRECTION::RIGHT;
			}
		}

		return true;
	}
	
	return false;
}


bool Ellie::DetectVerticalMovement()
{
	m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	bool isPressUp = false;
	bool isPressDown = false;

	bool isMoveVertical = false;

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		isPressUp = true;
		isMoveVertical = true;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		isPressDown = true;
		isMoveVertical = true;
	}

	if (true == isMoveVertical && true == isPressUp && true == isPressDown)
	{
		isMoveVertical = false;
	}

	if (true == isMoveVertical)
	{
		if (true == isPressUp)
		{
			m_VerticalKey = EVERTICAL_KEY_STATE::Up;
		}

		if (true == isPressDown)
		{
			m_VerticalKey = EVERTICAL_KEY_STATE::Down;
		}
	}

	return isMoveVertical;
}


bool Ellie::DetectHorizontalMovement()
{
	m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;

	bool isPressLeft = false;
	bool isPressRight = false;

	bool isMoveHorizontal = false;

	if (true == GameEngineInput::IsPress(VK_LEFT))
	{
		isPressLeft = true;
		isMoveHorizontal = true;
	}

	if (true == GameEngineInput::IsPress(VK_RIGHT))
	{
		isPressRight = true;
		isMoveHorizontal = true;
	}

	if (true == isPressLeft && true == isPressRight)
	{
		isMoveHorizontal = false;
	}

	if (true == isMoveHorizontal && true == isPressLeft && true == isPressRight)
	{
		isMoveHorizontal = false;
	}

	if (true == isMoveHorizontal)
	{
		if (true == isPressLeft)
		{
			m_HorizontalKey = EHORIZONTAL_KEY_STATE::Left;
		}

		if (true == isPressRight)
		{
			m_HorizontalKey = EHORIZONTAL_KEY_STATE::Right;
		}
	}

	return isMoveHorizontal;
}


float4 Ellie::CalulateDirectionVectorToDir(const EDIRECTION _Direction)
{
	float4 DirVector = float4::ZERO;

	switch (_Direction)
	{
	case EDIRECTION::UP:
		DirVector = { 0.0f , 1.0f };
		break;
	case EDIRECTION::LEFTUP:
		DirVector = { -1.0f , 1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::LEFT:
		DirVector = { -1.0f , 0.0f };
		break;
	case EDIRECTION::LEFTDOWN:
		DirVector = { -1.0f , -1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::RIGHTUP:
		DirVector = { 1.0f , 1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::RIGHT:
		DirVector = { 1.0f , 0.0f };
		break;
	case EDIRECTION::RIGHTDOWN:
		DirVector = { 1.0f , -1.0f };
		DirVector.Normalize();
		break;
	case EDIRECTION::DOWN:
		DirVector = { 0.0f , -1.0f };
		break;
	default:
		break;
	}

	return DirVector;
}