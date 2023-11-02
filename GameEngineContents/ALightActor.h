#pragma once
#include "RendererActor.h"

// Ό³Έν :
class ALightActor : public RendererActor
{
public:
	// constrcuter destructer
	ALightActor();
	~ALightActor();

	// delete Function
	ALightActor(const ALightActor& _Other) = delete;
	ALightActor(ALightActor&& _Other) noexcept = delete;
	ALightActor& operator=(const ALightActor& _Other) = delete;
	ALightActor& operator=(ALightActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

