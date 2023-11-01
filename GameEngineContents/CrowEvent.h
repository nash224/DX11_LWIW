#pragma once
#include "Conversation.h"


// Ό³Έν :
class CrowEvent : public GameEngineActor
{
public:
	enum class ECROWSTATE
	{
		EventStart,
		Idle,
		Disappear,
		None,
	};

	enum class ECROWTOPIC
	{
		Crow,
		Disappear,
	};


public:
	// constrcuter destructer
	CrowEvent();
	~CrowEvent();

	// delete Function
	CrowEvent(const CrowEvent& _Other) = delete;
	CrowEvent(CrowEvent&& _Other) noexcept = delete;
	CrowEvent& operator=(const CrowEvent& _Other) = delete;
	CrowEvent& operator=(CrowEvent&& _Other) noexcept = delete;

	void Init();


protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void RendererSetting();
	void StateSetting();
	void ConversationSetting();

	void UpdateEventStart(float _DeltaTime, GameEngineState* _Parent);
	void UpdateIdle(float _DeltaTime, GameEngineState* _Parent);
	void UpdateDisappear(float _DeltaTime, GameEngineState* _Parent);

	void ConverseWithEllie();

private:
	std::shared_ptr<GameEngineSpriteRenderer> CrowRenderer;
	GameEngineState State;
	Conversation CrowConveration;

	float StateTime = 0.0f;

	static constexpr const float Caw_Wait_Time = 2.0f;
	static constexpr const float Caw_CoolTime = 5.0f;

	static constexpr const float Caw_Animation_Inter = 0.12f;
	static constexpr const float Disappear_Animation_Inter = 0.16f;
};