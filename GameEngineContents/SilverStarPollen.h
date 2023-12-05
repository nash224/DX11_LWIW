#pragma once

// Ό³Έν :
class SilverStarPollen : public GameEngineActor
{
public:
	// constrcuter destructer
	SilverStarPollen();
	~SilverStarPollen();

	// delete Function
	SilverStarPollen(const SilverStarPollen& _Other) = delete;
	SilverStarPollen(SilverStarPollen&& _Other) noexcept = delete;
	SilverStarPollen& operator=(const SilverStarPollen& _Other) = delete;
	SilverStarPollen& operator=(SilverStarPollen&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void MoveSetting();

	void UpdateState(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> PollenRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> ParticleRenderer;

	float MovePower = 0.0f;

	static constexpr const float MovementRadius = 12.0f;

	static constexpr const float LiveTime = 1.0f;

};

