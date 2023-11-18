#pragma once

// Ό³Έν :
class FireSky : public GameEngineActor
{
public:
	// constrcuter destructer
	FireSky();
	~FireSky();

	// delete Function
	FireSky(const FireSky& _Other) = delete;
	FireSky(FireSky&& _Other) noexcept = delete;
	FireSky& operator=(const FireSky& _Other) = delete;
	FireSky& operator=(FireSky&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();

private:
	std::shared_ptr<GameEngineSpriteRenderer> LineRenderer;

};

