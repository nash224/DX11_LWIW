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
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, RendererBias });
	m_Body->CreateAnimation("Idle_Down", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 2, 5, true);
	m_Body->CreateAnimation("Idle_Up", "PumpkinTerrier_Vine_IdleA.png", 0.12f, 6, 9, true);
	m_Body->ChangeAnimation("Idle_Down");

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererBias });
	m_Shadow->SetSprite("PumpkinTerrier_Vine_IdleA.png", 1);
}