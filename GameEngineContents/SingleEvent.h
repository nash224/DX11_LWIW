#pragma once
#include "Conversation.h"

// Ό³Έν :
class SingleEvent : public GameEngineActor
{
protected:
	enum class ESINGLESTATE
	{
		Single,
		None,
	};

public:
	// constrcuter destructer
	SingleEvent();
	~SingleEvent();

	// delete Function
	SingleEvent(const SingleEvent& _Other) = delete;
	SingleEvent(SingleEvent&& _Other) noexcept = delete;
	SingleEvent& operator=(const SingleEvent& _Other) = delete;
	SingleEvent& operator=(SingleEvent&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void ConversationDone();

private:
	virtual void ConversationSetting() = 0;
	void StateSetting();

	void StartEvent(GameEngineState* _Parent);
	void EndEvent(GameEngineState* _Parent);

protected:
	GameEngineState State;
	Conversation EventConveration;


};