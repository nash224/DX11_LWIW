#pragma once



static constexpr const float Max_Day_Time = 450.0f;

enum class EDAYSTATE
{
	Day,
	Night,
	None,
};


// Ό³Έν :
class TimeManager 
{
public:
	// constrcuter destructer
	TimeManager();
	~TimeManager();

	// delete Function
	TimeManager(const TimeManager& _Other) = delete;
	TimeManager(TimeManager&& _Other) noexcept = delete;
	TimeManager& operator=(const TimeManager& _Other) = delete;
	TimeManager& operator=(TimeManager&& _Other) noexcept = delete;

	void Init();
	void SetTimeFlowRatio(float _FlowRatio);
	void SetTime(float _Time);

	void Pause(bool _Value);
	void Reset();

	float GetTime() const;
	void SetTime(unsigned int  _Hour, unsigned int  _Minute = 0);
	int GetHour() const;
	int GetMinute() const;
	float GetTimeRatio() const;
	float GetMinuteRatio() const;

	bool IsDay();

	void Update(float _Delta);
	void ConvertTimeToHour();
	void ConvertHourToTime();

protected:

private:
	bool IsPause = false;
	float TimeFlowRatio = 1.0f;
	float Time = 0.0f;

	int Hour = 0;
	int Minute = 0;

	EDAYSTATE DayState = EDAYSTATE::None;

	static constexpr const int Start_Day_Hour = 9;
	static constexpr const int End_Day_Hour = 24;

	static constexpr const int Ten_Minutes_Count_Per_Hour = 6;

	static constexpr const float Night_Start_Time = 240.0f;
	static constexpr const int Ratio_Per_Minute = 5;

	static constexpr const int Night_Hour = 19;

};

