#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	CreateChild<Player>();

	//CreateChild<GameEngineRenderer>();
}

void PlayLevel::Update(float _Delta)
{
	int a = 0;
}