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
	StaticEntity::Update(_Delta);
}

void Dian::Release()
{
	m_InteractiveCol = nullptr;

	if (0 == m_Body.use_count())
	{
		if (nullptr != GameEngineSprite::Find("Dian_idle.png"))
		{
			GameEngineSprite::Release("Dian_idle.png");
		}
	}
	
}

void Dian::LevelStart(class GameEngineLevel* _NextLevel)
{

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
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Dian_idle.png", 0.15f, 3, 7, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({0.0f, m_RendererBias });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Shadow->Transform.SetLocalPosition({ 0.0f, m_RendererBias });
	m_Shadow->SetSprite("Dian_idle.png", 0);
}