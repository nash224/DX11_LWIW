#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class DreamLevel : public ContentsLevel
{
private:
	enum class EDREAMSTATE
	{
		Stay,
		None,
	};

public:
	// constrcuter destructer
	DreamLevel();
	~DreamLevel();

	// delete Function
	DreamLevel(const DreamLevel& _Other) = delete;
	DreamLevel(DreamLevel&& _Other) noexcept = delete;
	DreamLevel& operator=(const DreamLevel& _Other) = delete;
	DreamLevel& operator=(DreamLevel&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();
	void StateSetting();

	void EndStay(GameEngineState* _Parent);
	void UpdateStay(float _Delta, GameEngineState* _Parent);

	void ResLoad();
	void ResRelease();

private:
	GameEngineSoundPlayer BGMPlayer;

	GameEngineState State;

};

