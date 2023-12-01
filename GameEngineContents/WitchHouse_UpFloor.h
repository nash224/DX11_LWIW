#pragma once
#include "PlayLevel.h"


// Ό³Έν :
class BackDrop_WitchHouse_UpFloor;
class WitchHouse_UpFloor : public PlayLevel
{
public:
	// constrcuter destructer
	WitchHouse_UpFloor();
	~WitchHouse_UpFloor();

	// delete Function
	WitchHouse_UpFloor(const WitchHouse_UpFloor& _Other) = delete;
	WitchHouse_UpFloor(WitchHouse_UpFloor&& _Other) noexcept = delete;
	WitchHouse_UpFloor& operator=(const WitchHouse_UpFloor& _Other) = delete;
	WitchHouse_UpFloor& operator=(WitchHouse_UpFloor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void LoadTexture();

	void SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel);

	void ReleaseTexture();

	void AutoPlayBGM();

};

