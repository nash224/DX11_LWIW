#include "PreCompile.h"
#include "Ellie.h"

#include "PlayLevel.h"
#include "TimeManager.h"
#include "UIManager.h"

#include "BackDrop_PlayLevel.h"



Ellie* Ellie::MainEllie = nullptr;
EELLIE_STATUS Ellie::g_Status = EELLIE_STATUS::None;
float Ellie::Stamina = 0.0f;
float Ellie::BroomFuel = MAX_FUEL;
int Ellie::Day = -1;
bool Ellie::FirstInitCheck = false;
Ellie::Ellie() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_Broomstick_Boosting_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Ellie\\Broom");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("SFX_PenCompleteMelody.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Ellie\\Pen");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}

	if (false == FirstInitCheck)
	{
		g_Status = EELLIE_STATUS::Normal;
		FirstInitCheck = true;
	}

	SetPixelPointBaseOnCenter();

	CheckDayChange();
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
	UpdateCoolTime(_Delta);
	UpdateCollision();
	UpdateTestCode();
}

void Ellie::UpdateTestCode()
{

}


void Ellie::Release()
{
	DynamicEntity::Release();

	ShadowRenderer = nullptr;
	VirgilRenderer = nullptr;
	EllieFxRenderer = nullptr;

	EllieCol = nullptr;
	InteractiveCol = nullptr;
	NetCollision = nullptr;

	OtherEntity = nullptr;

	Broom.BroomRenderer.clear();
}

void Ellie::LevelStart(class GameEngineLevel* _NextLevel)
{
 	OnLevelStart();
	CheckDayChange();
}

void Ellie::LevelEnd(class GameEngineLevel* _NextLevel)
{
	IsControl = true;
}


void Ellie::CollisionSetting()
{
	EllieCol = CreateComponent<GameEngineCollision>(ECOLLISION::Player);
	EllieCol->Transform.SetLocalScale(float4{ 4.0f , 4.0f });
	EllieCol->SetCollisionType(ColType::AABBBOX2D);

	NetCollision = CreateComponent<GameEngineCollision>(ECOLLISION::Net);
	NetCollision->Transform.SetLocalScale(float4(140.0f, 4.0f));
	NetCollision->SetCollisionType(ColType::SPHERE2D);
	NetCollision->Off();
}


void Ellie::Init()
{

}

void Ellie::SetLocalPosition(const float4& _Pos)
{
	Transform.SetLocalPosition(_Pos);
	ApplyDepth();
}

void Ellie::AddLocalPosition(const float4& _Pos)
{
	Transform.AddLocalPosition(_Pos);
	ApplyDepth();
}

void Ellie::OnLevelStart()
{
	RenewStatus();
	ResetMoveVector();
	ApplyDepth();
	MainEllie = this;
	OnControl();
}

void Ellie::RenewStatus()
{
	if (EELLIE_STATUS::Normal == g_Status && EELLIE_STATE::Idle != State)
	{
  		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	if (EELLIE_STATUS::Riding == g_Status && EELLIE_STATE::Riding_Standing != State)
	{
		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}

	if (EELLIE_STATE::None == State)
	{
		MsgBoxAssert("등록되지 않은 행동패턴입니다.");
		return;
	}
}

void Ellie::ChangeStatus(const EELLIE_STATUS _Status)
{
	g_Status = _Status;
}

void Ellie::OnControl()
{
	GameEngineInput::InputObjectOn(this);
	if (nullptr != EllieCol)
	{
		EllieCol->On();
	}
}

void Ellie::OffControl()
{
	GameEngineInput::InputObjectOff(this);
	if (nullptr != EllieCol)
	{
		EllieCol->Off();
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

void Ellie::SetAnimationByDirection(EDIRECTION _Dir /*= EDIRECTION::CENTER*/)
{
	if (EDIRECTION::CENTER != _Dir)
	{
		Dir = _Dir;

		if (EELLIE_STATUS::Normal == g_Status)
		{
			RenewStatus();
			ChangeDirectionAnimation("Idle");
		}

		if (EELLIE_STATUS::Riding== g_Status)
		{
			RenewStatus();
			ChangeDirectionAnimation("Riding_Standing");
		}
	}
}


void Ellie::SetPixelPointBaseOnCenter()
{
	static constexpr const float CheckPointGap = 2.0f;

	const float4& CheckPosBaseOnCenter = float4::ZERO;

	const float4& CheckScale = { 10.0f , 10.0f };
	const float4& HalfCheckScale = CheckScale.Half();

	CheckPoint.TopLeft = CheckPosBaseOnCenter + float4{ -HalfCheckScale.X + CheckPointGap , HalfCheckScale.Y };
	CheckPoint.TopRight = CheckPosBaseOnCenter + float4{ HalfCheckScale.X - CheckPointGap , HalfCheckScale.Y };
	CheckPoint.LeftTop = CheckPosBaseOnCenter + float4{ -HalfCheckScale.X , HalfCheckScale.Y - CheckPointGap };
	CheckPoint.LeftBottom = CheckPosBaseOnCenter + float4{ -HalfCheckScale.X , -HalfCheckScale.Y + CheckPointGap };
	CheckPoint.RightTop = CheckPosBaseOnCenter + float4{ HalfCheckScale.X , HalfCheckScale.Y - CheckPointGap };
	CheckPoint.RightBottom = CheckPosBaseOnCenter + float4{ HalfCheckScale.X , -HalfCheckScale.Y + CheckPointGap };
	CheckPoint.BottomLeft = CheckPosBaseOnCenter + float4{ -HalfCheckScale.X + CheckPointGap , -HalfCheckScale.Y };
	CheckPoint.BottomRight = CheckPosBaseOnCenter + float4{ HalfCheckScale.X - CheckPointGap , -HalfCheckScale.Y };
}


/////////////////////////////////////////////////////////////////////////////////////

#pragma region State 함수
void Ellie::UpdateState(float _Delta)
{
	switch (State)
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
	case EELLIE_STATE::Lift:									UpdateLift(_Delta);							break;
	case EELLIE_STATE::Cheer:									UpdateCheer(_Delta);						break;
	case EELLIE_STATE::Fail:									UpdateFail(_Delta);							break;
	case EELLIE_STATE::Drink:									UpdateDrink(_Delta);						break;
	default:
		break;
	}
}

void Ellie::UpdateCoolTime(float _Delta)
{
	if (CoolTime > 0.0f)
	{
		CoolTime -= _Delta;
		if (CoolTime < 0.0f)
		{
			CoolTime = 0.0f;
		}
	}
}

void Ellie::ChangeState(EELLIE_STATE _State)
{
	if (_State != State)
	{
		switch (State)
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

		if (nullptr != VirgilRenderer)
		{
			VirgilRenderer->Off();
		}

		if (true == Broom.BroomRenderer.empty())
		{
			MsgBoxAssert("빗자루 렌더러가 존재하지 않습니다.");
			return;
		}

		for (std::weak_ptr<GameEngineSpriteRenderer> BroomRenderer : Broom.BroomRenderer)
		{
			BroomRenderer.lock()->Off();
		}


		State = _State;

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
		case EELLIE_STATE::Lift:								StartLift();						break;
		case EELLIE_STATE::Cheer:								StartCheer();						break;
		case EELLIE_STATE::Fail:								StartFail();						break;
		case EELLIE_STATE::Drink:								StartDrink();						break;
		default:
			break;
		}
	}
}


void Ellie::ChangeAnimationByDirection(std::string_view _StateName, bool _DirectionInfluence /*= true*/, bool _Force /*= false*/, unsigned int _Index /*= 0*/)
{
	std::string AnimaitonName = "Ellie_Basic_";
	AnimaitonName += _StateName.data();

	ChangeShawdowSprite(AnimaitonName);
	ChangeVirgilSprite(AnimaitonName);

	if (g_Status == EELLIE_STATUS::Riding)
	{
		ChangeBroomSprite();
	}


	if (true == _DirectionInfluence)
	{
		switch (Dir)
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

	RenderDir = Dir;

	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다."); 
		return;
	}

	BodyRenderer->ChangeAnimation(AnimaitonName, _Force, _Index);
}

void Ellie::ChangeShawdowSprite(std::string_view _AnimationName)
{
	if (nullptr == ShadowRenderer)
	{
		MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
		return;
	}

	std::string ShadowSpriteName = _AnimationName.data() + std::string(".png");

	static constexpr const int OnlySpriteUse = 0;

	switch (State)
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
	case EELLIE_STATE::ButterflyNet:
		ShadowRenderer->SetSprite(ShadowSpriteName, 1);
		break;
	case EELLIE_STATE::RootUp:
		ShadowRenderer->SetSprite(ShadowSpriteName, 7);
		break;
	case EELLIE_STATE::Sit:
	case EELLIE_STATE::Fail:
	case EELLIE_STATE::Cheer:
		ShadowRenderer->SetSprite(ShadowSpriteName, OnlySpriteUse);
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
	if (nullptr == VirgilRenderer)
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

	switch (State)
	{
	case EELLIE_STATE::Idle:
	case EELLIE_STATE::SlowWalk:
	case EELLIE_STATE::Walk:
	case EELLIE_STATE::Run:
	case EELLIE_STATE::ButterflyNet:
	case EELLIE_STATE::RootUp:
	case EELLIE_STATE::Sit:
	case EELLIE_STATE::Throw:
	case EELLIE_STATE::Riding_Boosting:
	case EELLIE_STATE::Riding_Standing:
	case EELLIE_STATE::Riding_Moving:
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
		VirgilRenderer->SetSprite(ShadowSpriteName);
		VirgilRenderer->On();
	}
}

void Ellie::ChangeBroomSprite()
{
	if (nullptr == GameEngineSprite::Find("Broomstick_Basic_Boosting.png"))
	{
		GameEngineSprite::CreateCut("Broomstick_Basic_Boosting.png", 6, 6);
		GameEngineSprite::CreateCut("Broomstick_Basic_Moving.png", 6, 6);
		GameEngineSprite::CreateCut("Broomstick_Basic_Standing.png", 6, 6);
	}

	if (true == Broom.BroomRenderer.empty())
	{
		MsgBoxAssert("빗자루 렌더러가 존재하지 않습니다.");
		return;
	}

	std::string BroomSpriteName = "Broomstick_Basic_";

	switch (State)
	{
	case EELLIE_STATE::Riding_Standing:
		BroomSpriteName += "Boosting.png";
		break;
	case EELLIE_STATE::Riding_Moving:
		BroomSpriteName += "Moving.png";
		break;
	case EELLIE_STATE::Riding_Boosting:
		BroomSpriteName += "Boosting.png";
		break;
	default:
		break;
	}

	for (std::weak_ptr<GameEngineSpriteRenderer> BroomRenderer : Broom.BroomRenderer)
	{
		if (true == BroomRenderer.expired())
		{
			MsgBoxAssert("빗자루 렌더러가 존재하지 않습니다.");
			return;
		}

		BroomRenderer.lock()->SetSprite(BroomSpriteName);
		BroomRenderer.lock()->On();
	}
}

void Ellie::ChangeDirectionAnimation(std::string_view _StateName)
{
	if (Dir != RenderDir)
	{
		if (nullptr == BodyRenderer)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = BodyRenderer->GetCurIndex();
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
		if (EHORIZONTAL_KEY_STATE::Center == HorizontalInputKey)
		{
			if (EVERTICAL_KEY_STATE::Down == VerticalInputKey )
			{
				Dir = EDIRECTION::DOWN;
			}
			else
			{
				Dir = EDIRECTION::UP;
			}
		}
		else if (EHORIZONTAL_KEY_STATE::Left == HorizontalInputKey)
		{
			if (EVERTICAL_KEY_STATE::Down == VerticalInputKey )
			{
				Dir = EDIRECTION::LEFTDOWN;
			}
			else if (EVERTICAL_KEY_STATE::Up == VerticalInputKey )
			{
				Dir = EDIRECTION::LEFTUP;
			}
			else
			{
				Dir = EDIRECTION::LEFT;
			}
		}
		else
		{
			if (EVERTICAL_KEY_STATE::Down == VerticalInputKey )
			{
				Dir = EDIRECTION::RIGHTDOWN;
			}
			else if (EVERTICAL_KEY_STATE::Up == VerticalInputKey )
			{
				Dir = EDIRECTION::RIGHTUP;
			}
			else
			{
				Dir = EDIRECTION::RIGHT;
			}
		}

		return true;
	}
	
	return false;
}


bool Ellie::DetectVerticalMovement()
{
	VerticalInputKey  = EVERTICAL_KEY_STATE::Center;

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
			VerticalInputKey  = EVERTICAL_KEY_STATE::Up;
		}

		if (true == isPressDown)
		{
			VerticalInputKey  = EVERTICAL_KEY_STATE::Down;
		}
	}

	return isMoveVertical;
}


bool Ellie::DetectHorizontalMovement()
{
	HorizontalInputKey = EHORIZONTAL_KEY_STATE::Center;

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
			HorizontalInputKey = EHORIZONTAL_KEY_STATE::Left;
		}

		if (true == isPressRight)
		{
			HorizontalInputKey = EHORIZONTAL_KEY_STATE::Right;
		}
	}

	return isMoveHorizontal;
}

#pragma endregion 


#pragma region 이동 및 방향 

float4 Ellie::GetDirectionVectorToDir(const EDIRECTION _Direction)
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

void Ellie::CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce)
{
	const float4& DirVector = GetDirectionVectorToDir(Dir);

	SetMoveVector(DirVector * _MAXMoveForce);
	
	const float4& CurPos = Transform.GetWorldPosition();

	float4 LeftCheckPoint = CurPos;
	float4 RightCheckPoint = CurPos;
	float4 MoveDirVector = float4::ZERO;
	EDIRECTION CheckDir = EDIRECTION::CENTER;


	switch (Dir)
	{
	case EDIRECTION::UP:
		LeftCheckPoint += CheckPoint.TopLeft;
		RightCheckPoint += CheckPoint.TopRight;
		break;
	case EDIRECTION::LEFTUP:
		LeftCheckPoint += CheckPoint.LeftTop;
		RightCheckPoint += CheckPoint.TopLeft;
		break;
	case EDIRECTION::LEFT:
		LeftCheckPoint += CheckPoint.LeftBottom;
		RightCheckPoint += CheckPoint.LeftTop;
		break;
	case EDIRECTION::LEFTDOWN:
		LeftCheckPoint += CheckPoint.BottomLeft;
		RightCheckPoint += CheckPoint.LeftBottom;
		break;
	case EDIRECTION::DOWN:
		LeftCheckPoint += CheckPoint.BottomRight;
		RightCheckPoint += CheckPoint.BottomRight;
		break;
	case EDIRECTION::RIGHTDOWN:
		LeftCheckPoint += CheckPoint.RightBottom;
		RightCheckPoint += CheckPoint.BottomRight;
		break;
	case EDIRECTION::RIGHT:
		LeftCheckPoint += CheckPoint.RightTop;
		RightCheckPoint += CheckPoint.RightBottom;
		break;
	case EDIRECTION::RIGHTUP:
		LeftCheckPoint += CheckPoint.TopRight;
		RightCheckPoint += CheckPoint.RightTop;
		break;
	default:
		break;
	}

	CheckDir = ReturnDirectionCheckBothSide(Dir, LeftCheckPoint, RightCheckPoint);

	if (CheckDir != Dir)
	{
		if (CheckDir == EDIRECTION::CENTER)
		{
			ResetMoveVector();
		}
		else
		{
			MoveDirVector = GetDirectionVectorToDir(CheckDir);
			SetMoveVector(MoveDirVector * _MAXMoveForce * FrictionForce);
		}
	}
}


EDIRECTION Ellie::ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint)
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		return Dir;
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

float4 Ellie::GetMoveForceByDir(float _Delta, float _MAXMoveForce, float _Acceleration_Time)
{
	const float4& DirVector = GetDirectionVectorToDir(Dir);

	const float4& MaxForce = { DirVector.X * _MAXMoveForce / _Acceleration_Time, DirVector.Y * _MAXMoveForce / _Acceleration_Time };

	float4 ResultVector;
	ResultVector.X = MaxForce.X * _Delta;
	ResultVector.Y = MaxForce.Y * _Delta;
	return ResultVector;
}

void Ellie::LimitMoveVector(float _MAXMoveForce)
{
	const float4& MoveVectorSize = DirectX::XMVector2Length(DynamicEntity::GetMoveVector().DirectXVector);
	const float4& MoveUnitVector = DirectX::XMVector2Normalize(DynamicEntity::GetMoveVector().DirectXVector);
 	const float LimitedSpeed = std::clamp(MoveVectorSize.X, 0.0f, _MAXMoveForce);

	DynamicEntity::SetMoveVector(MoveUnitVector * LimitedSpeed);
}

#pragma endregion 

void Ellie::CheckDayChange()
{
	if (nullptr != PlayLevel::s_TimeManager)
	{
		if (Day != PlayLevel::s_TimeManager->GetDayCount())
		{
			Day = PlayLevel::s_TimeManager->GetDayCount();
			DayChangeEvent();
		}
	}
}

void Ellie::DayChangeEvent()
{
	Stamina = MAX_STAMINA;
}