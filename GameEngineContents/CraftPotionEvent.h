#pragma once
#include "SingleEvent.h"

// Ό³Έν :
class CraftPotionEvent : public SingleEvent
{
public:
	enum class ECRAFTPOTIONTOPIC
	{
		Find,
		None,
	};

public:
	// constrcuter destructer
	CraftPotionEvent();
	~CraftPotionEvent();

	// delete Function
	CraftPotionEvent(const CraftPotionEvent& _Other) = delete;
	CraftPotionEvent(CraftPotionEvent&& _Other) noexcept = delete;
	CraftPotionEvent& operator=(const CraftPotionEvent& _Other) = delete;
	CraftPotionEvent& operator=(CraftPotionEvent&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ConversationSetting() override;


};