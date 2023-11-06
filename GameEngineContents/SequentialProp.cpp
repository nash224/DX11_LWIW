#include "PreCompile.h"
#include "SequentialProp.h"

SequentialProp::SequentialProp() 
{
}

SequentialProp::~SequentialProp() 
{
}


void SequentialProp::Start()
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

void SequentialProp::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void SequentialProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SequentialProp::Init()
{
	static constexpr const int RenderOrder = 0;

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

	Transform.AddLocalPosition({ Speed });

	float4 CurPosition = Transform.GetWorldPosition();
	float DeleteDistance = -RenderScale.Half().X;

	if (CurPosition.X <= DeleteDistance)
	{
		isOverScreen = true;
	}
}
