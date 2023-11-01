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

int TimeManager::GetHour() const
{
	const int AddHour = static_cast<int>(Time / (Unit_Minute_Ratio * static_cast<float>(Ten_Minutes_Count_Per_Hour)));
	const int CurHour = Start_Hour + AddHour;
	return CurHour;
}

float TimeManager::GetTimeRatio() const
{
	return Time / Max_Day_Time ;
}

float TimeManager::GetMinuteRatio() const
{
	return Unit_Minute_Ratio / Max_Day_Time ;
}


void TimeManager::Update(float _Delta)
{
	if (true == IsPause)
	{
		return;
	}

	Time += _Delta * TimeFlowRatio;

	if (Time > Max_Day_Time )
	{
		DayState = EDAYSTATE::None;
	}
	else if (Time > Night_Start_Time)
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