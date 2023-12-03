#pragma once
#include "DynamicEntity.h"
#include "AnimationHelper.h"


static constexpr const float MAX_STAMINA = 1000.0f;
static constexpr const float MAX_FUEL = 1000.0f;


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
	Lift,
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
private:
	static EELLIE_STATUS g_Status;
	static int Day;
	static float Stamina;
	static float BroomFuel;
	static bool FirstInitCheck;

	static FrameAnimationHelper ShadowRendererHelper;
	static FrameAnimationHelper VirgilRendererHelper;
	static FrameAnimationHelper BroomHeadRendererHelper;
	static FrameAnimationHelper BroomBodyRendererHelper;

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

		float TransitionCoolDown = 0.0f;
		static constexpr const float Transition_Recovery_Time = 0.4f;

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

	void SetLocalPosition(const float4& _Pos);
	void AddLocalPosition(const float4& _Pos);
	void OnControl();
	void OffControl();
	void FinishWork();
	void WaitDone(EELLIE_STATE _State);
	void SetAnimationByDirection(EDIRECTION _Dir = EDIRECTION::CENTER);

	EELLIE_STATE GetState() const
	{
		return State;
	}

	float GetStamina() const
	{
		return Stamina;
	}

	float GetBroomFuel() const
	{
		return BroomFuel;
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
	void SetPixelPointBaseOnCenter();

	void OnLevelStart();
	
	void ChangeFrameAnimationInterAllDirection(std::string_view _AnimationName, const std::vector<float>& _Inter);
	void ChangeShawdowSprite(std::string_view _AnimationName);
	void ChangeVirgilSprite(std::string_view _AnimationName);
	void ChangeBroomSprite();


	void RenewStatus();
	void ChangeStatus(const EELLIE_STATUS _Status);

private:
	void UpdateCollision();
	void UpdatePortalCollsiion();
	void UpdateInteractionCollsiion();
	void CheckNetCollision();

	bool IsInSight(float _AngleToObject, float _LeftFov, float _RightFov);

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
	void StartLift();
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
	void UpdateLift(float _Delta);
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


	bool UsingTool();
	bool InputRidingMode();

	void SitShadowUpdate();

	// FX
	void OnRideFx();
	void UpdateCoolTime(float _Delta);
	void GenerateBroomDust(float _Delta);
	void GenerateBoostBroomDust(float _Delta);
	void CreateBroomParticle(float _ParticleDistance = 0.0f);
	float4 GetBroomParticlePosition(float _ParticleDistance); 
	bool ChecckCollideWall();

	void ConsumeBroomFuel(float _Delta);

	// Input
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	
	void CalulationMoveForceToNormalStatus(float _Delta, float _MAXMoveForce);
	EDIRECTION ReturnDirectionCheckBothSide(EDIRECTION _Direction, const float4& _LeftCheckPoint, const float4& _RightCheckPoint);

	// Move & WallCollision
	void DecelerateNotDir(float _Delta, const float _MaxMoveForce);
	float4 GetMoveForceByDir(float _Delta, float _MAXMoveForce, float _Acceleration_Time);
	void LimitMoveVector(float _MAXMoveForce);
	bool WallCollision();

	// DayChange Event
	void DayChangeEvent();
	void CheckDayChange();

private:
	EHORIZONTAL_KEY_STATE HorizontalInputKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE VerticalInputKey = EVERTICAL_KEY_STATE::Center;

	EELLIE_STATE State = EELLIE_STATE::None;
	EELLIE_STATE WaitState = EELLIE_STATE::None;

	EllieBroom Broom;
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> EllieFxRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> VirgilRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> EllieCol = nullptr;
	std::shared_ptr<GameEngineCollision> NetCollision = nullptr;
	InteractiveActor* OtherEntity = nullptr;
	PixelCheckPoint CheckPoint;

	
	float StateTime = 0.0f;
	float CoolTime = 0.0f;
	float Broom_Particle_Time = 0.0f;
	float BroomUsingTime = 0.0f;

	bool isFinishWork = false;
	bool isDoneCollect = false;
	bool isHolding = false;
	bool isWaitDone = false;
	bool isRootup = false;
	bool isPull = false;


	static constexpr const float LWIW_Ellie_Y_Correction = 30.0f;
	
	static constexpr float SlowWalk_Speed = 100.0f;
	static constexpr float Walk_Speed = 160.0f;
	static constexpr float Run_Speed = 220.0f;
	static constexpr float Riding_Move_Acceleration_Time = 0.8f;
	static constexpr float Riding_Boost_Acceleration_Time = 0.8f;
	static constexpr float Riding_Move_Speed = 270.0f;
	static constexpr float Riding_Boost_Speed = 330.0f;

	static constexpr const float FOVAngle = 60.0f;
	static constexpr const float FrictionForce = 0.5f;


};