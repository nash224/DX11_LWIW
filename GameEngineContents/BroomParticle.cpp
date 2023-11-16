#include "PreCompile.h"
#include "BroomParticle.h"

#include "BackDrop_PlayLevel.h"

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

	ParticleUpate(_Delta);
}

void BroomParticle::Release()
{ 
	FxRenderer = nullptr;
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
	ApplyDepth();
	RendererSetting();
}

void BroomParticle::RendererSetting()
{
	FxRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::NonAlphaBlend);
	FxRenderer->AnimationPauseOn();
	FxRenderer->SetAutoScaleRatio(3.0f);
	FxRenderer->SetSprite("Broom_Particle.png");
}

void BroomParticle::ParticleUpate(float _Delta)
{
	const float LiveTimeRatio = 1.0f - GetLiveTime() / BroomFxLiveTime;

	Transform.SetLocalScale(float4(LiveTimeRatio, LiveTimeRatio, 1.0f));
}

void BroomParticle::ApplyDepth()
{
	const float4& MyPos = Transform.GetLocalPosition();
	if (nullptr != BackDrop_PlayLevel::MainBackDrop)
	{
		const float4& BackScale = BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale();
		GlobalUtils::CalculateObjectDepth(BackScale.Y, MyPos.Y + 7.0f);
	}
}