#include "PreCompile.h"
#include "BroomParticle.h"

BroomParticle::BroomParticle() 
{
}

BroomParticle::~BroomParticle() 
{
}


void BroomParticle::Start()
{
}

void BroomParticle::Update(float _Delta)
{
	if (GetLiveTime() > BroomFxLiveTime)
	{
		Death();
	}
}

void BroomParticle::Release()
{ 
	m_FxRenderer = nullptr;
}

void BroomParticle::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void BroomParticle::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void BroomParticle::Init()
{
	// ��������
	RendererSetting();
}

void BroomParticle::RendererSetting()
{
	m_FxRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_FxRenderer->SetSprite("Broomstick_Contact_Particle.png");
}