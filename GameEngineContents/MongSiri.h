#pragma once
#include "InteractiveActor.h"
#include "AnimationHelper.h"
#include "Emoji.h"


enum class EMONGSIRISTATUS
{
	Normal,
	Escape,
	Look,
	None,
};

// Ό³Έν :
class MongSiri : public InteractiveActor
{
	friend class Ellie;
	friend class MongSiri_Population;

private:
	static FrameAnimationHelper ShadowRenderHelper;

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

	void GetCaught() override;

private:
	void ChangeAnimation(std::string_view _StateName);
	void ChangeAnimationByDircetion(std::string_view _StateName, unsigned int _Index = 0);
	void AutoChangeDirAnimation(std::string_view _StateName);

	void UpdateState(float _Delta);
	void ChangeState(EMONGSIRISTATE _State);

	// Start
	void StartIdle();
	void StartJump();
	void StartLook();
	void StartRecognize(GameEngineState* _Parent);
	void StartCaught();
	void StartCollected();
	void StartDisappear();

	// Update
	void UpdateIdle(float _Delta);
	void UpdateJump(float _Delta);
	void UpdateLook(float _Delta);
	void UpdateRecognize(float _Delta, GameEngineState* _Parent);
	void UpdateNotRecognize(float _Delta, GameEngineState* _Parent);
	void UpdateCaught(float _Delta);
	void UpdateCollected(float _Delta);
	void UpdateDisappear(float _Delta);

	// End
	void EndIdle();
	void EndJump();
	void EndNotRecognize(GameEngineState* _Parent);
	void EndCollected();

	void SearchJumpLocation();
	void ShowEscapeEmotion();

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;
	
	GameEngineState LookState;

	EMONGSIRISTATE State = EMONGSIRISTATE::None;
	EMONGSIRISTATUS Status = EMONGSIRISTATUS::None;

	EDIRECTION RenderDir = EDIRECTION::CENTER;

	Emoji Emotion;

	float4 TargetForce = float4::ZERO;

	int IdleCount = 0;
	bool IsOnTheHole = false;


	static constexpr float MongSiri_JumpMinSpeed = 0.0f;
	static constexpr float MongSiri_JumpMaxSpeed = 60.0f;

};