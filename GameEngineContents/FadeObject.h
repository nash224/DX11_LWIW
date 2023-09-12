#pragma once


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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


public:
	static void CallFadeOut(std::shared_ptr<GameEngineLevel> _Level, std::function<void()> _Func, float _FadeOutDuration = 1.0f);
	static void CallFadeIn(std::shared_ptr<GameEngineLevel> _Level, float _FadeOutDuration = 1.0f);


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_FadeRenderer = nullptr;

	CallFadeType m_FadeType = CallFadeType::None;

	std::function<void()> m_Func;

	bool IsQuit = false;
	const float QuitTime = 5.0f;

	int m_RequestAlphaValue = 0;

	float m_FadeDuration = 1.0f;
	float m_FadeTime = 0.0f;
	int m_DebugAlphaValue = 0;


	const int MinAlphaValue = 0;
	const int MaxAlphaValue = 255;
};

