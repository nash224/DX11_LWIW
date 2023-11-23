#pragma once

enum class EEMOJISTATE
{
	Exclamation,
	Question,
	None,
};

// Ό³Έν :
class Emoji
{
public:
	// constrcuter destructer
	Emoji();
	~Emoji();

	// delete Function
	Emoji(const Emoji& _Other) = delete;
	Emoji(Emoji&& _Other) noexcept = delete;
	Emoji& operator=(const Emoji& _Other) = delete;
	Emoji& operator=(Emoji&& _Other) noexcept = delete;

	void Init(GameEngineActor* _Actor, const float4& _EmotionPos = float4::ZERO);

	inline void SetRecognitionRange(float _Range)
	{
		RecognitionRange = _Range;
	}

	inline 	void UseOnlyExclamation()
	{
		isUseOnlyExclamation = true;
	}

	void ShowExclamation();

	void Update(float _Delta);

	void Release();

protected:

private:
	void RendererSetting(GameEngineActor* _Actor, const float4& _EmotionPos);
	void StateSetting();

	void StartExclamation(GameEngineState* State);
	void StartQuestion(GameEngineState* State);

	void UpdateExclamation(float _Delta, GameEngineState* State);
	void UpdateQuestion(float _Delta, GameEngineState* State);

	void StartNone(GameEngineState* State);

	float GetDistanceToEllie();

private:
	std::shared_ptr<GameEngineSpriteRenderer> Base;
	std::shared_ptr<GameEngineSpriteRenderer> Emotion;
	GameEngineActor* Parent = nullptr;

	GameEngineState State;

	bool isUseOnlyExclamation = false;
	float RecognitionRange = 30.0f;

};

