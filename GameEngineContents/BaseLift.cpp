#include "PreCompile.h"
#include "BaseLift.h"

#include "Ellie.h"
#include "FadeObject.h"


std::weak_ptr<BaseLift> BaseLift::MainLiftPtr;

bool BaseLift::isEnable = false;
BaseLift::BaseLift() 
{
}

BaseLift::~BaseLift() 
{
}

void BaseLift::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, float4{ 100.0f , 88.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Near, ECOLLECTION_METHOD::Lift, ETOOLTYPE::Nothing);
}

void BaseLift::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
	State.Update(_Delta);
}

void BaseLift::Release()
{
	InteractiveActor::Release();

	Lift.Lift = nullptr;
	Lift.Pattern = nullptr;
}

void BaseLift::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();

	FileLoadFunction::ReleaseAllTextureAndSpriteInPath("Resources\\PlayContents\\Lift");
}

void BaseLift::Init()
{
	FileLoadFunction::LoadTextureAndCreateSingleSpriteInPath("Resources\\PlayContents\\Lift");

	LiftSetting();
	StateSetting();

	LiftArrivePoint = Transform.GetLocalPosition();

	if (false == isEnable)
	{
		if (nullptr != InteractiveActor::InteractiveCol)
		{
			InteractiveActor::InteractiveCol->Off();
		}
	}

	MainLiftPtr = GetDynamic_Cast_This<BaseLift>();
}

void BaseLift::LiftSetting()
{
	const float LiftDepth = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Lift);
	const float PatternDepth = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::LiftPattern);

	Lift.Lift = CreateComponent<GameEngineSpriteRenderer>();
	Lift.Lift->Transform.SetLocalPosition(float4(0.0f, 0.0f, LiftDepth));
	Lift.Lift->SetSprite("Ev_Enter_2.png");
	Lift.Lift->Off();

	Lift.Pattern = CreateComponent<GameEngineSpriteRenderer>();
	Lift.Pattern->Transform.SetLocalPosition(float4(1.0f, 4.0f, PatternDepth));
	Lift.Pattern->SetSprite("Ev_Enter_1.png");
	Lift.Pattern->Off();
}


void BaseLift::EnableEv()
{
	isEnable = true;
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->On();
	}
}

void BaseLift::ActiveEv()
{
	State.ChangeState(ELIFTSTATE::Enter);
}

void BaseLift::LiftToArrive()
{
	State.ChangeState(ELIFTSTATE::Arrive);
}


void BaseLift::StateSetting()
{
	CreateStateParameter ReadyPara;
	ReadyPara.Start = std::bind(&BaseLift::StartReady, this, std::placeholders::_1);
	State.CreateState(ELIFTSTATE::Ready, ReadyPara);

	CreateStateParameter EnterPara;
	EnterPara.Start = std::bind(&BaseLift::StartEnter, this, std::placeholders::_1);
	EnterPara.Stay = std::bind(&BaseLift::UpdateEnter, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ELIFTSTATE::Enter, EnterPara);

	CreateStateParameter ArrivePara;
	ArrivePara.Start = std::bind(&BaseLift::StartArrive, this, std::placeholders::_1);
	ArrivePara.Stay = std::bind(&BaseLift::UpdateArrive, this, std::placeholders::_1, std::placeholders::_2);
	ArrivePara.End = std::bind(&BaseLift::EndArrive, this, std::placeholders::_1);
	State.CreateState(ELIFTSTATE::Arrive, ArrivePara);
}

void BaseLift::StartReady(GameEngineState* _Parent)
{
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->On();
	}
}

void BaseLift::StartEnter(GameEngineState* _Parent)
{
	GameEngineInput::IsOnlyInputObject(this);

	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->Off();
	}

	const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr();
	PlayerPtr->SetLocalPosition(Transform.GetLocalPosition());
	PlayerPtr->OffControl();
	PlayerPtr->SetAnimationByDirection(EDIRECTION::DOWN);
	

	LiftSpeed = 0.0f;
}

void BaseLift::StartArrive(GameEngineState* _Parent)
{
	GameEngineInput::IsOnlyInputObject(this);
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->Off();
	}
}



void BaseLift::UpdateEnter(float _Delta, GameEngineState* _Parent)
{
	const float MoveDistance = std::fabs(LiftArrivePoint.Y - Transform.GetLocalPosition().Y);

	if (false == isChangeLevel && EnterDistance < MoveDistance)
	{
		std::shared_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeOut(ChangeLevelName, 1.0f);
		isChangeLevel = true;
	}

	AddSpeed(_Delta, MaxSpeed);
	MoveEv(_Delta, EnterType);
}

void BaseLift::UpdateArrive(float _Delta, GameEngineState* _Parent)
{
	if (false == isArriveInit)
	{
		const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr();
		PlayerPtr->SetAnimationByDirection(EDIRECTION::DOWN);
		PlayerPtr->OffControl();

		LiftSpeed = MaxSpeed;
		SetEv(EnterType);

		isArriveInit = true;
	}

	const float DistanceToArrivePoint = std::fabs(Transform.GetLocalPosition().Y - LiftArrivePoint.Y);
	if (DistanceToArrivePoint < 12.0f)
	{
		AddSpeed(_Delta, -MaxSpeed);
	}

	if (LiftSpeed == 0.0f)
	{
		State.ChangeState(ELIFTSTATE::Ready);
		return;
	}

	MoveEv(_Delta, ArriveType);
}

void BaseLift::EndEnter(GameEngineState* _Parent)
{
	GameEngineInput::IsObjectAllInputOn();
	PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->OnControl();
}

void BaseLift::EndArrive(GameEngineState* _Parent)
{
	GameEngineInput::IsObjectAllInputOn();
	const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr();
	PlayerPtr->OnControl();
	PlayerPtr->SetLocalPosition(LiftArrivePoint);
}

void BaseLift::AddSpeed(float _Delta, float _Speed)
{
	LiftSpeed += _Speed * _Delta / AccelerationTime;
	if (_Speed > 0.0f && LiftSpeed > _Speed)
	{
		LiftSpeed = _Speed;
	}
	if (_Speed < 0.0f && LiftSpeed < 0.0f)
	{
		LiftSpeed = 0.0f;
	}
}

void BaseLift::MoveEv(float _Delta, ELIFTDIR _LiftType)
{
	float4 LiftMoveVector;
	if (ELIFTDIR::Up == _LiftType)
	{
		LiftMoveVector = float4::UP;
	}
	else if (ELIFTDIR::Down == _LiftType)
	{
		LiftMoveVector = float4::DOWN;
	}

	LiftMoveVector *= LiftSpeed * _Delta;

	PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->AddLocalPosition(LiftMoveVector);
	Transform.AddLocalPosition(LiftMoveVector);
}

void BaseLift::SetEv(ELIFTDIR _LiftType)
{
	float4 LiftMoveVector;
	if (ELIFTDIR::Up == _LiftType)
	{
		LiftMoveVector = float4::UP;
	}
	else if (ELIFTDIR::Down == _LiftType)
	{
		LiftMoveVector = float4::DOWN;
	}

	LiftMoveVector *= ArriveStartDistance;
	LiftMoveVector = Transform.GetLocalPosition() + LiftMoveVector;

	PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->SetLocalPosition(LiftMoveVector);
	

	Transform.SetLocalPosition(LiftMoveVector);
}

void BaseLift::AppearLift()
{
	if (nullptr == Lift.Lift
		|| nullptr == Lift.Pattern)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Lift.Lift->On();
	Lift.Pattern->On();
}

void BaseLift::DisappearLift()
{
	if (nullptr == Lift.Lift
		|| nullptr == Lift.Pattern)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	Lift.Lift->Off();
	Lift.Pattern->Off();
}