#include "PreCompile.h"
#include "GameEngineRenderer.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	GameEngineLevel* Level = GetLevel();

	GameEngineActor* Actor = GetActor();

	// 

	// 카메라를 찾아서 들어가야 합니다.
	// 카메를 찾으려면? GameEngineLevel
	// Level부터 찾아야해.
	// Level누가 들고 있죠? 나를 들고 있는 Actor가 들고 있어.

	// Level을 만들수 밖에 없습니다.

}

void GameEngineRenderer::SetCameraOrder(int _Order)
{

}