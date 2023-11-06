#include "PreCompile.h"
#include "Ellie.h"


#include "PortalObject.h"
#include "BackDrop_PlayLevel.h"

Ellie* Ellie::MainEllie = nullptr;
EELLIE_STATUS Ellie::g_Status = EELLIE_STATUS::None;
bool Ellie::FirstInitCheck = false;
Ellie::Ellie() 
{
}

Ellie::~Ellie() 
{
}

void Ellie::Start()
{
	GameEngineInput::AddInputObject(this);
	RendererSetting();
	CollisionSetting();
}

void Ellie::Update(float _Delta)
{
	UpdateState(_Delta);
	UpdateTestCode();
	UpdateCollision();
}

void Ellie::UpdateTestCode()
{
	//if (true == GameEngineInput::IsDown('2', this))
	//{
	//	ChangeState(EELLIE_STATE::Fail);
	//	return;
	//}
	//if (true == GameEngineInput::IsDown('3', this))
	//{
	//	ChangeState(EELLIE_STATE::Cheer);
	//	return;
	//}

	if (true == GameEngineInput::IsDown('1', this))
	{
		BackDrop_PlayLevel::MainBackDrop->CreateItem("Mongsiri_Collect", Transform.GetLocalPosition());
	}
}


void Ellie::Release()
{
	DynamicEntity::Release();

	Shadow = nullptr;
	Virgil = nullptr;
	EllieFx = nullptr;

	m_EllieCol = nullptr;
	m_InteractiveCol = nullptr;
	m_NetCol = nullptr;

	OtherEntity = nullptr;
}


// Ellie는 PlayLevel에서 Off할 수 있지만, Off한 채로 LevelStart 할 수는 없습니다.
void Ellie::LevelStart(class GameEngineLevel* _NextLevel)
{
	OnLevelStart();
}

void Ellie::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Ellie::CollisionSetting()
{
	m_EllieCol = CreateComponent<GameEngineCollision>(ECOLLISION::Player);
	m_EllieCol->Transform.SetLocalScale(float4{ 4.0f , 4.0f });
	m_EllieCol->SetCollisionType(ColType::AABBBOX2D);

	m_NetCol = CreateComponent<GameEngineCollision>(ECOLLISION::Net);
	m_NetCol->Transform.SetLocalScale(float4(140.0f, 4.0f));
	m_NetCol->SetCollisionType(ColType::SPHERE2D);
	m_NetCol->Off();
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

	OnLevelStart();
}


// 생성되거나 레벨이 바뀔때 호출되고 앨리의 상태를 초기화합니다.
void Ellie::OnLevelStart()
{
	RenewStatus();
	ApplyDepth(Transform.GetLocalPosition());
	MainEllie = this;
}

void Ellie::RenewStatus()
{
	if (EELLIE_STATUS::Normal == g_Status && EELLIE_STATE::Idle != m_State)
	{
  		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	if (EELLIE_STATUS::Riding == g_Status && EELLIE_STATE::Riding_Standing != m_State)
	{
		ChangeState(EELLIE_STATE::Riding_Standing);
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

	if (EELLIE_STATE::None == m_WaitState)
	{
		RenewStatus();
	}
}

void Ellie::FinishWork()
{
	isFinishWork = true;
}

void Ellie::WaitDone(EELLIE_STATE _State)
{
	ChangeState(_State);
	IsWaitDone = true;
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
	case EELLIE_STATE::Riding_Standing:							UpdateRiding_Standing(_Delta);				break;
	case EELLIE_STATE::Riding_Moving:							UpdateRiding_Moving(_Delta);				break;
	case EELLIE_STATE::Riding_Boosting:							UpdateRiding_Boosting(_Delta);				break;
	case EELLIE_STATE::Approach:								UpdateApproach(_Delta);						break;
	case EELLIE_STATE::ButterflyNet:							UpdateButterflyNet(_Delta);					break;
	case EELLIE_STATE::RootUp:									UpdateRootUp(_Delta);						break;
	case EELLIE_STATE::Sit:										UpdateSit(_Delta);							break;
	case EELLIE_STATE::MongSiri:								UpdateMongSiri(_Delta);						break;
	case EELLIE_STATE::Wait:									UpdateWait(_Delta);							break;
	case EELLIE_STATE::Juicy:									UpdateJuicy(_Delta);						break;
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
		switch (m_State)
		{
		case EELLIE_STATE::None:																	break;
		case EELLIE_STATE::Idle:									EndIdle();						break;
		case EELLIE_STATE::SlowWalk:																break;
		case EELLIE_STATE::Walk:																	break;
		case EELLIE_STATE::Run:																		break;
		case EELLIE_STATE::Throw:																	break;
		case EELLIE_STATE::Riding_Standing:															break;
		case EELLIE_STATE::Riding_Moving:															break;
		case EELLIE_STATE::Riding_Boosting:															break;
		case EELLIE_STATE::Approach:								EndApproach();					break;
		case EELLIE_STATE::ButterflyNet:							EndButterflyNet();				break;
		case EELLIE_STATE::RootUp:									EndRootUp();					break;
		case EELLIE_STATE::Sit:										EndSit();						break;
		case EELLIE_STATE::MongSiri:								EndRootUp();					break;
		case EELLIE_STATE::Wait:									EndWait();						break;
		case EELLIE_STATE::Juicy:									EndJuicy();						break;
		case EELLIE_STATE::Cheer:																	break;
		case EELLIE_STATE::Fail:																	break;
		case EELLIE_STATE::Drink:																	break;
		default:
			break;
		}

		if (nullptr != Virgil)
		{
			Virgil->Off();
		}

		m_State = _State;

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
		case EELLIE_STATE::Riding_Standing:						StartRiding_Standing();				break;
		case EELLIE_STATE::Riding_Moving:						StartRiding_Moving();				break;
		case EELLIE_STATE::Riding_Boosting:						StartRiding_Boosting();				break;
		case EELLIE_STATE::Approach:							StartApproach();					break;
		case EELLIE_STATE::ButterflyNet:						StartButterflyNet();				break;
		case EELLIE_STATE::RootUp:								StartRootUp();						break;
		case EELLIE_STATE::Sit:									StartSit();							break;
		case EELLIE_STATE::MongSiri:							StartMongSiri();					break;
		case EELLIE_STATE::Wait:								StartWait();						break;
		case EELLIE_STATE::Juicy:								StartJuicy();						break;
		case EELLIE_STATE::Cheer:								StartCheer();						break;
		case EELLIE_STATE::Fail:								StartFail();						break;
		case EELLIE_STATE::Drink:								StartDrink();						break;
		default:
			break;
		}
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
	std::string AnimaitonName = "Ellie_Basic_";
	AnimaitonName += _StateName.data();

	ChangeShawdowSprite(AnimaitonName);
	ChangeVirgilSprite(AnimaitonName);

	if (true == _DirectionInfluence)
	{
		switch (m_Dir)
		{
		case EDIRECTION::UP:
			AnimaitonName += "_UP";
			break;
		case EDIRECTION::LEFTUP:
			AnimaitonName += "_LEFTUP";
			break;
		case EDIRECTION::LEFT:
			AnimaitonName += "_LEFT";
			break;
		case EDIRECTION::LEFTDOWN:
			AnimaitonName += "_LEFTDOWN";
			break;
		case EDIRECTION::DOWN:
			AnimaitonName += "_DOWN";
			break;
		case EDIRECTION::RIGHTDOWN:
			AnimaitonName += "_RIGHTDOWN";
			break;
		case EDIRECTION::RIGHT:
			AnimaitonName += "_RIGHT";
			break;
		case EDIRECTION::RIGHTUP:
			AnimaitonName += "_RIGHTUP";
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

	m_Body->ChangeAnimation(AnimaitonName, _Force, _Index);
}

void Ellie::ChangeShawdowSprite(std::string_view _AnimationName)
{
	if (nullptr == Shadow)
	{
		MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
		return;
	}

	std::string ShadowSpriteName = _AnimationName.data() + std::string(".png");

	static constexpr const int OnlySpriteUse = 0;

	switch (m_State)
	{
	case EELLIE_STATE::Idle:
	case EELLIE_STATE::Walk:
	case EELLIE_STATE::Run:
	case EELLIE_STATE::Throw:
	case EELLIE_STATE::Riding_Standing:
	case EELLIE_STATE::Riding_Moving:
	case EELLIE_STATE::Riding_Boosting:
	case EELLIE_STATE::Approach:
	case EELLIE_STATE::Wait:
	case EELLIE_STATE::MongSiri:
	case EELLIE_STATE::Drink:
		Shadow->SetSprite(ShadowSpriteName, 1);
		break;
	case EELLIE_STATE::RootUp:
		Shadow->SetSprite(ShadowSpriteName, 7);
		break;
	case EELLIE_STATE::ButterflyNet:
		Shadow->SetSprite(ShadowSpriteName, 1);
		break;
	case EELLIE_STATE::Sit:
	case EELLIE_STATE::Fail:
	case EELLIE_STATE::Cheer:
		Shadow->SetSprite(ShadowSpriteName, OnlySpriteUse);
		break;
	case EELLIE_STATE::SlowWalk:
	case EELLIE_STATE::Juicy:
		break;
	default:
		break;
	}
}

void Ellie::ChangeVirgilSprite(std::string_view _AnimationName)
{
	if (nullptr == Virgil)
	{
		MsgBoxAssert("버질 렌더러가 존재하지 않습니다.");
		return;
	}

	std::string ShadowSpriteName = _AnimationName.data() + std::string(".png");
	if ("Ellie_Basic_SlowWalk.png" == ShadowSpriteName)
	{
		ShadowSpriteName = "Ellie_Basic_Walk.png";
	}

	bool isNeedVirgil = true;

	switch (m_State)
	{
	case EELLIE_STATE::Idle:
	case EELLIE_STATE::SlowWalk:
	case EELLIE_STATE::Walk:
	case EELLIE_STATE::Run:
	case EELLIE_STATE::ButterflyNet:
	case EELLIE_STATE::RootUp:
	case EELLIE_STATE::Sit:
	case EELLIE_STATE::Throw:
		break;
	case EELLIE_STATE::Riding_Standing:
		isNeedVirgil = false;
		break;
	case EELLIE_STATE::Riding_Moving:
		isNeedVirgil = false;
		break;
	case EELLIE_STATE::Riding_Boosting:
		isNeedVirgil = false;
		break;
	case EELLIE_STATE::Approach:
	case EELLIE_STATE::MongSiri:
	case EELLIE_STATE::Wait:
	case EELLIE_STATE::Cheer:
	case EELLIE_STATE::Fail:
		break;
	case EELLIE_STATE::Juicy:
		isNeedVirgil = false;
		break;
	case EELLIE_STATE::Drink:
		isNeedVirgil = false;
		break;
	default:
		break;
	}

	if (true == isNeedVirgil)
	{
		Virgil->SetSprite(ShadowSpriteName);
		Virgil->On();
	}
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

	if (true == GameEngineInput::IsPress(VK_UP, this))
	{
		isPressUp = true;
		isMoveVertical = true;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN, this))
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

	if (true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		isPressLeft = true;
		isMoveHorizontal = true;
	}

	if (true == GameEngineInput::IsPress(VK_RIGHT, this))
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
		m_MoveVector = MoveDirVector * _MAXMoveForce * FrictionForce;
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
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		return m_Dir;
	}

	int DirNum = static_cast<int>(_Direction);

	bool LeftCheck = BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(_LeftCheckPoint, GameEngineColor::RED);
	bool RightCheck = BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(_RightCheckPoint, GameEngineColor::RED);

	bool isLeftWall = (true == LeftCheck && false == RightCheck);
	if (isLeftWall)
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

	bool isRightWall = (false == LeftCheck && true == RightCheck);
	if (isRightWall)
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

	bool isFrontWall = (true == LeftCheck && true == RightCheck);
	if (isFrontWall)
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