#include "PreCompile.h"
#include "AlchemyPot.h"

AlchemyPot::AlchemyPot() 
{
}

AlchemyPot::~AlchemyPot() 
{
}


void AlchemyPot::Start()
{
	StartAlchemyPot();
}

void AlchemyPot::Update(float _Delta)
{

}

void AlchemyPot::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void AlchemyPot::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void AlchemyPot::StartAlchemyPot()
{
	CreateRendererAndAnimation();
	CreateInteractiveCollision();
}

void AlchemyPot::CreateRendererAndAnimation()
{
	m_PotRenderer = CreateComponent<GameEngineSpriteRenderer>(5);
	if (nullptr == m_PotRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_PotRenderer->SetSprite("DownFloor_Pot_0.png");


	m_WaterRenderer = CreateComponent<GameEngineSpriteRenderer>(6);
	if (nullptr == m_WaterRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_WaterRenderer->CreateAnimation("Boil", "Pot_Fx_IdleA.png", 0.1f, 0, 21);
	m_WaterRenderer->CreateAnimation("Boil", "Pot_Fx_Boil.png", 0.1f, 0, 14);
	m_WaterRenderer->CreateAnimation("Boil", "Pot_Fx_Fail.png", 0.1f, 0, 18);
	m_WaterRenderer->CreateAnimation("Boil", "Pot_Fx_Success.png", 0.1f, 0, 21);

	m_WaterRenderer->AutoSpriteSizeOn();



	m_FireRenderer = CreateComponent<GameEngineSpriteRenderer>(6);
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	m_FireRenderer->CreateAnimation("Small", "Pot_Fire_Small.png", 0.1f, 1, 23);
	m_FireRenderer->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_FireRenderer->AutoSpriteSizeOn();
	

	m_PotFxSteam = CreateComponent<GameEngineSpriteRenderer>(7);
	if (nullptr == m_PotFxSteam)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_PotFxSteam->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_PotFxSteam->AutoSpriteSizeOn();
}


void AlchemyPot::CreateInteractiveCollision()
{
	m_InteractiveCol = CreateComponent<GameEngineCollision>(ECOLLISION::Entity);
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_InteractiveCol->SetCollisionType(ColType::SPHERE2D);
	m_InteractiveCol->Transform.SetWorldScale({ 100.0f , 100.0f });
}