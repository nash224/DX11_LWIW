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
		FireWorks,
		LastConversation,
		EndTraining,
		FadeOut,
		None,
	};

	enum class EFIREWORKSEVENTTOPIC
	{
		Ready,
		Last,
		None,
	};

private:
	class FarsightedScenryStruct
	{
		friend class FireWorksEvent;

	public:
		void RendererSetting(GameEngineActor* _Actor);
		void Release();

	private:
		std::shared_ptr<GameEngineSpriteRenderer> SkyRenderer;
		std::shared_ptr<GameEngineSpriteRenderer> GroundRenderer;
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>> StarRenderers;

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
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


	void PotionSetting();
	void ConversationSetting();

	///////
	// State
	void StateSetting();

	// State::Start
	void StartFadeIn(GameEngineState* _Parent);
	void StartReadyConversation(GameEngineState* _Parent);
	void StartFireWorks(GameEngineState* _Parent);
	void StartLastConversation(GameEngineState* _Parent);
	void StartEndTraining(GameEngineState* _Parent);
	void StartFadeOut(GameEngineState* _Parent);

	// State::Update
	void UpdateFadeIn(float _Delta, GameEngineState* _Parent);\
	void UpdateFireWorks(float _Delta, GameEngineState* _Parent);
	void UpdateEndTraining(float _Delta, GameEngineState* _Parent);


	void SetElliePlacement() const;
	void CheckEndtrainingEvent();

private:
	FarsightedScenryStruct SceneryInfo;
	Conversation EventConversation;

	GameEngineState State;
	float StateTime = 0.0f;

	std::shared_ptr<class FireWorks> CrackerPotion;

	static constexpr float LastFadeTime = 1.2f;


};

