#pragma once
#include "FxBase.h"

// Ό³Έν :
class FailFx : public FxBase
{
public:
	// constrcuter destructer
	FailFx();
	~FailFx();

	// delete Function
	FailFx(const FailFx& _Other) = delete;
	FailFx(FailFx&& _Other) noexcept = delete;
	FailFx& operator=(const FailFx& _Other) = delete;
	FailFx& operator=(FailFx&& _Other) noexcept = delete;

	void SetAnimationInter(const std::vector<float>& _Inters);

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

