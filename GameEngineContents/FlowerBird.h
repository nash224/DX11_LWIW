#pragma once
#include "DynamicEntity.h"


constexpr float FlowerBirdMaxRange = 60.0f;

constexpr float FlowerBirdIdleWaitTime = 0.6f;

constexpr float FlowerBirdTurnSlowTime = 0.4f;
constexpr float FlowerBirdTurnFastTime = 0.1f;

constexpr float FlowerBirdPickWaitTime = 0.4f;

constexpr float FlowerBirdBloomInter = 0.06f;
constexpr float FlowerBirdPeaksInter = 0.2f;
constexpr float FlowerBirdBlossomInter = 1.0f;


constexpr float FlowerBirdMinWitherInter = 0.4f;
constexpr float FlowerBirdMaxWitherInter = 1.6f;


constexpr float FlowerBirdEllieWalkDetectionRange = 80.0f;
constexpr float FlowerBirdEllieDetectionRange = 40.0f;


constexpr float FlowerBirdFlySpeed = 600.0f;


constexpr float FlowerBirdExitCameraBias = 50.0f;


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
	void SwapDirection();
	void AssignTurnTime();
	void UpdateTurn(float _Delta);
	void EndTurn();

	void StartPick();
	void UpdatePick(float _Delta);
	void EndPick();

	void StartBloom();
	void UpdateBloom(float _Delta);
	void EndBloom();

	void StartBloomFake();
	float ReturnWaitWitherInter();
	void UpdateBloomFake(float _Delta);
	void EndBloomFake();

	void StartBloomFlowers();
	void UpdateBloomFlowers(float _Delta);
	void EndBloomFlowers();

	void StartFly();
	void DecideFlyDirection();
	void UpdateFly(float _Delta);

	bool GetReadyToFly();
	bool FeelThreatened();
	bool RecognizeWalkingEllie();
	bool RecognizeEllie();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

private:
	EFLOWERBIRDSTATE m_State = EFLOWERBIRDSTATE::None;
	EFLOWERBIRDSTATE m_NextState = EFLOWERBIRDSTATE::None;

	bool IsActted = false;

	float m_StateTime = 0.0f;
	float m_IdleTime = 0.0f;

	float m_TurnTime = 0.0f;
	int m_TurnCount = 0;
	int m_AssignedTurnCount = 0;

	int m_PickCount = 0;
	const int MaxPickCount = 8;

	float4 m_BirdFlyDirection = float4::ZERO;
	const float m_FlyDegree = 30.0f;
};

