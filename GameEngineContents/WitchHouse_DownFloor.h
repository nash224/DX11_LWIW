#pragma once
#include "PlayLevel.h"


// Ό³Έν :
class BackDrop_WitchHouse_DownFloor;
class WitchHouse_DownFloor : public PlayLevel
{
public:
	// constrcuter destructer
	WitchHouse_DownFloor();
	~WitchHouse_DownFloor();

	// delete Function
	WitchHouse_DownFloor(const WitchHouse_DownFloor& _Other) = delete;
	WitchHouse_DownFloor(WitchHouse_DownFloor&& _Other) noexcept = delete;
	WitchHouse_DownFloor& operator=(const WitchHouse_DownFloor& _Other) = delete;
	WitchHouse_DownFloor& operator=(WitchHouse_DownFloor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void LoadTexture();
	void LoadSprite();
	void LoadActor();

	void SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel);
	void CameraSetting();

private:


private:
	void LevelActorRelease();
	void ReleaseSprite();
	void ReleaseTexture();


private:
	std::shared_ptr<BackDrop_WitchHouse_DownFloor> m_BackDrop = nullptr;

};

