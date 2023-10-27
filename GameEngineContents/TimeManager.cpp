#include "PreCompile.h"
#include "TimeManager.h"


TimeManager::TimeManager() 
{
}

TimeManager::~TimeManager() 
{
}


void TimeManager::Init()
{
	DayState = EDAYSTATE::Day;
}

void TimeManager::SetTime(float _Time)
{
	Time = _Time;
}

void TimeManager::SetTimeFlowRatio(float _FlowRatio)
{
	TimeFlowRatio = _FlowRatio;
}

void TimeManager::Pause(bool _Value)
{
	IsPause = _Value;
}

void TimeManager::Reset()
{
	IsPause = false;
	Time = 0.0f;
	DayState = EDAYSTATE::Day;
}

float TimeManager::GetTime() const
{
	return Time;
}

float TimeManager::GetTimeRatio() const
{
	return Time / MAX_DAY_TIME;
}

float TimeManager::GetMinuteRatio() const
{
	return UNIT_MINUTE_RATIO / MAX_DAY_TIME;
}


void TimeManager::Update(float _Delta)
{
	if (true == IsPause)
	{
		return;
	}

	Time += _Delta * TimeFlowRatio;

	if (Time > MAX_DAY_TIME)
	{
		DayState = EDAYSTATE::None;
	}
	else if (Time > NIGHT_START_TIME)
	{
 		DayState = EDAYSTATE::Night;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


bool TimeManager::IsDay()
{
	if (EDAYSTATE::None == DayState)
	{
		MsgBoxAssert("초기화를 하지 않았습니다.");
		return false;
	}

	if (EDAYSTATE::Day == DayState)
	{
		return true;
	}

	return false;
}