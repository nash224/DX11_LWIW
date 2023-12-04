#pragma once
#include "BackDrop_PlayLevel.h"

// Ό³Έν :
class BackDrop_WitchHouse_Yard : public BackDrop_PlayLevel
{
public:
	// constrcuter destructer
	BackDrop_WitchHouse_Yard();
	~BackDrop_WitchHouse_Yard();

	// delete Function
	BackDrop_WitchHouse_Yard(const BackDrop_WitchHouse_Yard& _Other) = delete;
	BackDrop_WitchHouse_Yard(BackDrop_WitchHouse_Yard&& _Other) noexcept = delete;
	BackDrop_WitchHouse_Yard& operator=(const BackDrop_WitchHouse_Yard& _Other) = delete;
	BackDrop_WitchHouse_Yard& operator=(BackDrop_WitchHouse_Yard&& _Other) noexcept = delete;

	void RenewMap();

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void LoadSprite();
	void LoadSerBin();
	void CreateBase();
	void CreateNormalProp();
	void CreateHouse();
	void CreatePortalActor();
	void CreateDian();

	void EventSetting();

	void CheckLetterEvent();
	void CheckCrowEvent();
	void CheckDianSpawn();

	void CreateLetter();
	void ShowCrowEvent();


	void ReleaseYardSprite();
};

