#include "PreCompile.h"
#include "TestPlayer.h"

#include "TestLevel.h"
#include "PixelManager.h"

TestPlayer::TestPlayer() 
{
}

TestPlayer::~TestPlayer() 
{
}


void TestPlayer::Start()
{
	Ellie::Start();
}

void TestPlayer::Update(float _Delta)
{
	Ellie::Update(_Delta);
}

void TestPlayer::Release()
{
	Ellie::Release();
}

void TestPlayer::LevelStart(class GameEngineLevel* _NextLevel)
{
	Ellie::LevelStart(_NextLevel);
}

void TestPlayer::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

