#include "PreCompile.h"
#include "Ellie_Ride_Particle.h"

Ellie_Ride_Particle::Ellie_Ride_Particle() 
{
}

Ellie_Ride_Particle::~Ellie_Ride_Particle() 
{
}


void Ellie_Ride_Particle::Start()
{
}

void Ellie_Ride_Particle::Update(float _Delta)
{
	if (GetLiveTime() > BroomFxLiveTime)
	{
		Death();
	}
}

void Ellie_Ride_Particle::Release()
{ 
	m_FxRenderer = nullptr;
}

void Ellie_Ride_Particle::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Ellie_Ride_Particle::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Ellie_Ride_Particle::Init()
{
	// ��������
	RendererSetting();
}

void Ellie_Ride_Particle::RendererSetting()
{
	m_FxRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_FxRenderer->SetSprite("Broomstick_Contact_Particle.png");
}