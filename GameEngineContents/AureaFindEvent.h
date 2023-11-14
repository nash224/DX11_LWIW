#pragma once
#include "Conversation.h"

// Ό³Έν :
class AureaFindEvent : public GameEngineActor
{
public:
	class Aurea* AureaPtr = nullptr;

private:
	enum class ECURSEEVENTSTATE
	{
		FirstConversation,
		AureaFocusOn,
		Stay,
		AureaFocusOff,
		SecondConversation,
		None,
	};

	enum class ECURSEEVENTTOPIC
	{
		Look,
		Closer,
		None,
	};


public:
	// constrcuter destructer
	AureaFindEvent();
	~AureaFindEvent();

	// delete Function
	AureaFindEvent(const AureaFindEvent& _Other) = delete;
	AureaFindEvent(AureaFindEvent&& _Other) noexcept = delete;
	AureaFindEvent& operator=(const AureaFindEvent& _Other) = delete;
	AureaFindEvent& operator=(AureaFindEvent&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void StartFirstConversation(GameEngineState* _Parent);
	void StartAureaFocusOn(GameEngineState* _Parent);
	void StartSecondConversation(GameEngineState* _Parent);
	void StartAureaFocusOff(GameEngineState* _Parent);

	void UpdateAureaFocusOn(float _Delta, GameEngineState* _Parent);
	void UpdateStay(float _Delta, GameEngineState* _Parent);
	void UpdateAureaFocusOff(float _Delta, GameEngineState* _Parent);


	float CalculateDistanceCamemeraToActor(const float4& _Position);


	void StateSetting();
	void ConversationSetting();

	void ConverseWithEllie();

private:
	GameEngineState State;
	Conversation VirgilConveration;

	float4 CameraDirection = float4::ZERO;
	float4 TargetPos = float4::ZERO;

	static constexpr const float CameraMovePower = 300.0f;

};

