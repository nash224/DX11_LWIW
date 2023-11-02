#pragma once

// Ό³Έν :
class UI_Alert_Enter : public GameEngineActor
{
private:
	enum class EENTERSTATE
	{
		FadeIn,
		Stay,
		FadeOut,
	};

	class AlertEnterInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ZoneName;
		std::shared_ptr<GameEngineUIRenderer> Black;
		std::shared_ptr<GameEngineUIRenderer> Font;

	public:
		static constexpr const float Fade_Change_Time = 1.0f;
		const float4 FontColor = float4::WHITE;

	};


public:
	// constrcuter destructer
	UI_Alert_Enter();
	~UI_Alert_Enter();

	// delete Function
	UI_Alert_Enter(const UI_Alert_Enter& _Other) = delete;
	UI_Alert_Enter(UI_Alert_Enter&& _Other) noexcept = delete;
	UI_Alert_Enter& operator=(const UI_Alert_Enter& _Other) = delete;
	UI_Alert_Enter& operator=(UI_Alert_Enter&& _Other) noexcept = delete;

	static float AlertLevelEnter(GameEngineLevel* _Level, std::string_view _LevelName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void Init(std::string_view _LevelName);
	void RendererSetting(std::string_view _LevelName);
	void FSMSetting();

	void StartFadeIn(GameEngineState* _Parent);

	void UpdateFadeIn(float _DeltaTime, GameEngineState* _Parent);
	void UpdateStay(float _DeltaTime, GameEngineState* _Parent);
	void UpdateFadeOut(float _DeltaTime, GameEngineState* _Parent);

	void ChangeFontAlpha(float _ColorRatio);
	void ChangeMulColor(std::weak_ptr<GameEngineUIRenderer> _Member, float _ColorRatio);


private:
	AlertEnterInfo AlertData;

	GameEngineState State;

};

