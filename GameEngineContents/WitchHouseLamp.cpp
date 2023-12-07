#include "PreCompile.h"
#include "WitchHouseLamp.h"

#include "TimeManager.h"

WitchHouseLamp::WitchHouseLamp() 
{
}

WitchHouseLamp::~WitchHouseLamp() 
{
}


void WitchHouseLamp::Start()
{
	Init();

	SetColor(float4(0.82f, 0.7f, 0.07f, 1.0f));
	SetAlphaCorrection(0.2f);
	SetInner(0.1f);
	SetOutter(0.99f);
	Transform.SetLocalScale(float4(0.6f, 0.6f, 1.0f));

	CreateStateParameter DayState;
	DayState.Start = std::bind(&WitchHouseLamp::StartDay, this, std::placeholders::_1);
	DayState.Stay = std::bind(&WitchHouseLamp::UpdateDay, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EWH_LAMPSATE::Day, DayState);

	CreateStateParameter ChangeState;
	ChangeState.Stay = std::bind(&WitchHouseLamp::UpdateChange, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EWH_LAMPSATE::Change, ChangeState);

	CreateStateParameter NightState;
	NightState.Start = std::bind(&WitchHouseLamp::StartNight, this, std::placeholders::_1);
	State.CreateState(EWH_LAMPSATE::Night, NightState);

	NightStartTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime(18, 40);
	const float CurTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime();
	if (CurTime > NightStartTime)
	{
		State.ChangeState(EWH_LAMPSATE::Night);
	}
	else
	{
		State.ChangeState(EWH_LAMPSATE::Day);
	}
}

void WitchHouseLamp::Update(float _Delta)
{
	State.Update(_Delta);
}

void WitchHouseLamp::Release()
{
	ALightActor::Release();
}

void WitchHouseLamp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void WitchHouseLamp::StartDay(GameEngineState* _Parent)
{
	SetAlpha(0.0f);
}

void WitchHouseLamp::StartNight(GameEngineState* _Parent)
{
	SetAlpha(1.0f);
}


void WitchHouseLamp::UpdateDay(float _Delta, GameEngineState* _Parent)
{
	const float CurTime = PlayLevel::GetCurLevel()->GetTimeManager()->GetTime();
	if (CurTime > NightStartTime)
	{
		State.ChangeState(EWH_LAMPSATE::Change);
		return;
	}
}

void WitchHouseLamp::UpdateChange(float _Delta, GameEngineState* _Parent)
{
	const float EndTime = 2.0f;
	const float UpdateTime = _Parent->GetStateTime();
	if (UpdateTime > EndTime)
	{
		State.ChangeState(EWH_LAMPSATE::Night);
		return;
	}

	const float Brighter = UpdateTime / EndTime;
	const float Alpha = std::lerp(0.0f, 1.0f, Brighter);
	SetAlpha(Alpha);
}