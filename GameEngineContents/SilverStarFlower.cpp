#include "PreCompile.h"
#include "SilverStarFlower.h"

SilverStarFlower::SilverStarFlower() 
{
}

SilverStarFlower::~SilverStarFlower() 
{
}


void SilverStarFlower::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void SilverStarFlower::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void SilverStarFlower::Release()
{
	StaticEntity::Release();

	m_Plant = nullptr;
	m_Shadow = nullptr;
}

void SilverStarFlower::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void SilverStarFlower::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void SilverStarFlower::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void SilverStarFlower::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("SilverStarFlower.png"))
	{
		GameEngineSprite::CreateCut("SilverStarFlower.png", 4, 3);
	}

	static constexpr const int RenderOrder = 0;

	m_Plant = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Plant->CreateAnimation("Idle", "SilverStarFlower.png", 0.15f, 3, 3, false);
	m_Plant->CreateAnimation("Touch", "SilverStarFlower.png", 0.15f, 4, 9, false);
	m_Plant->AutoSpriteSizeOn();
	m_Plant->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Plant->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Shadow->SetSprite("SilverStarFlower.png", 1);
}