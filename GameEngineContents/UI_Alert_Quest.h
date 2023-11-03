#pragma once
#include "UI_Alert_Base.h"

// Ό³Έν :
class UI_Alert_Quest : public UI_Alert_Base
{
private:
	class AlertQuestInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> QuestFrame;
		std::shared_ptr<GameEngineUIRenderer> QuestName;
		std::shared_ptr<GameEngineUIRenderer> UnderLine;
		std::shared_ptr<GameEngineUIRenderer> Stamp;
		std::shared_ptr<GameEngineUIRenderer> Black;
		std::shared_ptr<GameEngineUIRenderer> Font;

	public:
		static constexpr const float Fade_Change_Time = 1.0f;

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

	static float AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void Init(std::string_view _LevelName);
	void RendererSetting(std::string_view _LevelName);

	void StartFadeIn(GameEngineState* _Parent) override;

	void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateStay(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent) override;

private:
	AlertQuestInfo QuestInfo;

};

