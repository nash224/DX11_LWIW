#pragma once
#include "ContentsLevel.h"

// Ό³Έν :
class BackDrop_Loading;
class LoadingLevel : public ContentsLevel
{
public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


public:


private:
	void LoadTexture();
	void LoadSprite();
	void LoadActor();
	void LoadItemInfo();
	
private:
	void ActorRelease();
	void ReleaseSprite();
	void ReleaseTexture();


private:
	std::shared_ptr<BackDrop_Loading> m_BackDrop = nullptr;

	bool GlobalTextureLoadCheck = false;
	bool GlobalSpriteLoadCheck = false;

};

