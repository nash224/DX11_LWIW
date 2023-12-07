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

	void RenewMap();

	float4 GetHouseLocation() const
	{
		return HouseLocation;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void LoadResources();
	void ReleaseResources();

	void CreateProp();
	void CreatePixelMap();
	void HouseLightSetting();
	void LoadPortalActor();
	void LiftSetting();
	void BedSetting();

	void DustEventSetting();


	void CheckHouseDustEvent();
	void ShowHouseDustEvent();

private:
	std::shared_ptr<GameEngineObject> ArrangePtr;
	const float4 HouseLocation = float4{340.0f , -50.0f };

	bool isInitDustEvent = false;

};

