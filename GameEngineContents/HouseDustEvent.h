#pragma once
#include "SingleEvent.h"

// Ό³Έν :
class HouseDustEvent : public SingleEvent
{
public:
	enum class EHOUSEDUSTSTATE
	{
		LookDust,
		None,
	};

	enum class EHOUSEDUSTTOPIC
	{
		LookDust,
		None,
	};

public:
	// constrcuter destructer
	HouseDustEvent();
	~HouseDustEvent();

	// delete Function
	HouseDustEvent(const HouseDustEvent& _Other) = delete;
	HouseDustEvent(HouseDustEvent&& _Other) noexcept = delete;
	HouseDustEvent& operator=(const HouseDustEvent& _Other) = delete;
	HouseDustEvent& operator=(HouseDustEvent&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ConversationSetting() override;

};