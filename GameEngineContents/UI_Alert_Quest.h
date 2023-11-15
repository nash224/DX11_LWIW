#pragma once
#include "UI_Alert_Base.h"

#include "AlertManager.h"

// Ό³Έν :
class UI_Alert_Quest : public UI_Alert_Base
{
private:
	enum class ESTAMPSTATE
	{
		Appear,
		Done,
		None,
	};

private:
	class AlertQuestInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> HeadFont;
		std::shared_ptr<GameEngineUIRenderer> QuestFrame;
		std::shared_ptr<GameEngineUIRenderer> UnderLine;
		std::shared_ptr<GameEngineUIRenderer> Stamp;
		std::shared_ptr<GameEngineUIRenderer> Black;
		std::shared_ptr<GameEngineUIRenderer> Font;

	public:
		static constexpr const float UnderLine_Initial_X_Scale_Ratio = 0.7f;

		const float4 Stamp_Initial_Scale_Ratio_Size = float4(1.8f, 1.8f);

		static constexpr const float Stamp_Change_FadeIn_Time = 0.2f;
		

		bool isStamped = false;

	};

public:
	// constrcuter destructer
	UI_Alert_Quest();
	~UI_Alert_Quest();

	// delete Function
	UI_Alert_Quest(const UI_Alert_Quest& _Other) = delete;
	UI_Alert_Quest(UI_Alert_Quest&& _Other) noexcept = delete;
	UI_Alert_Quest& operator=(const UI_Alert_Quest& _Other) = delete;
	UI_Alert_Quest& operator=(UI_Alert_Quest&& _Other) noexcept = delete;

	static void CallAlertQuest(GameEngineLevel* _Level, std::string_view _QuestName, EALERTTYPE _Type);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void SameInit(std::string_view _QuestName);
	void QuestAcceptInit(std::string_view _QuestName);
	void QuestClearInit(std::string_view _QuestName);

	void RendererSetting(std::string_view _LevelName);
	void StampRendererSetting();
	void SoundSetting();

	void StartFadeIn(GameEngineState* _Parent) override;

	void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateStay(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent) override;

private:
	AlertQuestInfo QuestInfo;
	GameEngineState StampState;

	static constexpr const float Fade_Change_Time = 1.0f;
	static constexpr const float WaitTime = 1.4f;

private:
	void FSMStampSetting();

	void StartAppear(GameEngineState* _Parent);
	void UpdateAppear(float _DeltaTime, GameEngineState* _Parent);
	void UpdateDone(float _DeltaTime, GameEngineState* _Parent);

};

