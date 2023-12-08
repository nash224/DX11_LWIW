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

	void CallFadeOut(std::string_view _NextLevelName, float _FadeOutDuration = 1.0f);
	void CallFadeIn(float _FadeOutDuration = 1.0f);


protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void Init();
	void RendererSetting();
	void PositionSetting();


private:
	void UpdateFade(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> FadeRenderer = nullptr;

	CallFadeType FadeType = CallFadeType::None;
	std::string NextLevelName;

	float FadeDuration = 1.0f;
	float AccTime = 0.0f;
	float Alpha = 0.0f;


};

