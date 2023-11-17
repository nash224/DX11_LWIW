#pragma once



enum class EDAYSTATE
{
	Day,
	Night,
	DayChange,
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

	float GetMaxTime();
	float GetTime() const;
	void SetTime(unsigned int  _Hour, unsigned int  _Minute);
	int GetHour() const;
	int GetStartHour() const;
	int GetMinute() const;
	int GetDayCount() const;
	
	float GetTimeRatio() const;
	float GetMinuteRatio() const;

	bool IsDay();
	EDAYSTATE GetDayState() const;

	void Update(float _Delta);
	void ConvertTimeToHour();
	void ConvertHourToTime();


	void ChangeDay();

protected:

private:
	bool IsPause = false;
	float TimeFlowRatio = 1.0f;
	float Time = 0.0f;
	float MaxTime = 0.0f;

	int DayCount = 1;
	int Hour = 0;
	int Minute = 0;

	EDAYSTATE DayState = EDAYSTATE::None;

	static constexpr const int Start_Day_Hour = 9;
	static constexpr const int Start_Night_Hour = 19;
	static constexpr const int End_Day_Hour = 24;

	static constexpr const int One_Minutes_Per_Hour = 60;

	static constexpr const int Ratio_Per_TenMinute = 5;

};

