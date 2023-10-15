#pragma once
#include "DynamicEntity.h"


constexpr float FlowerBirdMaxRange = 60.0f;

constexpr float FlowerBirdIdleWaitTime = 0.6f;

enum class EFLOWERBIRDSTATE
{
	Idle,
	Turn,
	Pick,
	Bloom,
	BloomFake,
	BloomFlowers,
	Fly,
	None,

};



// Ό³Έν :
class FlowerBird : public DynamicEntity
{
public:
	// constrcuter destructer
	FlowerBird();
	~FlowerBird();

	// delete Function
	FlowerBird(const FlowerBird& _Other) = delete;
	FlowerBird(FlowerBird&& _Other) noexcept = delete;
	FlowerBird& operator=(const FlowerBird& _Other) = delete;
	FlowerBird& operator=(FlowerBird&& _Other) noexcept = delete;


	void Init();
	void AnimationSetting();
	void DirectionSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateState(float _Delta);
	void ChangeState(EFLOWERBIRDSTATE _State);
	void ChangeFlowerBirdAnimation(std::string_view _AnimationName);


	void StartIdle();
	void DecideAction();
	void UpdateIdle(float _Delta);
	void EndIdle();

	void StartTurn();
	void UpdateTurn(float _Delta);

	void StartPick();
	void UpdatePick(float _Delta);

	void StartBloom();
	void UpdateBloom(float _Delta);

	void StartBloomFake();
	void UpdateBloomFake(float _Delta);

	void StartBloomFlowers();
	void UpdateBloomFlowers(float _Delta);

	void StartFly();
	void UpdateFly(float _Delta);



private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

	int m_PickCount = 0;
	const int MaxPickCount = 4;

private:
	EFLOWERBIRDSTATE m_State = EFLOWERBIRDSTATE::None;
	EFLOWERBIRDSTATE m_NextState = EFLOWERBIRDSTATE::None;

	bool IsActted = false;

	float m_StateTime = 0.0f;
	float m_IdleTime = 0.0f;

	int m_TurnCount = 0;
};

