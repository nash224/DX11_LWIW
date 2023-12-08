#include "PreCompile.h"
#include "ChubHole.h"

ChubHole::ChubHole() 
{
}

ChubHole::~ChubHole() 
{
}



void ChubHole::Release()
{
	HoleRenderer = nullptr;
}


void ChubHole::Init()
{
	if (nullptr == GameEngineSprite::Find("SquishychubHole.png"))
	{
		GameEngineSprite::CreateSingle("SquishychubHole.png");
	}

	HoleRenderer = CreateComponent<GameEngineSpriteRenderer>();
	HoleRenderer->SetSprite("SquishychubHole.png");
	HoleRenderer->Transform.AddLocalPosition({0.0f, 6.0f});
}