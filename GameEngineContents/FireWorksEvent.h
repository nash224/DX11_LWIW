#pragma once
#include "Conversation.h"

// Ό³Έν :
class FireWorksEvent : public GameEngineActor
{
private:
	enum class EFIREWORKSSTATE
	{
		FadeIn,
		ReadyConversation,
		PotionSetting,
		Fire,
		FireWorks,
		LastConversation,
		FadeOut,
		None,
	};

	enum class EFIREWORKSEVENTTOPIC
	{
		Ready,
		Last,
		None,
	};

public:
	// constrcuter destructer
	FireWorksEvent();
	~FireWorksEvent();

	// delete Function
	FireWorksEvent(const FireWorksEvent& _Other) = delete;
	FireWorksEvent(FireWorksEvent&& _Other) noexcept = delete;
	FireWorksEvent& operator=(const FireWorksEvent& _Other) = delete;
	FireWorksEvent& operator=(FireWorksEvent&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void PotionSetting();
	void ConversationSetting();
	void StateSetting();

	void StartFadeIn(GameEngineState* _Parent);
	void UpdateFadeIn(float _Delta, GameEngineState* _Parent);\

	void StartReadyConversation(GameEngineState* _Parent);

	void StartPotionSetting(GameEngineState* _Parent);
	void UpdatePotionSetting(float _Delta, GameEngineState* _Parent);

	void StartFire(GameEngineState* _Parent);
	void UpdateFire(float _Delta, GameEngineState* _Parent);
	void EndFire(GameEngineState* _Parent);

	void UpdateFireWorks(float _Delta, GameEngineState* _Parent);

	void StartLastConversation(GameEngineState* _Parent);

	void StartFadeOut(GameEngineState* _Parent);

private:
	Conversation EventConversation;

	GameEngineState State;

	static constexpr float LastFadeTime = 1.2f;

};

