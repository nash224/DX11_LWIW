#pragma once
#include "InteractiveActor.h"
#include "Emoji.h"


// Ό³Έν :
class FlowerBird : public InteractiveActor
{
private:
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

	void Leave();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	std::string RandomBirdCrySoundName();

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

	bool ReadyToFly();
	bool FeelThreatened();
	void ShowThreatenRange() const;
	bool RecognizeWalkingEllie() const;
	bool RecognizeEllie() const;


private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;

	Emoji Emotion;

	EFLOWERBIRDSTATE m_State = EFLOWERBIRDSTATE::None;
	EFLOWERBIRDSTATE NextState = EFLOWERBIRDSTATE::None;

	bool IsActted = false;

	int PickCount = 0;
	int TurnCount = 0;
	int AssignedTurnCount = 0;
	const int MaxPickCount = 8;

	float StateTime = 0.0f;
	float IdleTime = 0.0f;
	float TurnTime = 0.0f;


	float4 FlyDirVector = float4::ZERO;
	static constexpr float FlyDegree = 30.0f;
	static constexpr float TurnSlowTime = 0.4f;
	static constexpr float TurnFastTime = 0.1f;

};

