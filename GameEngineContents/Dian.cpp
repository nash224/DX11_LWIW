#include "PreCompile.h"
#include "Dian.h"

Dian::Dian() 
{
}

Dian::~Dian() 
{
}


void Dian::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void Dian::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	m_ConversationInfo.UpdateConversation(_Delta);
}

void Dian::Release()
{
	NPCEntity::Release();
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Dian::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void Dian::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Dian_idle.png"))
	{
		GameEngineSprite::CreateCut("Dian_idle.png", 3, 3);
	}


	m_Body = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Object);
	m_Body->CreateAnimation("Idle", "Dian_idle.png", 0.15f, 3, 7, true);
	m_Body->Transform.SetLocalPosition({0.0f, RendererYCorrection });
	m_Body->AutoSpriteSizeOn();
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	m_Shadow->SetSprite("Dian_idle.png", 0);
}