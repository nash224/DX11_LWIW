#pragma once
#include "InteractiveActor.h"
#include "ActorEnum.h"

constexpr float EllieIdleInter = 0.2f;
constexpr float EllieWalkSpeed = 200.0f;

constexpr float Ellie_Run_Inter = 0.1f;
constexpr float Ellie_Run_Speed = 300.0f;

enum class EELLIE_STATE
{
	None,
	Idle,
	Walk,
	Run,
};



// 설명 : 주인공 앨리입니다. 
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
	// 이니셜
	void Init();
	

private:
	// FSM
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
	// 방향 키 감지
	// 안될건 없지만 1프레임당 한번 업데이트 되는 것을 원칙으로 합니다.
	// 어차피 한번 실행하나 두번 실행하다 똑같습니다.
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// 방향 계산 함수
	float4 CalulateDirectionVectorToDir(const EDIRECTION _Direction);

private:
	// 렌더러
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


private:
	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;
	float m_StateTime = 0.0f;


	// 방향 키 관련
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

private:
};

