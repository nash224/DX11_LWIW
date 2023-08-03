#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
}

void GameEngineCamera::Start()
{
	GameEngineActor::Start();

	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	// Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	if (Level->Cameras[CameraOrder] == shared_from_this())
	{
		Level->Cameras[CameraOrder] = nullptr;
	}
	CameraOrder = _Order;
	Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}