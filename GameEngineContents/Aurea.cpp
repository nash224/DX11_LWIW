#include "PreCompile.h"
#include "Aurea.h"

Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	StaticEntity::Start();
}

void Aurea::Update(float _Delta)
{
	StaticEntity::Update(_Delta);
}

void Aurea::Release()
{
	StaticEntity::Release();
}

void Aurea::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Aurea::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Aurea::Init()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 180.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}



	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Shadow->SetSprite("Aurea_idle.png", 1);


	m_MerchantCreature = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_MerchantCreature)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}
	
	m_MerchantCreature->CreateAnimation("Idle", "merchant_creature.png", 0.12f);
	m_MerchantCreature->AutoSpriteSizeOn();
	m_MerchantCreature->Transform.SetLocalPosition({ 0.0f, 100.0f, 60.0f });
	m_MerchantCreature->ChangeAnimation("Idle");
}