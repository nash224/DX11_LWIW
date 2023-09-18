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


// ���� : ���ΰ� �ٸ��Դϴ�. 
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
	// �̴ϼ�
	void Init();
	void SetSpawnLocalPosition(const float4& _Position);
	void SetMoveControl(bool _Value);
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
	// ���� Ű ����
	// �ȵɰ� ������ 1�����Ӵ� �ѹ� ������Ʈ �Ǵ� ���� ��Ģ���� �մϴ�.
	// ������ �ѹ� �����ϳ� �ι� �����ϴ� �Ȱ����ϴ�.
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// ���� ��� �Լ�
	float4 CalulateDirectionVectorToDir(const EDIRECTION _Direction);


	void CalculateMoveForce(float _Delta, float _MAXMoveForce, float _Acceleration_Time);
	bool IsOverSpeed(float _CurSpeed, const float _MaxMoveForce);
	void DecelerateAtMidpoint(float _Delta, const float _MaxMoveForce, const float _Time);
	void ApplyMovementToTransform(float _DElta);
	


private:
	void UpdateCollision();


private:
	// ������
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


private:
	// �ൿ
	EELLIE_STATE m_State = EELLIE_STATE::None;
	EELLIE_STATUS m_Status = EELLIE_STATUS::None;
	float m_StateTime = 0.0f;


	// Ű ����
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	bool IsControl = true;

private:
	// �̵�
	float4 m_MoveVector = float4::ZERO;
	float4 m_MoveForce = float4::ZERO;

	const float CONST_Ellie_NonRiding_Acceleration_Time = 0.1f;
	const float CONST_Ellie_Riding_Move_Acceleration_Time = 1.2f;
	const float CONST_Ellie_Riding_Boosting_Acceleration_Time = 1.0f;

private:
	const float CONST_Ellie_SlowWalk_Speed = 120.0f;
	const float CONST_Ellie_Walk_Speed = 200.0f;
	const float CONST_Ellie_Run_Speed = 300.0f;

	const float CONST_Ellie_Riding_Move_Speed = 500.0f;
	const float CONST_Ellie_Riding_Boost_Speed = 700.0f;


private:
	std::shared_ptr<GameEngineCollision> EllieCol = nullptr;
};

