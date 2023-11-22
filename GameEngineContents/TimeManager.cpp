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
	Reset();

	MaxTime = static_cast<float>((End_Day_Hour - Start_Day_Hour) * One_Minutes_Per_Hour / (10 / Ratio_Per_TenMinute));

	SetTime(10, 0);
}

void TimeManager::SetTime(float _Time)
{
	Time = _Time;

	ConvertTimeToHour();
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

	Hour = Start_Day_Hour;
	Minute = 0;
}


float TimeManager::GetMaxTime()
{
	return MaxTime;
}

float TimeManager::GetTime() const
{
	return Time;
}

void TimeManager::SetTime(unsigned int _Hour, unsigned int _Minute)
{
	int AddHour = 0;

	while (true)
	{
		if (_Minute >= 60)
		{
			_Minute -= 60;
			AddHour++;
		}
		else
		{
			Minute = _Minute;
			break;
		}
	}

	AddHour += _Hour;

	if (AddHour < Start_Day_Hour)
	{
		Hour = Start_Day_Hour;
		Minute = 0;
	}
	else if (AddHour > End_Day_Hour)
	{
		Hour = 24;
		Minute = 0;
	}
	else
	{
		Hour = AddHour;
	}

	ConvertHourToTime();
}

int TimeManager::GetHour() const
{
	return Hour;
}

int TimeManager::GetStartHour() const
{
	return Start_Day_Hour;
}

int TimeManager::GetMinute() const
{
	return Minute;
}

int TimeManager::GetDayCount() const
{
	return DayCount;
}

float TimeManager::GetTimeRatio() const
{
	return Time / MaxTime;
}

float TimeManager::GetMinuteRatio() const
{
	return static_cast<float>(Ratio_Per_TenMinute) / MaxTime;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void TimeManager::Update(float _Delta)
{
	if (true == IsPause)
	{
		return;
	}

	Time += _Delta * TimeFlowRatio;

	ConvertTimeToHour();

	if (Hour >= Start_Night_Hour)
	{
		DayState = EDAYSTATE::Night;
	}
	else
	{
		DayState = EDAYSTATE::Day;
	}
}

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

EDAYSTATE TimeManager::GetDayState() const
{
	if (EDAYSTATE::None == DayState)
	{
		return EDAYSTATE::None;
	}
	
	return DayState;
}

void TimeManager::ConvertTimeToHour()
{
	float fHour = 0.0f;
	float TimeRatio = Time / static_cast<float>(One_Minutes_Per_Hour / (10 / Ratio_Per_TenMinute));
	float fMinutes = std::modff(TimeRatio, &fHour);
	const int AddHour = static_cast<int>(fHour);

	Hour = Start_Day_Hour + AddHour;
	Minute = static_cast<int>(fMinutes * 60.0f);

	if (Hour >= Start_Night_Hour)
	{
		DayState = EDAYSTATE::Night;
	}
	else
	{
		DayState = EDAYSTATE::Day;
	}
}

void TimeManager::ConvertHourToTime()
{
	int HourTime = (Hour - Start_Day_Hour) * One_Minutes_Per_Hour / (10 / Ratio_Per_TenMinute);
	int MinuteTime = Minute / (10 / Ratio_Per_TenMinute);
	Time = static_cast<float>(HourTime + MinuteTime);

	if (Hour >= Start_Night_Hour)
	{
		DayState = EDAYSTATE::Night;
	}
	else
	{
		DayState = EDAYSTATE::Day;
	}
}

void TimeManager::ChangeDay()
{
	Reset();
	++DayCount;
}