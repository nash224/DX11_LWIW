#include "PreCompile.h"
#include "BushBug.h"

BushBug::BushBug() 
{
}

BushBug::~BushBug() 
{
}


void BushBug::Start()
{
	DynamicEntity::Start();
}

void BushBug::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);
}

void BushBug::Release()
{
	DynamicEntity::Release();
}

void BushBug::LevelStart(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelStart(_NextLevel);
}

void BushBug::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BushBug::Init()
{
	//SetDepthBias();
	//ApplyDepth();
	CreateAndSetCollision(ECOLLISION::Entity, { 200.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Dragonfly);
	AnimationSetting();
}

void BushBug::AnimationSetting()
{
	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Bushbug_Standing.png", 2, 9, true);

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->SetSprite("Bushbug_Standing.png", 1);
}