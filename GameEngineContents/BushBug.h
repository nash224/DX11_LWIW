#pragma once
#include "DynamicEntity.h"

#define BUSHBUG_SPEED 16.0f
#define BUSHBUG_MAX_YANGLE 5.0f
#define BUSHBUG_MOVE_RANGE 50.0f


enum class EBUSHBUGSTATE
{
	Idle,
	Move,
	None,
};


// Ό³Έν :
class BushBug : public DynamicEntity
{
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void AnimationSetting();
	void StateSetting();


	void StartMove(GameEngineState* _Parent);
	void SearchFlyDirection();
	void UPdateMove(float _Delta, GameEngineState* _Parent);


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

	GameEngineState MoveState;

	float4 SpawnPosition = float4::ZERO;
	float m_FlyAngle = 0.0f;
};

