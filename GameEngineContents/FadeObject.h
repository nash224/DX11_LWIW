#pragma once


constexpr float MaxAlphaValue = 1.0f;
constexpr float MinAlphaValue = 0.0f;

enum class CallFadeType
{
	None,
	FadeOut,
	FadeIn,
};


// Ό³Έν :
class FadeObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	void Init();

	static void CallFadeOut(GameEngineLevel* _Level, std::string_view _NextLevelName, float _FadeOutDuration = 1.0f);
	static void CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration = 1.0f);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void RendererSetting();
	void PositionSetting();


private:
	void UpdateFade(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> m_FadeRenderer = nullptr;

private:
	CallFadeType m_FadeType = CallFadeType::None;
	std::string m_NextLevelName = "";

	float m_FadeDuration = 1.0f;
	float m_FadeTime = 0.0f;
	float m_AlphaValue = 0.0f;


};

