#include "PreCompile.h"
#include "PumpkinTerrier.h"

PumpkinTerrier::PumpkinTerrier() 
{
}

PumpkinTerrier::~PumpkinTerrier() 
{
}


void PumpkinTerrier::Start()
{
	InteractiveActor::Start();
}

void PumpkinTerrier::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void PumpkinTerrier::Release()
{
	InteractiveActor::Release();

	ShadowRenderer = nullptr;
}

void PumpkinTerrier::LevelStart(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelStart(_NextLevel);
}

void PumpkinTerrier::LevelEnd(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelEnd(_NextLevel);
}


void PumpkinTerrier::Init()
{
	ApplyDepth();
	CreateAndSetCollision(ECOLLISION::Entity, { 100.0f, }, 0.0f, ColType::SPHERE2D);
	RendererSetting();
}

void PumpkinTerrier::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("PumpkinTerrier_Vine_GaspA.png"))
	{
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_GaspA.png", 5, 4);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_GaspB.png", 5, 4);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_IdleA.png", 4, 3);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_IdleB.png", 4, 3);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_PawA.png", 4, 4);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_PawB.png", 4, 4);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_RunA.png", 3, 3);
		GameEngineSprite::CreateCut("PumpkinTerrier_Vine_RunB.png", 3, 3);
	}

	
	InteractiveActor::BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	InteractiveActor::BodyRenderer->AutoSpriteSizeOn();
	InteractiveActor::BodyRenderer->Transform.SetLocalPosition({ 0.0f, RendererBias });
	InteractiveActor::BodyRenderer->CreateAnimation("Idle_Down", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 2, 5, true);
	InteractiveActor::BodyRenderer->CreateAnimation("Idle_Up", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 6, 9, true);
	InteractiveActor::BodyRenderer->ChangeAnimation("Idle_Down");

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer->Transform.SetLocalPosition({ 0.0f, RendererBias });
	ShadowRenderer->SetSprite("PumpkinTerrier_Vine_IdleA.png", 1);
}