#pragma once
#include "FxBase.h"


// Ό³Έν :
class CheerFx : public FxBase
{
public:
	// constrcuter destructer
	CheerFx();
	~CheerFx();

	// delete Function
	CheerFx(const CheerFx& _Other) = delete;
	CheerFx(CheerFx&& _Other) noexcept = delete;
	CheerFx& operator=(const CheerFx& _Other) = delete;
	CheerFx& operator=(CheerFx&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


};

