#include "PreCompile.h"
#include "Aurea.h"


#include "BackDrop_PlayLevel.h"
#include "Ellie.h"

Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 180.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void Aurea::Update(float _Delta)
{
	NPCEntity::Update(_Delta);
}

void Aurea::Release()
{
	NPCEntity::Release();
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Aurea::Init()
{
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



	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	m_Body->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererCorrection , GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)});
	m_Shadow->SetSprite("Aurea_idle.png", 1);


	float4 CreaturePos = float4(0.0f, CreatureYPos);
	CreaturePos.Z = BackDrop_PlayLevel::MainBackDrop->ReturnPlusDepth(CreaturePos.Y);

	m_MerchantCreature = CreateComponent<GameEngineSpriteRenderer>();
	m_MerchantCreature->Transform.SetLocalPosition(CreaturePos);
	m_MerchantCreature->CreateAnimation("Idle", "merchant_creature.png", 0.12f);
	m_MerchantCreature->AutoSpriteSizeOn();
	m_MerchantCreature->ChangeAnimation("Idle");
}