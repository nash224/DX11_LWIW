#pragma once
#include "StaticEntity.h"
#include "Conversation.h"

// Ό³Έν :
class InteractiveLetter : public StaticEntity
{
private:
	enum class ELETTERTOPICTYPE
	{
		StartTraining,
		None,
	};

	enum class ELETTERSTATE
	{
		Idle,
		Read,
		Disappear,
		None,
	};

public:
	// constrcuter destructer
	InteractiveLetter();
	~InteractiveLetter();

	// delete Function
	InteractiveLetter(const InteractiveLetter& _Other) = delete;
	InteractiveLetter(InteractiveLetter&& _Other) noexcept = delete;
	InteractiveLetter& operator=(const InteractiveLetter& _Other) = delete;
	InteractiveLetter& operator=(InteractiveLetter&& _Other) noexcept = delete;

	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void RendererSetting();
	void StateSetting();
	void ConversationSetting();

	void StartRead(GameEngineState* _Parent);
	void StartDisappear(GameEngineState* _Parent);

	void UpdateIdle(float _DeltaTime, GameEngineState* _Parent);



private:
	GameEngineState State;
	Conversation LetterConversation;
	std::shared_ptr<class UI_Frame> CutsceneFrame;
	

	static constexpr const float DisappearTime = 1.2f;
};