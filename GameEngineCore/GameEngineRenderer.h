#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"

// 설명 : GameEngineRenderer에게 Order는 랜더링 되는 순서를 의미합니다.
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetCameraOrder(int _Order);

protected:
	void Start();

private:
	int CameraOrder = 0;
};

