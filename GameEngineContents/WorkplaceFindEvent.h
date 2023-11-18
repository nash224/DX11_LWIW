#pragma once
#include "SingleEvent.h"

// Ό³Έν :
class WorkplaceFindEvent : public SingleEvent
{
public:
	enum class EWORKPLACEFINDTOPIC
	{
		Find,
		None,
	};

public:
	// constrcuter destructer
	WorkplaceFindEvent();
	~WorkplaceFindEvent();

	// delete Function
	WorkplaceFindEvent(const WorkplaceFindEvent& _Other) = delete;
	WorkplaceFindEvent(WorkplaceFindEvent&& _Other) noexcept = delete;
	WorkplaceFindEvent& operator=(const WorkplaceFindEvent& _Other) = delete;
	WorkplaceFindEvent& operator=(WorkplaceFindEvent&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ConversationSetting() override;

};