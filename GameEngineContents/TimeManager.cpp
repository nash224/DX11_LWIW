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

float TimeManager::GetTime() const
{
	return Time;
}

void TimeManager::SetTime(unsigned int _Hour, unsigned int _Minute /*= 0*/)
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

	if (Hour > Night_Hour)
	{
		DayState = EDAYSTATE::Night;
	}

	ConvertHourToTime();
}

int TimeManager::GetHour() const
{
	return Hour;
}

int TimeManager::GetMinute() const
{
	return Minute;
}

float TimeManager::GetTimeRatio() const
{
	return Time / Max_Day_Time;
}

float TimeManager::GetMinuteRatio() const
{
	return static_cast<float>(Ratio_Per_Minute) / Max_Day_Time;
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

	if (Hour >= Night_Hour)
	{
 		DayState = EDAYSTATE::Night;
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

void TimeManager::ConvertTimeToHour()
{
	float fHour = 0.0f;
	float TimeRatio = Time / static_cast<float>(Ratio_Per_Minute * Ten_Minutes_Count_Per_Hour);
	float fMinutes = std::modff(TimeRatio, &fHour);
	const int AddHour = static_cast<int>(fHour);

	Hour = Start_Day_Hour + AddHour;
	Minute = static_cast<int>(fMinutes * 60.0f);
}

void TimeManager::ConvertHourToTime()
{
	// 450 / 15 = 30
	// (End_Day_Hour - Start_Day_Hour) * Ten_Minutes_Count_Per_Hour * Ratio_Per_Minute
	int HourTime = (Hour - Start_Day_Hour) * Ten_Minutes_Count_Per_Hour * Ratio_Per_Minute;
	int MinuteTime = Minute / (60);
	Time = static_cast<float>(HourTime + MinuteTime);
}