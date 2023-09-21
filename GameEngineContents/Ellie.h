#pragma once
#include "InteractiveActor.h"
#include "ActorEnum.h"


constexpr float EllieIdleInter = 0.2f;
constexpr float Ellie_SlowWalk_Inter = 0.2f;

constexpr float Ellie_Run_Inter = 0.1f;

constexpr float Ellie_Throw_Inter = 0.1f;

constexpr float Ellie_Riding_Idle_Inter = 0.1f;
constexpr float Ellie_Riding_Move_Inter = 0.1f;
constexpr float Ellie_Riding_Boost_Inter = 0.1f;

constexpr float Ellie_ButterflyNet_Inter = 0.1f;

constexpr float Ellie_RootUp_Inter = 0.15f;

constexpr float Ellie_Sit_Inter = 0.12f;

constexpr float Ellie_MongSiri_Inter = 0.2f;


// 체크 포인트 간격
constexpr float CheckPointGap = 2.0f;


enum class EELLIE_STATE
{
	None,
	Idle,
	SlowWalk,
	Walk,
	Run,
	Throw,
	Riding_Idle,
	Riding_Move,
	Riding_Boost,
	Net,
	RootUp,
	Sit,
	MongSiri,
	Cheer,
	Fail,
	Drink,
};

enum class EELLIE_STATUS
{
	None,
	Normal,
	Riding,
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
	void SetSpawnLocalPosition(const float4& _Position);
	void SetMoveControl(bool _Value);
	void SetPixelPointBaseOnCenter();
	/*void TransferControl(bool _Value);*/


	void TestCode();

private:
	// FSM
	void ChangeState(EELLIE_STATE _State);
	void UpdateState(float _Delta);
	void ChangeAnimationByDirection(const std::string& _StateName, bool _DirectionInfluence = true, bool _Force =  false, unsigned int _Index = 0);
	

	bool InputTestPattern();

	void StartIdle();
	void UpdateIdle(float _Delta);

	void StartSlowWalk();
	void UpdateSlowWalk(float _Delta);

	void StartWalk();
	void UpdateWalk(float _Delta);

	void StartRun();
	void UpdateRun(float _Delta);

	void StartThrow();
	void UpdateThrow(float _Delta);

	void StartRiding_Idle();
	void UpdateRiding_Idle(float _Delta);

	void StartRiding_Move();
	void UpdateRiding_Move(float _Delta);

	void StartRiding_Boost();
	void UpdateRiding_Boost(float _Delta);


	void StartNet();
	void UpdateNet(float _Delta);

	void StartRootUp();
	void UpdateRootUp(float _Delta);

	void StartSit();
	void UpdateSit(float _Delta);

	void StartMongSiri();
	void UpdateMongSiri(float _Delta);

	void StartCheer();
	void UpdateCheer(float _Delta);

	void StartFail();
	void UpdateFail(float _Delta);

	void StartDrink();
	void UpdateDrink(float _Delta);

private:
	// 방향 키 감지
	// 안될건 없지만 1프레임당 한번 업데이트 되는 것을 원칙으로 합니다.
	// 어차피 한번 실행하나 두번 실행하다 똑같습니다.
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// 방향 계산 함수
	float4 CalculateDirectionVectorToDir(const EDIRECTION _Direction);

	void CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce);
	EDIRECTION ReturnDirectionCheckBothSide(EDIRECTION _Direction , const float4& _LeftCheckPoint, const float4& _RightCheckPoint);
	EDIRECTION ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(EDIRECTION _Dir, const float4& _MoveVector);


	float4 ReturnPostMoveVector(float _Delta, float _MAXMoveForce, float _Acceleration_Time);

	EDIRECTION ReturnCheckDirToMoveVector(const float4& _MoveVector);
	bool IsOverSpeed(float _CurSpeed, const float _MaxMoveForce);
	void DecelerateMoveVector(float _Delta, const float _MaxMoveForce, const float _DecelerationTime);
	void DecelerateAtMidpoint(float _Delta, const float _MaxMoveForce, const float _Time);
	void ApplyMovementToTransform(float _DElta);
	


private:
	void UpdateCollision();


private:
	// 렌더러
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


private:
	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;
	EELLIE_STATUS m_Status = EELLIE_STATUS::None;
	float m_StateTime = 0.0f;


	// 키 조작
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	bool IsControl = true;

private:
	// 이동
	float4 m_MoveVector = float4::ZERO;
	float4 m_MoveForce = float4::ZERO;



	const float CONST_Ellie_NonRiding_Acceleration_Time = 1.0f;
	const float CONST_Ellie_Riding_Move_Acceleration_Time = 1.2f;
	const float CONST_Ellie_Riding_Boosting_Acceleration_Time = 1.0f;

	const float CONST_Ellie_SlowWalk_Speed = 120.0f;
	const float CONST_Ellie_Walk_Speed = 200.0f;
	const float CONST_Ellie_Run_Speed = 300.0f;

	const float CONST_Ellie_Riding_Move_Speed = 500.0f;
	const float CONST_Ellie_Riding_Boost_Speed = 700.0f;

private:
	// Pixel 충돌
	const float4 m_PixelCheckScale = { 20.0f , 10.0f };
	const float4 m_PixelCheckPosBaseOnCenter = { 0.0f , -27.0f };

	// Pixel 충돌 체크 포인트
	float4 m_PixelCheckTopLeft = float4::ZERO;
	float4 m_PixelCheckTopRight = float4::ZERO;
	float4 m_PixelCheckLeftTop = float4::ZERO;
	float4 m_PixelCheckLeftBottom = float4::ZERO;
	float4 m_PixelCheckRightTop = float4::ZERO;
	float4 m_PixelCheckRightBottom = float4::ZERO;
	float4 m_PixelCheckBottomLeft = float4::ZERO;
	float4 m_PixelCheckBottomRight = float4::ZERO;

	// 벽 마찰력
	const float COSNT_FrictionForce = 0.5f;

private:
	std::shared_ptr<GameEngineCollision> EllieCol = nullptr;
};

