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
	static constexpr int RenderOrder = 0;

	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
}

void SequentialProp::SetTextureScale(const float4& _Scale)
{
	RenderScale = _Scale;
}

void SequentialProp::SetSpeed(float _Speed)
{
	m_Speed = _Speed;
}


void SequentialProp::UpdateSequential(float _Delta)
{
	float Speed = m_Speed * _Delta;

	Transform.AddLocalPosition(float4(Speed));

	const float DeleteDistance = -RenderScale.Half().X;
	if (Transform.GetWorldPosition().X <= DeleteDistance)
	{
		isOverScreen = true;
	}
}
