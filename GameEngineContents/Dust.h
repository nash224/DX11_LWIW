#pragma once
#include "InteractiveActor.h"
#include "Conversation.h"

// Ό³Έν :
class Dust : public InteractiveActor
{
	enum class EDUSTSTATE
	{
		Idle,
		Remove,
		Converse,
		None,
	};
	
protected:
	enum class EDUSTTOPICTYPE
	{
		About,
		None,
	};

public:
	// constrcuter destructer
	Dust();
	~Dust();

	// delete Function
	Dust(const Dust& _Other) = delete;
	Dust(Dust&& _Other) noexcept = delete;
	Dust& operator=(const Dust& _Other) = delete;
	Dust& operator=(Dust&& _Other) noexcept = delete;

	void Init(std::string_view _DustSpriteName, bool _isGroundDust = false);
	void AddDepth(float _PlusDepth);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void SetConversationData(const std::vector<ConversationData>& _ConversationDatas);
	void SetStartEvent(std::function<void()> _StartEvent);
	void SetEndEvnet(std::function<void()> _EndEvent);

	inline void SetDustScaleRatio(float _ScaleRatio)
	{
		DustScaleRatio = _ScaleRatio;
	}

private:

	void RendererSetting(std::string_view _DustSpriteName);
	void StateSetting();
	void ConversationSetting();

	void StartRemove(GameEngineState* _Parent);
	void StartConverse(GameEngineState* _Parent);

	void UpdateIdle(float _DeltaTime, GameEngineState* _Parent);
	void UpdateRemove(float _DeltaTime, GameEngineState* _Parent);

	void EndConverse(GameEngineState* _Parent);

private:
	GameEngineState State;
	Conversation AboutConversation;
	std::vector<ConversationData> ConversationDatas;

	std::function<void()> StartEvent;
	std::function<void()> EndEvent;

	float DustScaleRatio = 1.0f;

};

