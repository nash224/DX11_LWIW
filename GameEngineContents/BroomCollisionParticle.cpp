#include "PreCompile.h"
#include "BroomCollisionParticle.h"

BroomCollisionParticle::BroomCollisionParticle() 
{
}

BroomCollisionParticle::~BroomCollisionParticle() 
{
}

void BroomCollisionParticle::Update(float _Delta) 
{
	if (GetLiveTime() > 0.5f)
	{
		Death();
	}

	Speed -= MaxSpeed * _Delta / 0.4f;
	if (Speed < 0.0f)
	{
		Speed = 0.0f;
	}

	Alpha -= _Delta / 0.4f;
	if (Alpha < 0.4f)
	{
		Alpha = 0.4f;
	}

	Transform.AddLocalPosition(Direction * Speed * _Delta);
	EffectRenderer->GetColorData().MulColor.A = Alpha;
}

void BroomCollisionParticle::Release()
{
	EffectRenderer = nullptr;
}

void BroomCollisionParticle::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void BroomCollisionParticle::Init(float _Size, float _Angle, float _Speed)
{
	Direction = float4::GetUnitVectorFromDeg(_Angle);
	Speed = _Speed;
	MaxSpeed = _Speed;

	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>();
	EffectRenderer->SetSprite("Broomstick_Collide_Particle.png");
	EffectRenderer->GetImageTransform().SetLocalScale(float4(_Size, _Size));
}