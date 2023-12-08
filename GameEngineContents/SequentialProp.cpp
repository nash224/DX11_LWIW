#include "PreCompile.h"
#include "SequentialProp.h"

SequentialProp::SequentialProp() 
{
}

SequentialProp::~SequentialProp() 
{
}

void SequentialProp::Update(float _Delta)
{
	UpdateSequential(_Delta);
}

void SequentialProp::Release()
{
	Renderer = nullptr;
}

void SequentialProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void SequentialProp::Init()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
}

void SequentialProp::SetTextureScale(const float4& _Scale)
{
	RenderScale = _Scale;
}

void SequentialProp::SetSpeed(float _Speed)
{
	MoveSpeed = _Speed;
}


void SequentialProp::UpdateSequential(float _Delta)
{
	const float Speed = MoveSpeed * _Delta;
	Transform.AddLocalPosition(float4(Speed));

	const float DeleteDistance = -RenderScale.Half().X;
	if (Transform.GetWorldPosition().X <= DeleteDistance)
	{
		isOverScreen = true;
	}
}
