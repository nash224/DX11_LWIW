#include "PreCompile.h"
#include "ChubHole.h"

ChubHole::ChubHole() 
{
}

ChubHole::~ChubHole() 
{
}


void ChubHole::Start()
{

}

void ChubHole::Update(float _Delta)
{
	
}

void ChubHole::Release()
{
	
}

void ChubHole::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}

void ChubHole::LevelEnd(class GameEngineLevel* _NextLevel)
{
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void ChubHole::Init()
{
	if (nullptr == GameEngineSprite::Find("SquishychubHole.png"))
	{
		GameEngineSprite::CreateSingle("SquishychubHole.png");
	}

	m_HoleRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_HoleRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_HoleRenderer->SetSprite("SquishychubHole.png");
	m_HoleRenderer->Transform.AddLocalPosition({0.0f, 6.0f});
}