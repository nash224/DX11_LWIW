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

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateProp(GameEngineLevel* _Level);
	void CreatePixelMap(GameEngineLevel* _Level);
	void CreateStaticActor();

	void CreateRenderActor(int _UpdateOrder, 
		std::string_view _SpriteName, 
		const float4& _Position, 
		int _DepthType, 
		bool _isFixDepth = true, 
		float _DepthCorrection = 0.0f);

	void DustEventSetting();

private:
	const float4 HouseMoveVector = float4( 150.0f , -10.0f );
};

