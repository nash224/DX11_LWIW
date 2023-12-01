#pragma once
#include "FieldLevel.h"

// ���� :
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
	void SetPlayerPosition(class GameEngineLevel* _NextLevel) const;

	void LoadLevelTexture();
	void ReleaseLevelTexture();

};

