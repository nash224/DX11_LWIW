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

#pragma region 기본 조작

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

	{
		m_Body->CreateAnimation("SlowWalk_LEFT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		m_Body->CreateAnimation("SlowWalk_LEFTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 34, 41);
		m_Body->CreateAnimation("SlowWalk_DOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 42, 49);
		m_Body->CreateAnimation("SlowWalk_RIGHT", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		m_Body->CreateAnimation("SlowWalk_RIGHTDOWN", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 54, 61);
		m_Body->CreateAnimation("SlowWalk_LEFTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 66, 73);
		m_Body->CreateAnimation("SlowWalk_UP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 78, 85);
		m_Body->CreateAnimation("SlowWalk_RIGHTUP", "Ellie_Basic_Walk.png", Ellie_SlowWalk_Inter, 91, 98);
	}

	{
		m_Body->CreateAnimation("Run_LEFT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		m_Body->CreateAnimation("Run_LEFTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 4, 9);
		m_Body->CreateAnimation("Run_DOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 10, 15);
		m_Body->CreateAnimation("Run_RIGHT", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		m_Body->CreateAnimation("Run_RIGHTDOWN", "Ellie_Basic_Run.png", Ellie_Run_Inter, 17, 22);
		m_Body->CreateAnimation("Run_LEFTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 23, 28);
		m_Body->CreateAnimation("Run_UP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 30, 35);
		m_Body->CreateAnimation("Run_RIGHTUP", "Ellie_Basic_Run.png", Ellie_Run_Inter, 36, 41);
	}

	{
		m_Body->CreateAnimation("Throw_LEFT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		m_Body->CreateAnimation("Throw_LEFTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 4, 8);
		m_Body->CreateAnimation("Throw_DOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 9, 13);
		m_Body->CreateAnimation("Throw_RIGHT", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		m_Body->CreateAnimation("Throw_RIGHTDOWN", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 15, 19);
		m_Body->CreateAnimation("Throw_LEFTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 20, 24);
		m_Body->CreateAnimation("Throw_UP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 25, 29);
		m_Body->CreateAnimation("Throw_RIGHTUP", "Ellie_Basic_Throw.png", Ellie_Throw_Inter, 31, 35);
	}

	{
		m_Body->CreateAnimation("Riding_Idle_LEFT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Idle_LEFTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Idle_DOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 11, 14);
		m_Body->CreateAnimation("Riding_Idle_RIGHT", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Idle_RIGHTDOWN", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Idle_LEFTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 23, 26);
		m_Body->CreateAnimation("Riding_Idle_UP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 27, 30);
		m_Body->CreateAnimation("Riding_Idle_RIGHTUP", "Ellie_Basic_Riding_Standing.png", Ellie_Riding_Idle_Inter, 31, 34);
	}

	{
		m_Body->CreateAnimation("Riding_Move_LEFT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Move_LEFTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Move_DOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 11, 14);
		m_Body->CreateAnimation("Riding_Move_RIGHT", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Move_RIGHTDOWN", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Move_LEFTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 23, 26);
		m_Body->CreateAnimation("Riding_Move_UP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 27, 30);
		m_Body->CreateAnimation("Riding_Move_RIGHTUP", "Ellie_Basic_Riding_Moving.png", Ellie_Riding_Move_Inter, 31, 34);
	}

	{
		m_Body->CreateAnimation("Riding_Boost_LEFT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Boost_LEFTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 7, 10);
		m_Body->CreateAnimation("Riding_Boost_DOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 11, 14);
		m_Body->CreateAnimation("Riding_Boost_RIGHT", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Boost_RIGHTDOWN", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 15, 18);
		m_Body->CreateAnimation("Riding_Boost_LEFTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 23, 26);
		m_Body->CreateAnimation("Riding_Boost_UP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 27, 30);
		m_Body->CreateAnimation("Riding_Boost_RIGHTUP", "Ellie_Basic_Riding_Boosting.png", Ellie_Riding_Boost_Inter, 31, 34);
	}

#pragma endregion


#pragma region 채칩 및 수집

	{
		m_Body->CreateAnimation("Net_LEFT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13);
		m_Body->CreateAnimation("Net_LEFTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 7, 13);
		m_Body->CreateAnimation("Net_DOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 21, 27);
		m_Body->CreateAnimation("Net_RIGHT", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41);
		m_Body->CreateAnimation("Net_RIGHTDOWN", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 35, 41);
		m_Body->CreateAnimation("Net_LEFTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 49, 55);
		m_Body->CreateAnimation("Net_UP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 63, 69);
		m_Body->CreateAnimation("Net_RIGHTUP", "Ellie_Basic_ButterflyNet.png", Ellie_ButterflyNet_Inter, 77, 83);
	}

	{
		m_Body->CreateAnimation("RootUp_LEFT", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		m_Body->CreateAnimation("RootUp_LEFTDOWN", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 13, 20);
		m_Body->CreateAnimation("RootUp_DOWN", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 25, 32);
		m_Body->CreateAnimation("RootUp_RIGHT", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		m_Body->CreateAnimation("RootUp_RIGHTDOWN", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 34, 41);
		m_Body->CreateAnimation("RootUp_LEFTUP", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		m_Body->CreateAnimation("RootUp_UP", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 43, 50);
		m_Body->CreateAnimation("RootUp_RIGHTUP", "Ellie_Basic_Colleciton_RootUp.png", Ellie_RootUp_Inter, 51, 58);
	}

	{
		m_Body->CreateAnimation("Sit_LEFT", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Sit_LEFTDOWN", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Sit_DOWN", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 7, 12);
		m_Body->CreateAnimation("Sit_RIGHT", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 13, 18);
		m_Body->CreateAnimation("Sit_RIGHTDOWN", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 13, 18);
		m_Body->CreateAnimation("Sit_LEFTUP", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 19, 24);
		m_Body->CreateAnimation("Sit_UP", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 25, 30);
		m_Body->CreateAnimation("Sit_RIGHTUP", "Ellie_Basic_Colleciton_Sit.png", Ellie_Sit_Inter, 25, 30);
	}

	{
		m_Body->CreateAnimation("MongSiri_LEFT", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("MongSiri_LEFTDOWN", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("MongSiri_DOWN", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("MongSiri_RIGHT", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("MongSiri_RIGHTDOWN", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("MongSiri_LEFTUP", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 3, 7);
		m_Body->CreateAnimation("MongSiri_UP", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
		m_Body->CreateAnimation("MongSiri_RIGHTUP", "Ellie_Basic_Collecting_Mongsiri.png", Ellie_MongSiri_Inter, 9, 13);
	}

#pragma endregion

	{
		m_Body->CreateAnimation("Cheer", "Ellie_Basic_Cheer.png", 0.1f, 4, 15);
		m_Body->CreateAnimation("Fail", "Ellie_Basic_Fail.png", 0.1f, 5, 14);
		m_Body->CreateAnimation("Drink", "Ellie_Basic_Drink.png", 0.1f, 3, 16);
	}

	m_Body->AutoSpriteSizeOn();
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
	ChangeState(EELLIE_STATE::Idle);
	//TestCode();
}

void Ellie::SetSpawnLocalPosition(const float4& _Position)
{
	Transform.SetLocalPosition(_Position);
}

void Ellie::SetMoveControl(bool _Value)
{
	IsControl = _Value;
}


void Ellie::TestCode()
{
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->Death();
}

/////////////////////////////////////////////////////////////////////////////////////

#pragma region State 함수
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
	case EELLIE_STATE::SlowWalk:								UpdateSlowWalk(_Delta);						break;
	case EELLIE_STATE::Walk:									UpdateWalk(_Delta);							break;
	case EELLIE_STATE::Run:										UpdateRun(_Delta);							break;
	case EELLIE_STATE::Throw:									UpdateThrow(_Delta);						break;
	case EELLIE_STATE::Riding_Idle:								UpdateRiding_Idle(_Delta);					break;
	case EELLIE_STATE::Riding_Move:								UpdateRiding_Move(_Delta);					break;
	case EELLIE_STATE::Riding_Boost:							UpdateRiding_Boost(_Delta);					break;
	case EELLIE_STATE::Net:										UpdateNet(_Delta);							break;
	case EELLIE_STATE::RootUp:									UpdateRootUp(_Delta);						break;
	case EELLIE_STATE::Sit:										UpdateSit(_Delta);							break;
	case EELLIE_STATE::MongSiri:								UpdateMongSiri(_Delta);						break;
	case EELLIE_STATE::Cheer:									UpdateCheer(_Delta);						break;
	case EELLIE_STATE::Fail:									UpdateFail(_Delta);							break;
	case EELLIE_STATE::Drink:									UpdateDrink(_Delta);						break;
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
		case EELLIE_STATE::SlowWalk:							StartSlowWalk();					break;
		case EELLIE_STATE::Walk:								StartWalk();						break;
		case EELLIE_STATE::Run:									StartRun();							break;
		case EELLIE_STATE::Throw:								StartThrow();						break;
		case EELLIE_STATE::Riding_Idle:							StartRiding_Idle();					break;
		case EELLIE_STATE::Riding_Move:							StartRiding_Move();					break;
		case EELLIE_STATE::Riding_Boost:						StartRiding_Boost();				break;
		case EELLIE_STATE::Net:									StartNet();							break;
		case EELLIE_STATE::RootUp:								StartRootUp();						break;
		case EELLIE_STATE::Sit:									StartSit();							break;
		case EELLIE_STATE::MongSiri:							StartMongSiri();					break;
		case EELLIE_STATE::Cheer:								StartCheer();						break;
		case EELLIE_STATE::Fail:								StartFail();						break;
		case EELLIE_STATE::Drink:								StartDrink();						break;
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


// 호출하면 방향에 따라 애니메이션 출력을 다르게 바꿔줍니다.
void Ellie::ChangeAnimationByDirection(const std::string& _StateName, bool _DirectionInfluence /*= true*/, bool _Force /*= false*/, unsigned int _Index /*= 0*/)
{
	std::string SpriteName = "";
	SpriteName += _StateName;

	if (true == _DirectionInfluence)
	{
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
	}

	m_RenderDir = m_Dir;

	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다."); 
		return;
	}

	m_Body->ChangeAnimation(SpriteName, _Force, _Index);
}

#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////


#pragma region 이동 키 감지

bool Ellie::DetectMovement()
{
	bool IsLeftDetect = DetectVerticalMovement();
	bool IsRightDetect = DetectHorizontalMovement();

	if (true == IsLeftDetect || true == IsRightDetect)
	{
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

#pragma endregion 


// 방향을 인자로 넣으면 방향 기저벡터를 뱉어 줍니다.
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