#pragma once
#include "InteractiveActor.h"

enum class ELIFTDIR
{
	Up,
	Down,
	None,
};

struct LiftStruct
{
	friend class BaseLift;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Lift;
	std::shared_ptr<GameEngineSpriteRenderer> Pattern;

};

// Ό³Έν :
class BaseLift : public InteractiveActor
{
	friend class Ellie;

public:
	static std::weak_ptr<BaseLift> MainLiftPtr;
	static bool isEnable;

private:
	enum class ELIFTSTATE
	{
		Disable,
		Ready,
		Enter,
		Arrive,
	};

public:
	// constrcuter destructer
	BaseLift();
	~BaseLift();

	// delete Function
	BaseLift(const BaseLift& _Other) = delete;
	BaseLift(BaseLift&& _Other) noexcept = delete;
	BaseLift& operator=(const BaseLift& _Other) = delete;
	BaseLift& operator=(BaseLift&& _Other) noexcept = delete;

	virtual void Init();
	void ActiveEv();
	void LiftToArrive();
	void EnableEv();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void LiftSetting();
	void StateSetting();

	// Start
	void StartReady(GameEngineState* _Parent);
	virtual void StartEnter(GameEngineState* _Parent);
	virtual void StartArrive(GameEngineState* _Parent);

	// Update
	void UpdateEnter(float _Delta, GameEngineState* _Parent);
	void UpdateArrive(float _Delta, GameEngineState* _Parent);

	// End
	virtual void EndEnter(GameEngineState* _Parent);
	virtual void EndArrive(GameEngineState* _Parent);

	void AddSpeed(float _Delta, float _Speed);
	void MoveEv(float _Delta, ELIFTDIR _LiftType);
	void SetEv(ELIFTDIR _LiftType);

	void AppearLift();
	void DisappearLift();

protected:
	static constexpr float AccelerationTime = 0.6f;
	static constexpr float MaxSpeed = 40.0f;
	const float EnterDistance = 30.0f;
	const float ArriveStartDistance = 60.0f;
	float LiftSpeed = 0.0f;
	float4 LiftArrivePoint = float4::ZERO;
	std::string ChangeLevelName;
	ELIFTDIR EnterType = ELIFTDIR::Up;
	ELIFTDIR ArriveType = ELIFTDIR::Down;

private:
	GameEngineState State;
	LiftStruct Lift;

	bool isChangeLevel = false;
	bool isArriveInit = false;

};

