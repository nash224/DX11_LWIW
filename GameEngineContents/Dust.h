#pragma once
#include "StaticEntity.h"
#include "Conversation.h"

// Ό³Έν :
class Dust : public StaticEntity
{
	enum class EDUSTTOPICTYPE
	{
		About,
		None,
	};

	enum class EDUSTSTATE
	{
		Idle,
		Remove,
		Converse,
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

	void Init(std::string_view _DustSpriteName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	virtual void SetConversationData();

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

	static constexpr const float RemoveDustTime = 1.2f;

};

