#include "PreCompile.h"
#include "Ellie_Ride_Fx.h"

Ellie_Ride_Fx::Ellie_Ride_Fx() 
{
}

Ellie_Ride_Fx::~Ellie_Ride_Fx() 
{
}


void Ellie_Ride_Fx::Start()
{
}

void Ellie_Ride_Fx::Update(float _Delta)
{
	if (GetLiveTime() > BroomFxLiveTime)
	{
		Death();
	}
}

void Ellie_Ride_Fx::Release()
{ 
	m_FxRenderer = nullptr;
}

void Ellie_Ride_Fx::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Ellie_Ride_Fx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Ellie_Ride_Fx::Init()
{
	// ��������
	RendererSetting();
}

void Ellie_Ride_Fx::RendererSetting()
{
	m_FxRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_FxRenderer->SetSprite("Broomstick_Contact_Particle.png");
}