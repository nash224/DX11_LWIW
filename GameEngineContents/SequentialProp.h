#pragma once


class SequentialProp : public GameEngineActor
{
	friend class ChainProp;

public:
	// constrcuter destructer
	SequentialProp();
	~SequentialProp();

	// delete Function
	SequentialProp(const SequentialProp& _Other) = delete;
	SequentialProp(SequentialProp&& _Other) noexcept = delete;
	SequentialProp& operator=(const SequentialProp& _Other) = delete;
	SequentialProp& operator=(SequentialProp&& _Other) noexcept = delete;

	void Init();
	void SetTextureScale(const float4& _Scale);
	void SetSpeed(float _Speed);

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateSequential(float _Delta);

public:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

private:
	float4 RenderScale = float4::ZERO;

	float MoveSpeed = 0.0f;
	bool isOverScreen = false;
};

