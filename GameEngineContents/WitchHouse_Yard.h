#pragma once
#include "FieldLevel.h"

// Ό³Έν :
class BackDrop_WitchHouse_Yard;
class WitchHouse_Yard : public FieldLevel
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
	void LoadActor();

	void SetElliePosToEnter(class GameEngineLevel* _NextLevel);
	void CameraSetting();

	void ReleaseTexture();


private:
	std::shared_ptr<BackDrop_WitchHouse_Yard> Back = nullptr;

};

