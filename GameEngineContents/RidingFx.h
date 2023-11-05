#pragma once

// Ό³Έν :
class RidingFx : public GameEngineActor
{
public:
	// constrcuter destructer
	RidingFx();
	~RidingFx();

	// delete Function
	RidingFx(const RidingFx& _Other) = delete;
	RidingFx(RidingFx&& _Other) noexcept = delete;
	RidingFx& operator=(const RidingFx& _Other) = delete;
	RidingFx& operator=(RidingFx&& _Other) noexcept = delete;


	void Init(const float4& _ParentPosition);

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> FxRenderer;


};

