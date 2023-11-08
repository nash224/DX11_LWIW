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
	DynamicEntity::Start();
}

void PumpkinTerrier::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void PumpkinTerrier::Release()
{
	DynamicEntity::Release();

	m_Shadow = nullptr;
}

void PumpkinTerrier::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void PumpkinTerrier::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void PumpkinTerrier::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
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


	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, RendererBias });
	m_Body->CreateAnimation("Idle_Down", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 2, 5, true);
	m_Body->CreateAnimation("Idle_Up", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 6, 9, true);
	m_Body->ChangeAnimation("Idle_Down");

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererBias });
	m_Shadow->SetSprite("PumpkinTerrier_Vine_IdleA.png", 1);
}