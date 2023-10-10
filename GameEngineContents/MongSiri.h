#pragma once
#include "DynamicEntity.h"

constexpr float MongSiri_JumpMinSpeed = 0.0f;
constexpr float MongSiri_JumpMaxSpeed = 60.0f;


enum class EMONGSIRISTATUS
{
	Normal,
	Escape,
	Look,
	None,
};
// 몽시리 상태 : 


enum class EMONGSIRISTATE
{
	Idle,
	Jump,
	Look,
	Caught,
	Collected,
	Disappear,
	None,
};

// 설명 :
class MongSiri : public DynamicEntity
{
	friend class Ellie;
	friend class MongSiri_Population;

private:
	class MongSiri_Population* MongSiriParant = nullptr;

public:
	// constrcuter destructer
	MongSiri();
	~MongSiri();

	// delete Function
	MongSiri(const MongSiri& _Other) = delete;
	MongSiri(MongSiri&& _Other) noexcept = delete;
	MongSiri& operator=(const MongSiri& _Other) = delete;
	MongSiri& operator=(MongSiri&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateAndSetRenderer();
	void InitDirection();

private:
	void ChangeAnimation(std::string_view _StateName);
	void ChangeAnimationByDircetion(std::string_view _StateName);

	bool IsPlayerAround();

private:
	void UpdateState(float _Delta);
	void ChangeState(EMONGSIRISTATE _State);

	void StartIdle();
	void UpdateIdle(float _Delta);
	void EndIdle();

	void StartJump();
	void SearchJumpLocation();
	void UpdateJump(float _Delta);
	void EndJump();

	void StartLook();
	void UpdateLook(float _Delta);

	void GetCaught() override;
	void StartCaught();
	void UpdateCaught(float _Delta);


	void StartCollected();
	void UpdateCollected(float _Delta);
	void EndCollected();

	void StartDisappear();
	void UpdateDisappear(float _Delta);



private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

private:
	// 상태
	EMONGSIRISTATE m_State = EMONGSIRISTATE::None;
	EMONGSIRISTATUS m_Status = EMONGSIRISTATUS::None;

private:
	float4 m_TargetForce = float4::ZERO;
	int m_IdleCount = 0;

	bool IsOnTheHole = false;

private:
	const float MongSiri_FOVSize = 90.0f;
};


