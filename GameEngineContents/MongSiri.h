#pragma once
#include "DynamicEntity.h"
#include "Emoji.h"


enum class EMONGSIRISTATUS
{
	Normal,
	Escape,
	Look,
	None,
};


// Ό³Έν :
class MongSiri : public DynamicEntity
{
	friend class Ellie;
	friend class MongSiri_Population;

private:
	class MongSiri_Population* MongSiriParant = nullptr;

private:
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

	enum class ELOOKSTATE
	{
		Recognize,
		NotRecognize,
		None,
	};

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
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void RendererSetting();
	void LookStateSetting();
	void InitDirection();

private:
	void ChangeAnimation(std::string_view _StateName);
	void ChangeAnimationByDircetion(std::string_view _StateName, unsigned int _Index = 0);
	void AutoChangeDirAnimation(std::string_view _StateName);

	bool IsPlayerAround();

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

	void StartRecognize(GameEngineState* _Parent);
	void UpdateRecognize(float _Delta, GameEngineState* _Parent);

	void StartNotRecognize(GameEngineState* _Parent);
	void UpdateNotRecognize(float _Delta, GameEngineState* _Parent);
	void EndNotRecognize(GameEngineState* _Parent);

	void GetCaught() override;
	void StartCaught();
	void UpdateCaught(float _Delta);


	void StartCollected();
	void UpdateCollected(float _Delta);
	void EndCollected();

	void StartDisappear();
	void UpdateDisappear(float _Delta);

	void ShowEscapeEmotion();

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;

	GameEngineState LookState;

	EMONGSIRISTATE m_State = EMONGSIRISTATE::None;
	EMONGSIRISTATUS Status = EMONGSIRISTATUS::None;

	EDIRECTION RenderDir = EDIRECTION::CENTER;

	Emoji Emotion;

	float4 TargetForce = float4::ZERO;

	int IdleCount = 0;
	bool IsOnTheHole = false;
	static constexpr float MongSiri_FOVSize = 90.0f;


	static constexpr float MongSiri_JumpMinSpeed = 0.0f;
	static constexpr float MongSiri_JumpMaxSpeed = 60.0f;

};


