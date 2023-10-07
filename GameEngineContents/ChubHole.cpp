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
	m_HoleRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::ObjectShadow);
	if (nullptr == m_HoleRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_HoleRenderer->SetSprite("SquishychubHole.png");
}