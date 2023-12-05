#pragma once
#include "InteractiveActor.h"
#include "ALightLerp.h"


// Ό³Έν :
class BushBug : public InteractiveActor
{
private:
	enum class EBUSHBUGSTATE
	{
		Idle,
		Move,
		None,
	};

public:
	// constrcuter destructer
	BushBug();
	~BushBug();

	// delete Function
	BushBug(const BushBug& _Other) = delete;
	BushBug(BushBug&& _Other) noexcept = delete;
	BushBug& operator=(const BushBug& _Other) = delete;
	BushBug& operator=(BushBug&& _Other) noexcept = delete;

	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void AnimationSetting();
	void StateSetting();
	void ALightSetting();


	void StartMove(GameEngineState* _Parent);
	void SearchFlyDirection();
	void UpdateMove(float _Delta, GameEngineState* _Parent);
	


private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	ALightLerp Alight;

	GameEngineState MainState;

	float4 SpawnPosition = float4::ZERO;
	float FlyAngle = 0.0f;
};

