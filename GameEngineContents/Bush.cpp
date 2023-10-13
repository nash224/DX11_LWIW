#include "PreCompile.h"
#include "Bush.h"

Bush::Bush() 
{
}

Bush::~Bush() 
{
}


void Bush::Start()
{
	StaticEntity::Start();
}

void Bush::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void Bush::Release()
{
	StaticEntity::Release();

	m_Bush = nullptr;
}

void Bush::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Bush::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Bush::SetBushType(BushType _Type)
{
	m_BushType = _Type;
}

void Bush::Init()
{
	CreateBushAnimation();
}

void Bush::CreateBushAnimation()
{
	m_Bush = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Bush)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Bush->CreateAnimation("Normal", "Bush_0.png", 5.0f, 9, 9);					// 평상시


	if (BushType::BushApple == m_BushType)
	{
		m_Bush->CreateAnimation("Shaking", "Bush_0.png", 0.1f, 0, 7, false);	
		m_Bush->CreateAnimation("Apple", "Bush_0.png", 5.0f, 10, 10,true);				// 사과
	}

	if (BushType::BushBug == m_BushType)
	{
		m_Bush->CreateAnimation("Rustle", "Bush_Animation_1.png", 0.1f, 1, 5, true);	
		m_Bush->FindAnimation("Rustle")->Inter = { 0.1f, 0.1f, 0.1f, 0.1f, 0.8f };

		m_Bush->CreateAnimation("AppearBug", "BushBug_Appearing.png", 0.1f, 1, 18, false);	
	}
}