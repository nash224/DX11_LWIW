#include "PreCompile.h"
#include "BaseLift.h"

#include "Ellie.h"
#include "FadeObject.h"


std::weak_ptr<BaseLift> BaseLift::MainLiftPtr;

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
}

void BaseLift::Init()
{
	LiftSetting();
	StateSetting();

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

void BaseLift::StateSetting()
{
	CreateStateParameter ReadyPara;
	ReadyPara.Start = std::bind(&BaseLift::StartReady, this, std::placeholders::_1);
	State.CreateState(ELIFTSTATE::Ready, ReadyPara);

	CreateStateParameter EnterPara;
	EnterPara.Start = std::bind(&BaseLift::StartEnter, this, std::placeholders::_1);
	EnterPara.Stay = std::bind(&BaseLift::UpdateEnter, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ELIFTSTATE::Enter, EnterPara);
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
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->Off();
	}

	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->SetLocalPosition(Transform.GetLocalPosition());
		Ellie::MainEllie->OffControl();
		Ellie::MainEllie->SetAnimationByDirection(EDIRECTION::DOWN);
	}

	LiftSpeed = 0.0f;
}

void BaseLift::StartArrive(GameEngineState* _Parent)
{
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		Ellie::MainEllie->SetLocalPosition(Transform.GetLocalPosition());
		InteractiveActor::InteractiveCol->Off();
		Ellie::MainEllie->SetAnimationByDirection(EDIRECTION::DOWN);
	}

	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OffControl();
	}

	LiftSpeed = 0.0f;
}



void BaseLift::UpdateEnter(float _Delta, GameEngineState* _Parent)
{
 	const float4& CurLiftPos = Lift.Lift->Transform.GetLocalPosition();
	const float MoveDistance = LiftArrivePoint.Y - CurLiftPos.Y;

	if (false == isChangeLevel && MoveDistance > EnterDistance)
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
	static constexpr float ArriveRange = 3.0f;
	const float4& CurLiftPos = Lift.Lift->Transform.GetLocalPosition();
	const float DistanceToArrivePoint = std::fabs(CurLiftPos.Y - LiftArrivePoint.Y);
	
	if (DistanceToArrivePoint < ArriveRange)
	{
		State.ChangeState(ELIFTSTATE::Ready);
		return;
	}

	MoveEv(_Delta, ArriveType);
}




void BaseLift::EndEnter(GameEngineState* _Parent)
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OnControl();
	}
}

void BaseLift::EndArrive(GameEngineState* _Parent)
{
	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->OnControl();
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

void BaseLift::AddSpeed(float _Delta, float _Speed)
{
	LiftSpeed += _Speed * _Delta / AccelerationTime;
	if (LiftSpeed > _Speed)
	{
		LiftSpeed = _Speed;
	}
	if (LiftSpeed < 0.0f)
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

	if (nullptr != Ellie::MainEllie)
	{
		Ellie::MainEllie->AddLocalPosition(LiftMoveVector);
	}

	Lift.Lift->Transform.AddLocalPosition(LiftMoveVector);
	Lift.Pattern->Transform.AddLocalPosition(LiftMoveVector);
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