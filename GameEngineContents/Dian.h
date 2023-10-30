#pragma once
#include "NPCEntity.h"

#include "Conversation.h"

// Ό³Έν :
class Dian : public NPCEntity
{
public:
	enum class EDIANTOPICTYPE
	{
		Hello,
		None,
	};

	enum class EDIANSTATE
	{
		Normal,
		None,
	};

public:
	// constrcuter destructer
	Dian();
	~Dian();

	// delete Function
	Dian(const Dian& _Other) = delete;
	Dian(Dian&& _Other) noexcept = delete;
	Dian& operator=(const Dian& _Other) = delete;
	Dian& operator=(Dian&& _Other) noexcept = delete;

	void Init();

	

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void StateSetting();
	void ConversationSetting();
	void NormalUpdate(float _DeltaTime, GameEngineState* _Parent);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;
	
	GameEngineState State;

	static constexpr const float RendererYCorrection = 30.0f;

};

