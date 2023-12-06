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
	friend class ContentsGUI;
	friend class PlayLevel;

public:
	// constrcuter destructer
	TimeManager();
	~TimeManager();

	// delete Function
	TimeManager(const TimeManager& _Other) = delete;
	TimeManager(TimeManager&& _Other) noexcept = delete;
	TimeManager& operator=(const TimeManager& _Other) = delete;
	TimeManager& operator=(TimeManager&& _Other) noexcept = delete;

	void SetTimeFlowRatio(float _FlowRatio);
	void SetTime(float _Time);

	void Pause(bool _Value);
	void Reset();

	float GetMaxTime() const;
	float GetTime() const;
	float GetTime(unsigned int  _Hour, unsigned int  _Minute) const;
	void SetTime(unsigned int  _Hour, unsigned int  _Minute);
	int GetHour() const;
	int GetStartHour() const;
	int GetMinute() const;
	int GetDayCount() const;
	
	float GetTimeRatio() const;
	float GetMinuteRatio() const;

	bool IsDay();
	EDAYSTATE GetDayState() const;


	void ChangeDay();

	inline bool& GetPause()
	{
		return IsPause;
	}

	inline float& GetTimeFlowRatio()
	{
		return TimeFlowRatio;
	}

	inline float& GetTimePointer()
	{
		return Time;
	}

protected:
	void Update(float _Delta);
	void ConvertTimeToHour();
	void ConvertHourToTime();

private:
	bool IsPause = false;
	float TimeFlowRatio = 1.0f;
	float Time = 0.0f;
	float MaxTime = 0.0f;

	int DayCount = 1;
	int Hour = 0;
	int Minute = 0;

	EDAYSTATE DayState = EDAYSTATE::None;

	static constexpr int Start_Day_Hour = 9;
	static constexpr int Start_Night_Hour = 19;
	static constexpr int End_Day_Hour = 24;

	static constexpr int OneMinutes_PerHour = 60;

	static constexpr int TenMinute_PerHour = 5;

};

