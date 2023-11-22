#include "PreCompile.h"
#include "UpperLift.h"

#include "FadeObject.h"

#include "Ellie.h"

EUPPERLIFTSTATE UpperLift::s_State = EUPPERLIFTSTATE::Dust;
UpperLift::UpperLift()
{
}

UpperLift::~UpperLift()
{
}


void UpperLift::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 120.0f, 80.0f }, float4::ZERO, ColType::AABBBOX2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);

	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}

	InteractiveActor::InteractiveCol->Off();
}

void UpperLift::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
}

void UpperLift::Release()
{
	StaticEntity::Release();
}

void UpperLift::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void UpperLift::Init()
{
	StateSetting();
}

void UpperLift::StateSetting()
{
	CreateStateParameter DustState;
	DustState.Stay = std::bind(&UpperLift::UpdateDust, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EUPPERLIFTSTATE::Dust, DustState);

	CreateStateParameter LiftState;
	LiftState.Start = std::bind(&UpperLift::StartLift, this, std::placeholders::_1);
	LiftState.Stay = std::bind(&UpperLift::UpdateLift, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EUPPERLIFTSTATE::Lift, LiftState);

	if (s_State == EUPPERLIFTSTATE::Lift)
	{
		State.ChangeState(EUPPERLIFTSTATE::Lift);
	}
	else
	{
		State.ChangeState(EUPPERLIFTSTATE::Dust);
	}
}

void UpperLift::StartLift(GameEngineState* _Parent)
{
	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}

	InteractiveActor::InteractiveCol->On();
}

void UpperLift::UpdateDust(float _Delta, GameEngineState* _Parent)
{
	if (s_State == EUPPERLIFTSTATE::Lift)
	{
		State.ChangeState(EUPPERLIFTSTATE::Lift);
	}
}


void UpperLift::UpdateLift(float _Delta, GameEngineState* _Parent)
{
	if (true == InteractiveActor::IsEnalbeActive)
	{
		if (nullptr != InteractiveActor::InteractiveCol)
		{
			InteractiveActor::InteractiveCol->Off();
		}

		if (nullptr == Ellie::MainEllie)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
			return;
		}

		Ellie::MainEllie->OffControl();

		std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Entity);
		Fade.lock()->CallFadeOut("WitchHouse_DownFloor", 1.2f);
	}
}

void UpperLift::ActiveLift()
{
	s_State = EUPPERLIFTSTATE::Lift;
}