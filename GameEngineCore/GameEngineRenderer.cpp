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

	// ī�޶� ã�Ƽ� ���� �մϴ�.
	// ī�޸� ã������? GameEngineLevel
	// Level���� ã�ƾ���.
	// Level���� ��� ����? ���� ��� �ִ� Actor�� ��� �־�.

	// Level�� ����� �ۿ� �����ϴ�.

}

void GameEngineRenderer::SetCameraOrder(int _Order)
{

}