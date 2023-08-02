#pragma once
#include "GameEngineObject.h"
#include <list>

// 설명 :
class GameEngineActor : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:

private:
	// 다형성은 무조건 위쪽을 가질수록 범용성이 높아집니다.
	// 그리고 + 이런 기능은 
	// Renderer와 Collision : GameEngineComponent

};

