#pragma once
#include "UI_Alert_Base.h"

// Ό³Έν :
class UI_Alert_Tutorial : public UI_Alert_Base
{
private:
	enum class ETUTORIALTYPE
	{
		Move,
		Interact,
		SlowWalk,
		Sprint,
		SwapTool,
		Direction,
	};


private:
	class UIAlertTutorialInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> Base;
		std::shared_ptr<GameEngineUIRenderer> Img;
		std::shared_ptr<GameEngineUIRenderer> Fade;
		std::shared_ptr<GameEngineUIRenderer> TitleFont;
		std::shared_ptr<GameEngineUIRenderer> ContentFont;

	public:
		static constexpr float Fade_Change_Time = 1.0f;

		static constexpr float FontScale = 23.0f;

	};


public:
	// constrcuter destructer
	UI_Alert_Tutorial();
	~UI_Alert_Tutorial();

	// delete Function
	UI_Alert_Tutorial(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial(UI_Alert_Tutorial&& _Other) noexcept = delete;
	UI_Alert_Tutorial& operator=(const UI_Alert_Tutorial& _Other) = delete;
	UI_Alert_Tutorial& operator=(UI_Alert_Tutorial&& _Other) noexcept = delete;

	static float AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void Init(std::string_view _LevelName);
	void RendererSetting(std::string_view _LevelName);

	void StartFadeIn(GameEngineState* _Parent) override;

	void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateStay(float _DeltaTime, GameEngineState* _Parent) override;
	void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent) override;


private:
	UIAlertTutorialInfo AlertInfo;

	const float4 FadeMulColor = float4(0.0f, 0.0f, 0.0f, 0.4f);

	static constexpr float StartAlphaRatio = 0.7f;
	static constexpr float PopupTime = 0.3f;

};

