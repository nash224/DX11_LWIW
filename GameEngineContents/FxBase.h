#pragma once

// Ό³Έν :
class FxBase : public GameEngineActor
{
public:
	// constrcuter destructer
	FxBase();
	~FxBase();

	// delete Function
	FxBase(const FxBase& _Other) = delete;
	FxBase(FxBase&& _Other) noexcept = delete;
	FxBase& operator=(const FxBase& _Other) = delete;
	FxBase& operator=(FxBase&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void Init();

	std::shared_ptr<GameEngineSpriteRenderer> Fx;


};

