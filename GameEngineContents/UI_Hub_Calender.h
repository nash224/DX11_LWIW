#pragma once
#include "UI_Hub_Actor.h"

#include "TimeManager.h"

// Ό³Έν :
class UI_Hub_Calender : public UI_Hub_Actor
{
private:
	class CalenderStruct
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> UnderLine;
		std::shared_ptr<GameEngineUIRenderer> Symbol;
		std::shared_ptr<GameEngineUIRenderer> Font_Day;
		std::shared_ptr<GameEngineUIRenderer> Font_Week;
		std::shared_ptr<GameEngineUIRenderer> Font_Time;
		std::shared_ptr<GameEngineUIRenderer> Font_Meridiem;

	};


public:
	// constrcuter destructer
	UI_Hub_Calender();
	~UI_Hub_Calender();

	// delete Function
	UI_Hub_Calender(const UI_Hub_Calender& _Other) = delete;
	UI_Hub_Calender(UI_Hub_Calender&& _Other) noexcept = delete;
	UI_Hub_Calender& operator=(const UI_Hub_Calender& _Other) = delete;
	UI_Hub_Calender& operator=(UI_Hub_Calender&& _Other) noexcept = delete;

	void Init();
	
protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void UpateCalender();

	void UpdateAll();
	void UpdateRenderTime();
	void UpdateRenderDayAndWeek();
	void UpdateSymbol();
	void UpdateMeridiem(std::string_view _Text);

	void DayReset();

	void SetCalenderFont(const std::shared_ptr<GameEngineUIRenderer>& _FontRenderer,
		std::string_view _Text, float _Scale) const;

private:
	CalenderStruct Calender;
	std::string WeekString;
	int RenderTime = 0;
	int RenderDayCount = 0;
	bool RenderAnteMeridiem = true;
	EDAYSTATE RenderDayState = EDAYSTATE::None;

	std::string_view FontStyle = GlobalValue::Font_Cafe24;
	const float4 FontColorWhite = float4(0.95f, 0.95f, 0.95f, 1.0f);

};


