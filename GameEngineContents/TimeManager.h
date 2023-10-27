#pragma once

#define UNIT_MINUTE_RATIO 5.0f

#define MAX_DAY_TIME 450.0f
#define NIGHT_START_TIME 240.0f


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
	float GetTimeRatio() const;
	float GetMinuteRatio() const;

	bool IsDay();

	void Update(float _Delta);

protected:

private:
	bool IsPause = false;
	float TimeFlowRatio = 1.0f;
	float Time = 0.0f;

	EDAYSTATE DayState = EDAYSTATE::None;

};

