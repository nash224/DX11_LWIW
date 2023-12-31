#pragma once
#include "FieldLevel.h"

// ���� :
class BackDrop_CenterField;
class Ellie;
class PortalObject;
class Field_Center : public FieldLevel
{
public:
	// constrcuter destructer
	Field_Center();
	~Field_Center();

	// delete Function
	Field_Center(const Field_Center& _Other) = delete;
	Field_Center(Field_Center&& _Other) noexcept = delete;
	Field_Center& operator=(const Field_Center& _Other) = delete;
	Field_Center& operator=(Field_Center&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:

	void SetPlayerPosAndFade(class GameEngineLevel* _NextLevel);
	void CameraSetting();

};

