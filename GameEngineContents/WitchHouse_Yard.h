#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class BackDrop_WitchHouse_Yard;
class WitchHouse_Yard : public PlayLevel
{
public:
	// constrcuter destructer
	WitchHouse_Yard();
	~WitchHouse_Yard();

	// delete Function
	WitchHouse_Yard(const WitchHouse_Yard& _Other) = delete;
	WitchHouse_Yard(WitchHouse_Yard&& _Other) noexcept = delete;
	WitchHouse_Yard& operator=(const WitchHouse_Yard& _Other) = delete;
	WitchHouse_Yard& operator=(WitchHouse_Yard&& _Other) noexcept = delete;

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
	void ReleaseSprite();
	void ReleaseTexture();


private:
	std::shared_ptr<BackDrop_WitchHouse_Yard> m_BackDrop = nullptr;
};

