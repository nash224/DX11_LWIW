#pragma once
#include "PlayLevel.h"


// Ό³Έν :
class FieldLevel : public PlayLevel
{
public:
	// constrcuter destructer
	FieldLevel();
	~FieldLevel();

	// delete Function
	FieldLevel(const FieldLevel& _Other) = delete;
	FieldLevel(FieldLevel&& _Other) noexcept = delete;
	FieldLevel& operator=(const FieldLevel& _Other) = delete;
	FieldLevel& operator=(FieldLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	void AutoPlayBGM();

};

