#pragma once
#include "DynamicEntity.h"
#include "ActorEnum.h"

constexpr float Ellie_Bias = 30.0f;


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
	Approach,
	Net,
	RootUp,
	Sit,
	MongSiri,
	Juicy,
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


struct PixelCheckPoint
{
public:
	float4 TopLeft = float4::ZERO;
	float4 TopRight = float4::ZERO;
	float4 LeftTop = float4::ZERO;
	float4 LeftBottom = float4::ZERO;
	float4 RightTop = float4::ZERO;
	float4 RightBottom = float4::ZERO;
	float4 BottomLeft = float4::ZERO;
	float4 BottomRight = float4::ZERO;

};


// 설명 : 주인공 앨리입니다. 
class Ellie : public DynamicEntity
{
public:
	static Ellie* MainEllie;

private:
	static EELLIE_STATUS g_Status;
	static bool FirstInitCheck;

public:
	// constrcuter destructer
	Ellie();
	~Ellie();

	// delete Function
	Ellie(const Ellie& _Other) = delete;
	Ellie(Ellie&& _Other) noexcept = delete;
	Ellie& operator=(const Ellie& _Other) = delete;
	Ellie& operator=(Ellie&& _Other) noexcept = delete;

	// 이니셜
	void Init();

	void OnControl();
	void OffControl();
	void SetPixelPointBaseOnCenter();


	EELLIE_STATE GetState() const
	{
		return m_State;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void OnLevelStart();
	void RenewStatus();
	void ChangeStatus(const EELLIE_STATUS _Status);

	void UpdateOutPutDebug(float _Delta);

private:
	void RendererSetting();
	void RideFxSetting();
	

	void CollisionSetting();

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Fx = nullptr;


private:
	void UpdateTestCode();

	// FSM
	void ChangeState(EELLIE_STATE _State);
	void UpdateState(float _Delta);
	void ChangeAnimationByDirection(std::string_view  _StateName, bool _DirectionInfluence = true, bool _Force =  false, unsigned int _Index = 0);
	void ChangeDirectionAnimation(std::string_view  _StateName);
	

	bool InputTestPattern();

	bool UsingTool();

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
	void OnRideFx();
	void UpdateRiding_Idle(float _Delta);

	void StartRiding_Move();
	void UpdateRiding_Move(float _Delta);

	void StartRiding_Boost();
	void UpdateRiding_Boost(float _Delta);

	void StartApproach();
	void UpdateApproach(float _Delta);
	void EndApproach();

	void StartNet();
	void UpdateNet(float _Delta);
	void NetCollision();
	void EndNet();

	void StartRootUp();
	void UpdateRootUp(float _Delta);
	void EndRootUp();

	void StartSit();
	void UpdateSit(float _Delta);
	void EndSit();

	void StartMongSiri();
	void UpdateMongSiri(float _Delta);
	void EndMongSiri();

	void StartJuicy();
	void UpdateJuicy(float _Delta);
	void EndJuicy();

	void StartCheer();
	void UpdateCheer(float _Delta);

	void StartFail();
	void UpdateFail(float _Delta);

	void StartDrink();
	void UpdateDrink(float _Delta);


private:
	// 방향 키 감지
	// 가능한 1프레임당 한번 업데이트 되는 것을 원칙으로 합니다.
	// 어차피 한번 실행하나 두번 실행하나 똑같습니다.
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// 방향 계산 함수
	float4 CalculateDirectionVectorToDir(const EDIRECTION _Direction);

	void CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce);
	EDIRECTION ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint);
	EDIRECTION ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(EDIRECTION _Dir, const float4& _MoveVector);


	float4 ReturnPostMoveVector(float _Delta, float _MAXMoveForce, float _Acceleration_Time);

	bool IsOverSpeed(float _CurSpeed, const float _MaxMoveForce);
	void DecelerateMoveVector(float _Delta, const float _MaxMoveForce, const float _DecelerationTime);
	void DecelerateAtMidpoint(float _Delta, const float _MaxMoveForce, const float _Time);
	void ApplyMovementToTransform(float _DElta);

private:
	// 방향키
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;

	bool IsControl = true;
	const float CONST_Ellie_SlowWalk_Speed = 100.0f;
	const float CONST_Ellie_Walk_Speed = 160.0f;
	const float CONST_Ellie_Run_Speed = 220.0f;

	const float CONST_Ellie_NonRiding_Acceleration_Time = 1.0f;
	const float CONST_Ellie_Riding_Move_Acceleration_Time = 1.2f;
	const float CONST_Ellie_Riding_Boosting_Acceleration_Time = 1.0f;
	const float CONST_Ellie_Riding_Move_Speed = 500.0f;
	const float CONST_Ellie_Riding_Boost_Speed = 700.0f;



private:
	// 충돌 업데이트
	void UpdateCollision();
	void UpdatePortalCollsiion();
	void UpdateInteractionCollsiion();

private:
	// Pixel 충돌
	const float4 m_PixelCheckScale = { 10.0f , 10.0f };
	const float4 m_PixelCheckPosBaseOnCenter = float4::ZERO;
	// 벽 마찰력
	const float COSNT_FrictionForce = 0.5f;

	// Pixel 충돌 체크 포인트
	PixelCheckPoint m_PixelCheckPoint;


private:
	std::shared_ptr<GameEngineCollision> m_EllieCol = nullptr;
	std::shared_ptr<GameEngineCollision> m_NetCol = nullptr;
	InteractiveActor* OtherEntity = nullptr;
	
	bool IsCollected = false;
	bool IsHolding = false;

	// 상호작용 Collision 시야각도 입니다.
	const float FOVAngle = 60.0f;

	
};

