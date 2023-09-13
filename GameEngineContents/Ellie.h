#pragma once
#include "InteractiveActor.h"
#include "ActorEnum.h"

constexpr float EllieIdleInter = 0.2f;

constexpr float EllieWalkSpeed = 200.0f;

enum class EELLIE_STATE
{
	None,
	Idle,
	Walk,
	Run,
};

// 설명 :
class Ellie : public InteractiveActor
{
public:
	// constrcuter destructer
	Ellie();
	~Ellie();

	// delete Function
	Ellie(const Ellie& _Other) = delete;
	Ellie(Ellie&& _Other) noexcept = delete;
	Ellie& operator=(const Ellie& _Other) = delete;
	Ellie& operator=(Ellie&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	void Init();
	

private:
	void ChangeState(EELLIE_STATE _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationByDirection(const std::string& _StateName, bool _Force =  false, unsigned int _Index = 0);


	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartWalk();
	void UpdateWalk(float _Delta);

	void StartRun();
	void UpdateRun(float _Delta);


private:
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	float4 CalulateDirectionVectorToDir(const EDIRECTION _Direction);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


private:
	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;
	float m_StateTime = 0.0f;

	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

private:
};

