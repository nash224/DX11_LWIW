#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class EndLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	EndLevel();
	~EndLevel();

	// delete Function
	EndLevel(const EndLevel& _Other) = delete;
	EndLevel(EndLevel&& _Other) noexcept = delete;
	EndLevel& operator=(const EndLevel& _Other) = delete;
	EndLevel& operator=(EndLevel&& _Other) noexcept = delete;




protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void Init();
	void ResLoad();
	void ResRelease();
	void PlayEndingBGM();

private:
	GameEngineSoundPlayer BGMPlayer;

};

