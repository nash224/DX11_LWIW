#pragma once
#include "SingleEvent.h"

// Ό³Έν :
class CraftFireCrackerEvent : public SingleEvent
{
private:
	enum class ECRAFTTOPIC
	{
		Finally,
		None,
	};

public:
	// constrcuter destructer
	CraftFireCrackerEvent();
	~CraftFireCrackerEvent();

	// delete Function
	CraftFireCrackerEvent(const CraftFireCrackerEvent& _Other) = delete;
	CraftFireCrackerEvent(CraftFireCrackerEvent&& _Other) noexcept = delete;
	CraftFireCrackerEvent& operator=(const CraftFireCrackerEvent& _Other) = delete;
	CraftFireCrackerEvent& operator=(CraftFireCrackerEvent&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ConversationSetting() override;


};

