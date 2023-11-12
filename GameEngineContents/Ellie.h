#pragma once
#include "DynamicEntity.h"
#include "ActorEnum.h"


constexpr float CheckPointGap = 2.0f;
constexpr float FOVAngle = 60.0f;
constexpr float FrictionForce = 0.5f;
static constexpr const float LWIW_Ellie_Y_Correction = 30.0f;

constexpr float EllieIdleInter = 0.2f;
constexpr float Ellie_SlowWalk_Inter = 0.2f;
constexpr float Ellie_Run_Inter = 0.1f;
constexpr float Ellie_Throw_Inter = 0.1f;
constexpr float Ellie_Riding_Idle_Inter = 0.1f;
constexpr float Ellie_Riding_Move_Inter = 0.1f;
constexpr float Ellie_Riding_Boost_Inter = 0.1f;
constexpr float Ellie_ButterflyNet_Inter = 0.1f;
constexpr float Ellie_RootUp_Inter = 0.12f;
constexpr float Ellie_Sit_Inter = 0.12f;
constexpr float Ellie_MongSiri_Inter = 0.2f;

constexpr float CONST_Ellie_SlowWalk_Speed = 100.0f;
constexpr float CONST_Ellie_Walk_Speed = 160.0f;
constexpr float CONST_Ellie_Run_Speed = 220.0f;
constexpr float CONST_Ellie_NonRiding_Acceleration_Time = 1.0f;
constexpr float CONST_Ellie_Riding_Move_Acceleration_Time = 1.2f;
constexpr float CONST_Ellie_Riding_Boosting_Acceleration_Time = 1.0f;
constexpr float CONST_Ellie_Riding_Move_Speed = 500.0f;
constexpr float CONST_Ellie_Riding_Boost_Speed = 700.0f;


enum class EELLIE_STATE
{
	None,
	Idle,
	SlowWalk,
	Walk,
	Run,
	Throw,
	Riding_Standing,
	Riding_Moving,
	Riding_Boosting,
	Approach,
	ButterflyNet,
	RootUp,
	Sit,
	MongSiri,
	Wait,
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

private:
	class EllieBroom
	{
	public:
		enum class EBROOMSTRUCT
		{
			Head,
			Body,
			Max,
		};

	public:
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BroomRenderer;

	};


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
	void FinishWork();
	void WaitDone(EELLIE_STATE _State);
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

	void RendererSetting();
	void VirgilSetting();
	void BroomSetting();
	void CollisionSetting();

	void ChangeBroomAndVirgilIndexToRidingMode(int _HeadIndex, int _BodyIndex, int _VirgilIndex);

	void ChangeFrameAnimationInterAllDirection(std::string_view _AnimationName, const std::vector<float>& _Inter);
	void ChangeShawdowSprite(std::string_view _AnimationName);
	void ChangeVirgilSprite(std::string_view _AnimationName);
	void ChangeBroomSprite();


	// 레벨 시작 초기화 함수
	void OnLevelStart();
	void RenewStatus();
	void ChangeStatus(const EELLIE_STATUS _Status);

private:
	void UpdateCollision();
	void UpdatePortalCollsiion();
	void UpdateInteractionCollsiion();
	void NetCollision();

	void UpdateTestCode();

	// FSM
	void ChangeState(EELLIE_STATE _State);
	void UpdateState(float _Delta);
	void ChangeAnimationByDirection(std::string_view  _StateName, bool _DirectionInfluence = true, bool _Force =  false, unsigned int _Index = 0);
	void ChangeDirectionAnimation(std::string_view  _StateName);
	

	void StartIdle();
	void StartSlowWalk();
	void StartWalk();
	void StartRun();
	void StartThrow();
	void StartRiding_Standing();
	void StartRiding_Moving();
	void StartRiding_Boosting();
	void StartApproach();
	void StartButterflyNet();
	void StartRootUp();
	void StartSit();
	void StartMongSiri();
	void StartWait();
	void StartJuicy();
	void StartCheer();
	void StartFail();
	void StartDrink();


	void UpdateIdle(float _Delta);
	void UpdateSlowWalk(float _Delta);
	void UpdateWalk(float _Delta);
	void UpdateRun(float _Delta);
	void UpdateThrow(float _Delta);
	void UpdateRiding_Standing(float _Delta);
	void UpdateRiding_Moving(float _Delta);
	void UpdateRiding_Boosting(float _Delta);
	void UpdateApproach(float _Delta);
	void UpdateButterflyNet(float _Delta);
	void UpdateRootUp(float _Delta);
	void UpdateSit(float _Delta);
	void UpdateMongSiri(float _Delta);
	void UpdateWait(float _Delta);
	void UpdateJuicy(float _Delta);
	void UpdateCheer(float _Delta);
	void UpdateFail(float _Delta);
	void UpdateDrink(float _Delta);


	void EndIdle();
	void EndApproach();
	void EndButterflyNet();
	void EndRootUp();
	void EndSit();
	void EndMongSiri();
	void EndWait();
	void EndJuicy();


	bool InputTestPattern();


	bool UsingTool();

	void SitShadowUpdate();

	void OnRideFx();
	void GenerateBroomParticle();
	float4 GetBroomParticlePosition();

private:
	// 방향 키 감지
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

	void PlaySFX(std::string_view _FileName);

private:
	// 방향키
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	// 행동
	EELLIE_STATE m_State = EELLIE_STATE::None;
	EELLIE_STATE m_WaitState = EELLIE_STATE::None;

	EllieBroom Broom;
	std::shared_ptr<GameEngineSpriteRenderer> Shadow = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> EllieFx = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Virgil = nullptr;
	std::shared_ptr<GameEngineCollision> m_EllieCol = nullptr;
	std::shared_ptr<GameEngineCollision> m_NetCol = nullptr;
	InteractiveActor* OtherEntity = nullptr;
	PixelCheckPoint m_PixelCheckPoint;

	const float4 m_PixelCheckScale = { 10.0f , 10.0f };
	const float4 m_PixelCheckPosBaseOnCenter = float4::ZERO;

	float Broom_Particle_Time = 0.0f;

	bool isFinishWork = false;
	bool IsControl = true;
	bool IsCollected = false;
	bool IsHolding = false;
	bool IsWaitDone = false;
	bool isRootup = false;

	static constexpr const float Broom_Particle_Cool_Down = 0.08f;

	static constexpr const float Shadow_Renderer_Y_Correction = 30.0f;
	
};

