#pragma once
#include "BackDrop_PlayLevel.h"

// Ό³Έν :
class BackDrop_WitchHouse_UpFloor : public BackDrop_PlayLevel
{
public:
	// constrcuter destructer
	BackDrop_WitchHouse_UpFloor();
	~BackDrop_WitchHouse_UpFloor();

	// delete Function
	BackDrop_WitchHouse_UpFloor(const BackDrop_WitchHouse_UpFloor& _Other) = delete;
	BackDrop_WitchHouse_UpFloor(BackDrop_WitchHouse_UpFloor&& _Other) noexcept = delete;
	BackDrop_WitchHouse_UpFloor& operator=(const BackDrop_WitchHouse_UpFloor& _Other) = delete;
	BackDrop_WitchHouse_UpFloor& operator=(BackDrop_WitchHouse_UpFloor&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


public:
	void ActorRelease();

private:
	void CreateProp(GameEngineLevel* _Level);
	void CreatePixelMap(GameEngineLevel* _Level);
	void LoadPortalActor(GameEngineLevel* _Level);

private:
	float4 m_HouseLocation = float4{300.0f , 0.0f };
};

