#pragma once

enum class EMOJITYPE
{
	Exclamation,
	Question,
};

// Ό³Έν :
class Emoji
{
private:
	enum class EEMOJISTATE
	{
		Expression,
		None,
	};

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

	void ShowExpression(EMOJITYPE _Type);

	void Update(float _Delta);

	void Release();

protected:

private:
	void RendererSetting(GameEngineActor* _Actor, const float4& _EmotionPos);
	void StateSetting();

	void StartExpression(GameEngineState* State);
	void StartNone(GameEngineState* State);

	void UpdateExpression(float _Delta, GameEngineState* State);

	std::string GetFileName(EMOJITYPE _Type);
	void CalculateEmotionPos();

private:
	std::shared_ptr<GameEngineUIRenderer> BaseRenderer;
	std::shared_ptr<GameEngineUIRenderer> EmotionRenderer;
	GameEngineActor* Parent = nullptr;

	GameEngineState State;
	float4 EmotionPos;

};

