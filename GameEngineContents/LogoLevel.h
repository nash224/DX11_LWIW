#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class LogoLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	LogoLevel();
	~LogoLevel();

	// delete Function
	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void LoadTexture();
	void LoadSprite();
	void LoadActor();

	void UpdateFade(float _Delta);

	void ReleaseSprite();
	void ReleaseTexture();


private:
	bool GlobalTextureLoadCheck = false;
	bool GlobalSpriteLoadCheck = false;

	float AccTime = 0.0f;
	bool IsFadeOn = false;
};

