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

void SequentialProp::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void SequentialProp::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SequentialProp::SetTextureScale(const float4& _Scale)
{
	m_TextureScale = _Scale;
}

void SequentialProp::SetSpeed(float _Speed)
{
	m_Speed = _Speed;
}


void SequentialProp::UpdateSequential(float _Delta)
{
	float Speed = m_Speed * _Delta;

	Transform.AddLocalPosition(Speed);

	float4 CurPosition = Transform.GetWorldPosition();
	float DeleteDistance = -m_TextureScale.Half().X;

	if (CurPosition.X <= DeleteDistance)
	{
		isOverScreen = true;
	}
}
