#include "PreCompile.h"
#include "MongSiri.h"

#include "MonSiri_Population.h"

MongSiri::MongSiri() 
{
}

MongSiri::~MongSiri() 
{
}


void MongSiri::Start()
{
	DynamicEntity::Start();

	m_CollectionMethod = ECOLLECTION_METHOD::MongSiri;
	m_CollectionTool = ETOOLTYPE::Gloves;
}

void MongSiri::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void MongSiri::Release()
{
	DynamicEntity::Release();
}

void MongSiri::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void MongSiri::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void MongSiri::Init()
{
	CreateAndSetRenderer();
	CreateAndSetCollision(ECOLLISION::Entity, { 50, 50 }, float4::ZERO, ColType::SPHERE2D);
}

void MongSiri::CreateAndSetRenderer()
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Mongsiri_Idle.png", 0.1f, 4, 7);
	m_Body->ChangeAnimation("Idle");
	m_Body->AutoSpriteSizeOn();

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::ObjectShadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->CreateAnimation("Shadow_Idle", "Mongsiri_Idle.png");
	m_Shadow->ChangeAnimation("Shadow_Idle");
	m_Shadow->AutoSpriteSizeOn();
}