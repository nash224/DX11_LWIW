#pragma once
#include "DynamicEntity.h"

// Ό³Έν :
class MongSiri : public DynamicEntity
{
public:
	// constrcuter destructer
	MongSiri();
	~MongSiri();

	// delete Function
	MongSiri(const MongSiri& _Other) = delete;
	MongSiri(MongSiri&& _Other) noexcept = delete;
	MongSiri& operator=(const MongSiri& _Other) = delete;
	MongSiri& operator=(MongSiri&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

