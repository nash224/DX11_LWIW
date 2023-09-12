#pragma once
#include "BackDrop.h"

// Ό³Έν :
class BackDrop_ElliesHouse : public BackDrop
{
public:
	// constrcuter destructer
	BackDrop_ElliesHouse();
	~BackDrop_ElliesHouse();

	// delete Function
	BackDrop_ElliesHouse(const BackDrop_ElliesHouse& _Other) = delete;
	BackDrop_ElliesHouse(BackDrop_ElliesHouse&& _Other) noexcept = delete;
	BackDrop_ElliesHouse& operator=(const BackDrop_ElliesHouse& _Other) = delete;
	BackDrop_ElliesHouse& operator=(BackDrop_ElliesHouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

