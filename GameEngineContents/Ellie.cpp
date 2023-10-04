#include "PreCompile.h"
#include "Ellie.h"


#include "PortalObject.h"
#include "BackDrop_PlayLevel.h"

Ellie::Ellie() 
{
}

Ellie::~Ellie() 
{
}

Ellie* Ellie::MainEllie = nullptr;
EELLIE_STATUS Ellie::g_Status = EELLIE_STATUS::None;
bool Ellie::FirstInitCheck = false;
void Ellie::Start()
{
	StartFSM();
	StartCollision();
}

void Ellie::Update(float _Delta)
{
	UpdateState(_Delta);
	UpdateCollision();
}


void Ellie::LevelStart(class GameEngineLevel* _NextLevel)
{
	OnLevelStart();
}

void Ellie::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void Ellie::StartFSM()
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

void Ellie::StartCollision()
{
	EllieCol = CreateComponent<GameEngineCollision>(ECOLLISION::Player);
	if (nullptr == EllieCol)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}


	EllieCol->Transform.SetLocalScale(float4{ 4.0f , 4.0f });
	EllieCol->SetCollisionType(ColType::AABBBOX2D);
}


// Ellie를 생성하면 무조건 실행해야하는 함수입니다.
void Ellie::Init()
{
	if (false == FirstInitCheck)
	{
		ChangeStatus(EELLIE_STATUS::Normal);
		FirstInitCheck = true;
	}

	SetPixelPointBaseOnCenter();

	MainEllie = this;
}

// 앨리의 위치를 지정합니다.
void Ellie::SetSpawnLocalPosition(const float4& _Position)
{
	Transform.SetLocalPosition(_Position);
}


// 생성되거나 레벨이 바뀔때 호출되고 앨리의 상태를 초기화합니다.
void Ellie::OnLevelStart()
{
	RenewStatus();

	MainEllie = this;
}

void Ellie::RenewStatus()
{
	if (EELLIE_STATUS::Normal == g_Status && EELLIE_STATE::Idle != m_State)
	{
  		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	if (EELLIE_STATUS::Riding == g_Status && EELLIE_STATE::Riding_Idle != m_State)
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	if (EELLIE_STATE::None == m_State)
	{
		MsgBoxAssert("등록되지 않은 행동패턴입니다.");
		return;
	}
}

void Ellie::ChangeStatus(const EELLIE_STATUS _Status)
{
	if (_Status != g_Status)
	{
		g_Status = _Status;
	}
}

// 움직일 수 있게 권한을 줍니다.
void Ellie::OnControl()
{
	IsControl = true;
}

// 움직일 수 없게 권한을 뺐습니다.
void Ellie::OffControl()
{
	IsControl = false;

	RenewStatus();
}




// 픽셀 충돌에 사용될 변수입니다.
// 액터의 중앙기준으로 초기화 되며 각 방향에 필요한 체크포인트를 설정합니다.
void Ellie::SetPixelPointBaseOnCenter()
{
	float4 HalfPixelCheckScale = m_PixelCheckScale.Half();

	m_PixelCheckPoint.TopLeft = m_PixelCheckPosBaseOnCenter + float4{ -HalfPixelCheckScale.X + CheckPointGap , HalfPixelCheckScale.Y };
	m_PixelCheckPoint.TopRight = m_PixelCheckPosBaseOnCenter + float4{ HalfPixelCheckScale.X - CheckPointGap , HalfPixelCheckScale.Y };
	m_PixelCheckPoint.LeftTop = m_PixelCheckPosBaseOnCenter + float4{ -HalfPixelCheckScale.X , HalfPixelCheckScale.Y - CheckPointGap };
	m_PixelCheckPoint.LeftBottom = m_PixelCheckPosBaseOnCenter + float4{ -HalfPixelCheckScale.X , -HalfPixelCheckScale.Y + CheckPointGap };
	m_PixelCheckPoint.RightTop = m_PixelCheckPosBaseOnCenter + float4{ HalfPixelCheckScale.X , HalfPixelCheckScale.Y - CheckPointGap };
	m_PixelCheckPoint.RightBottom = m_PixelCheckPosBaseOnCenter + float4{ HalfPixelCheckScale.X , -HalfPixelCheckScale.Y + CheckPointGap };
	m_PixelCheckPoint.BottomLeft = m_PixelCheckPosBaseOnCenter + float4{ -HalfPixelCheckScale.X + CheckPointGap , -HalfPixelCheckScale.Y };
	m_PixelCheckPoint.BottomRight = m_PixelCheckPosBaseOnCenter + float4{ HalfPixelCheckScale.X - CheckPointGap , -HalfPixelCheckScale.Y };
}




/////////////////////////////////////////////////////////////////////////////////////

#pragma region State 함수
void Ellie::UpdateState(float _Delta)
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
void Ellie::ChangeAnimationByDirection(std::string_view _StateName, bool _DirectionInfluence /*= true*/, bool _Force /*= false*/, unsigned int _Index /*= 0*/)
{
	std::string SpriteName = "";
	SpriteName += _StateName.data();

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

void Ellie::ChangeDirectionAnimation(std::string_view _StateName)
{
	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection(_StateName, true, false, CurIndex);
	}
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


#pragma region 이동 및 방향 

// 방향을 인자로 넣으면 방향 기저벡터를 반환해줍니다.
float4 Ellie::CalculateDirectionVectorToDir(const EDIRECTION _Direction)
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

// 노멀 모드일 때, 속력을 계산해줍니다.
void Ellie::CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce)
{
	float4 DirVector = CalculateDirectionVectorToDir(m_Dir);

	m_MoveVector = DirVector * _MAXMoveForce;
	
	float4 CurPos = Transform.GetWorldPosition();

	float4 LeftCheckPoint = CurPos;
	float4 RightCheckPoint = CurPos;
	float4 MoveDirVector = float4::ZERO;
	EDIRECTION CheckDir = EDIRECTION::CENTER;


	switch (m_Dir)
	{
	case EDIRECTION::UP:
		LeftCheckPoint += m_PixelCheckPoint.TopLeft;
		RightCheckPoint += m_PixelCheckPoint.TopRight;
		break;
	case EDIRECTION::LEFTUP:
		LeftCheckPoint += m_PixelCheckPoint.LeftTop;
		RightCheckPoint += m_PixelCheckPoint.TopLeft;
		break;
	case EDIRECTION::LEFT:
		LeftCheckPoint += m_PixelCheckPoint.LeftBottom;
		RightCheckPoint += m_PixelCheckPoint.LeftTop;
		break;
	case EDIRECTION::LEFTDOWN:
		LeftCheckPoint += m_PixelCheckPoint.BottomLeft;
		RightCheckPoint += m_PixelCheckPoint.LeftBottom;
		break;
	case EDIRECTION::DOWN:
		LeftCheckPoint += m_PixelCheckPoint.BottomRight;
		RightCheckPoint += m_PixelCheckPoint.BottomRight;
		break;
	case EDIRECTION::RIGHTDOWN:
		LeftCheckPoint += m_PixelCheckPoint.RightBottom;
		RightCheckPoint += m_PixelCheckPoint.BottomRight;
		break;
	case EDIRECTION::RIGHT:
		LeftCheckPoint += m_PixelCheckPoint.RightTop;
		RightCheckPoint += m_PixelCheckPoint.RightBottom;
		break;
	case EDIRECTION::RIGHTUP:
		LeftCheckPoint += m_PixelCheckPoint.TopRight;
		RightCheckPoint += m_PixelCheckPoint.RightTop;
		break;
	default:
		break;
	}

	// 무조건 Left, Right 순으로 인자를 전달해야합니다.
	CheckDir = ReturnDirectionCheckBothSide(m_Dir, LeftCheckPoint, RightCheckPoint);

	// 위 함수에서 반환된 방향이 현재의 방향과 같으면 아무것도 하지 않습니다.
	if (CheckDir == m_Dir)
	{

	}
	// 만약 Center가 나왔다면 벽에 맞부딪혔다는 것으로 움직이지 않습니다.
	else if (CheckDir == EDIRECTION::CENTER)
	{
		m_MoveVector = float4::ZERO;
	}
	// 진행 방향과 다르면 벽에 비벼 올라갈 수 있습니다. 하지만 일반 속도보다 상대적으로 느리기 때문에 마찰력 영향을 받습니다.
	else
	{
		MoveDirVector = CalculateDirectionVectorToDir(CheckDir);
		m_MoveVector = MoveDirVector * _MAXMoveForce * COSNT_FrictionForce;
	}
}


EDIRECTION Ellie::ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(EDIRECTION _Dir, const float4& _MoveVector)
{
	float4 CurPos = Transform.GetWorldPosition();

	float4 LeftCheckPoint = CurPos;
	float4 RightCheckPoint = CurPos;
	float4 MoveDirVector = float4::ZERO;

	switch (_Dir)
	{
	case EDIRECTION::UP:
		LeftCheckPoint += m_PixelCheckPoint.TopLeft;
		RightCheckPoint += m_PixelCheckPoint.TopRight;
		break;
	case EDIRECTION::LEFTUP:
		LeftCheckPoint += m_PixelCheckPoint.LeftTop;
		RightCheckPoint += m_PixelCheckPoint.TopLeft;
		break;
	case EDIRECTION::LEFT:
		LeftCheckPoint += m_PixelCheckPoint.LeftBottom;
		RightCheckPoint += m_PixelCheckPoint.LeftTop;
		break;
	case EDIRECTION::LEFTDOWN:
		LeftCheckPoint += m_PixelCheckPoint.BottomLeft;
		RightCheckPoint += m_PixelCheckPoint.LeftBottom;
		break;
	case EDIRECTION::DOWN:
		LeftCheckPoint += m_PixelCheckPoint.BottomRight;
		RightCheckPoint += m_PixelCheckPoint.BottomLeft;
		break;
	case EDIRECTION::RIGHTDOWN:
		LeftCheckPoint += m_PixelCheckPoint.RightBottom;
		RightCheckPoint += m_PixelCheckPoint.BottomRight;
		break;
	case EDIRECTION::RIGHT:
		LeftCheckPoint += m_PixelCheckPoint.RightTop;
		RightCheckPoint += m_PixelCheckPoint.RightBottom;
		break;
	case EDIRECTION::RIGHTUP:
		LeftCheckPoint += m_PixelCheckPoint.TopRight;
		RightCheckPoint += m_PixelCheckPoint.RightTop;
		break;
	default:
		break;
	}

	// 무조건 Left, Right 순으로 인자를 전달해야합니다.
	return ReturnDirectionCheckBothSide(_Dir, LeftCheckPoint, RightCheckPoint);
}


// 왼쪽과 오른쪽 점을 검사해 픽셀 충돌을 검사합니다.
// 한쪽만 부딪혔다면 벽을 타고 갈 수 있으며, 양쪽과 부딪힐 시 움직일 수 없는 상태로 간주합니다
// (움직일 수는 없지만 렌더러는 움직입니다. 즉, 속도가 0으로 반환되게 할껍니다).
EDIRECTION Ellie::ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint)
{
	int DirNum = static_cast<int>(_Direction);

	bool LeftCheck = BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(_LeftCheckPoint, GameEngineColor::RED);
	bool RightCheck = BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(_RightCheckPoint, GameEngineColor::RED);

	if (true == LeftCheck && false == RightCheck)
	{
		if (8 == DirNum)
		{
			DirNum = 1;
		}
		else
		{
			++DirNum;
		}
	}

	if (false == LeftCheck && true == RightCheck)
	{
		if (1 == DirNum)
		{
			DirNum = 8;
		}
		else
		{
			--DirNum;
		}
	}

	if (true == LeftCheck && true == RightCheck)
	{
		DirNum = 0;
	}

	return static_cast<EDIRECTION>(DirNum);
}



// 가속도로 이동한다. 
// 한계치를 넘기면 속도 제한이 걸린다.
// 키가 정방향이면 속도가 가속한다.
// 키가 Center면 속도가 줄어든다.
// 키가 역방향이면 속도가 빨리 줄어든다.
float4 Ellie::ReturnPostMoveVector(float _Delta, float _MAXMoveForce, float _Acceleration_Time)
{
	float4 Dir = CalculateDirectionVectorToDir(m_Dir);

	float4 MaxSpeed = { Dir.X * _MAXMoveForce , Dir.Y * _MAXMoveForce };

	m_MoveForce.X = (MaxSpeed.X / _Acceleration_Time) * _Delta;
	m_MoveForce.Y = (MaxSpeed.Y / _Acceleration_Time) * _Delta;

	float4 MoveVector = m_MoveVector + m_MoveForce;

	return MoveVector;
}

EDIRECTION Ellie::ReturnCheckDirToMoveVector(const float4& _MoveVector)
{
	float4 MoveVector = _MoveVector;
	float4 UnitVetor = MoveVector.NormalizeReturn();
	float Degree = UnitVetor.Angle2DDeg();
	if (UnitVetor.Y < 0)
	{
		Degree = 180.0f - Degree;
		Degree += 180.0f;
	}

	float Cake16OnePieceDegree = 360.0f / 16.0f;

	if (Degree <= Cake16OnePieceDegree || Degree >= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHT;
	}

	if (Degree > Cake16OnePieceDegree * 1.0f && Degree <= Cake16OnePieceDegree * 3.0f)
	{
		return EDIRECTION::RIGHTUP;
	}

	if (Degree > Cake16OnePieceDegree * 3.0f && Degree <= Cake16OnePieceDegree * 5.0f)
	{
		return EDIRECTION::UP;
	}

	if (Degree > Cake16OnePieceDegree * 5.0f && Degree <= Cake16OnePieceDegree * 7.0f)
	{
		return EDIRECTION::LEFTUP;
	}

	if (Degree > Cake16OnePieceDegree * 7.0f && Degree <= Cake16OnePieceDegree * 9.0f)
	{
		return EDIRECTION::LEFT;
	}

	if (Degree > Cake16OnePieceDegree * 9.0f && Degree <= Cake16OnePieceDegree * 11.0f)
	{
		return EDIRECTION::LEFTDOWN;
	}

	if (Degree > Cake16OnePieceDegree * 11.0f && Degree <= Cake16OnePieceDegree * 13.0f)
	{
		return EDIRECTION::DOWN;
	}

	if (Degree > Cake16OnePieceDegree * 13.0f && Degree <= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHTDOWN;
	}

	MsgBoxAssert("잘못된 반환입니다.");
	return m_Dir;
}


// 만약 현재 속도가 과속했을 시, 최대 속도로 맞춰줍니다.
bool Ellie::IsOverSpeed(float _CurSpeed, const float _MaxMoveForce)
{
	if (_CurSpeed > 0.0f && _MaxMoveForce > 0.0f)
	{
		if (_CurSpeed > _MaxMoveForce)
		{
			return true;
		}
	}

	if (_CurSpeed < 0.0f && _MaxMoveForce < 0.0f)
	{
		if (_CurSpeed < _MaxMoveForce)
		{
			return true;
		}
	}
	
	return false;
}


void Ellie::DecelerateMoveVector(float _Delta, const float _MaxMoveForce, const float _DecelerationTime)
{
	if (0.0f != m_MoveVector.X)
	{
		if (m_MoveVector.X > 0.0f)
		{
			m_MoveVector.X -= (_MaxMoveForce / _DecelerationTime) * _Delta;
		}
		else
		{
			m_MoveVector.X += (_MaxMoveForce / _DecelerationTime) * _Delta;
		}
	}

	if (0.0f != m_MoveVector.Y)
	{
		if (m_MoveVector.Y > 0.0f)
		{
			m_MoveVector.Y -= (_MaxMoveForce / _DecelerationTime) * _Delta;
		}
		else
		{
			m_MoveVector.Y += (_MaxMoveForce / _DecelerationTime) * _Delta;
		}
	}
}


// 만약 세로, 가로키가 Center로 있다면 속도를 줄여줍니다.
void Ellie::DecelerateAtMidpoint(float _Delta, const float _MaxMoveForce, const float _DecelerationTime)
{
	if (EHORIZONTAL_KEY_STATE::Center == m_HorizontalKey)
	{
		if (0.0f != m_MoveVector.X)
		{
			if (m_MoveVector.X > 0.0f)
			{
				m_MoveVector.X -= (_MaxMoveForce / _DecelerationTime) * _Delta;
			}
			else
			{
				m_MoveVector.X += (_MaxMoveForce / _DecelerationTime) * _Delta;
			}
		}
	}

	if (EVERTICAL_KEY_STATE::Center == m_VerticalKey)
	{
		if (0.0f != m_MoveVector.Y)
		{
			if (m_MoveVector.Y > 0.0f)
			{
				m_MoveVector.Y -= (_MaxMoveForce / _DecelerationTime) * _Delta;
			}
			else
			{
				m_MoveVector.Y += (_MaxMoveForce / _DecelerationTime) * _Delta;
			}
		}
	}
}

// 최종속도를 적용하는 함수입니다.
void Ellie::ApplyMovementToTransform(float _Delta)
{
	Transform.AddLocalPosition(m_MoveVector * _Delta);
}

#pragma endregion 