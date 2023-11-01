#pragma once
#include "StaticEntity.h"
#include "Conversation.h"

// Ό³Έν :
class NPCEntity : public InteractiveActor
{
public:
	// constrcuter destructer
	NPCEntity();
	~NPCEntity();

	// delete Function
	NPCEntity(const NPCEntity& _Other) = delete;
	NPCEntity(NPCEntity&& _Other) noexcept = delete;
	NPCEntity& operator=(const NPCEntity& _Other) = delete;
	NPCEntity& operator=(NPCEntity&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


	template<typename TopicType>
	void InteractWithEllie(TopicType _Topic)
	{
		InteractWithEllie(static_cast<int>(_Topic));
	}

	void InteractWithEllie(int _Topic);


protected:
	Conversation NPCConversation;

};

