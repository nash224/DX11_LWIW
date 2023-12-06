#pragma once
#include "BackDrop_PlayLevel.h"

// Ό³Έν :
class BackDrop_WitchHouse_DownFloor : public BackDrop_PlayLevel
{
public:
	// constrcuter destructer
	BackDrop_WitchHouse_DownFloor();
	~BackDrop_WitchHouse_DownFloor();

	// delete Function
	BackDrop_WitchHouse_DownFloor(const BackDrop_WitchHouse_DownFloor& _Other) = delete;
	BackDrop_WitchHouse_DownFloor(BackDrop_WitchHouse_DownFloor&& _Other) noexcept = delete;
	BackDrop_WitchHouse_DownFloor& operator=(const BackDrop_WitchHouse_DownFloor& _Other) = delete;
	BackDrop_WitchHouse_DownFloor& operator=(BackDrop_WitchHouse_DownFloor&& _Other) noexcept = delete;

	void Init();
	void RenewMap();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void PropSetting();
	void PixelMapSetting();
	void InteractiveActorSetting();

	void DustEventSetting();

private:
	std::shared_ptr<RendererActor> LightActor;
	const float4 HousePoint = float4( 150.0f , -10.0f );
};

