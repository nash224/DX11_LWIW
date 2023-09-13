#pragma once
#include "InteractiveActor.h"
#include "ActorEnum.h"

constexpr float EllieIdleInter = 0.2f;
constexpr float EllieWalkSpeed = 200.0f;

constexpr float Ellie_Run_Inter = 0.1f;
constexpr float Ellie_Run_Speed = 300.0f;


constexpr float Ellie_ButterflyNet_Inter = 0.1f;

constexpr float Ellie_RootUp_Inter = 0.15f;

constexpr float Ellie_Sit_Inter = 0.12f;

constexpr float Ellie_MongSiri_Inter = 0.2f;

enum class EELLIE_STATE
{
	None,
	Idle,
	Walk,
	Run,
	Net,
	RootUp,
	Sit,
	MongSiri,
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


	void StartNet();
	void UpdateNet(float _Delta);

	void StartRootUp();
	void UpdateRootUp(float _Delta);

	void StartSit();
	void UpdateSit(float _Delta);

	void StartMongSiri();
	void UpdateMongSiri(float _Delta);


private:
	// ���� Ű ����
	// �ȵɰ� ������ 1�����Ӵ� �ѹ� ������Ʈ �Ǵ� ���� ��Ģ���� �մϴ�.
	// ������ �ѹ� �����ϳ� �ι� �����ϴ� �Ȱ����ϴ�.
	bool DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();

	// ���� ��� �Լ�
	float4 CalulateDirectionVectorToDir(const EDIRECTION _Direction);

private:
	// ������
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;


private:
	// �ൿ
	EELLIE_STATE m_State = EELLIE_STATE::None;
	float m_StateTime = 0.0f;


	// ���� Ű ����
	EDIRECTION m_Dir = EDIRECTION::LEFT;
	EDIRECTION m_RenderDir = EDIRECTION::CENTER;
	EHORIZONTAL_KEY_STATE m_HorizontalKey = EHORIZONTAL_KEY_STATE::Center;
	EVERTICAL_KEY_STATE m_VerticalKey = EVERTICAL_KEY_STATE::Center;

	bool IsControl = true;

private:
};

