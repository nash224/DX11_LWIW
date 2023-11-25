#include "PreCompile.h"
#include "LoopTextureActor.h"

LoopTextureActor::LoopTextureActor() 
{
}

LoopTextureActor::~LoopTextureActor() 
{
}


void LoopTextureActor::Update(float _Delta)
{
	if (nullptr == Renderer)
	{
		return;
	}
	
	Renderer->RenderBaseInfoValue.VertexUVPlus += Speed * _Delta;
}

void LoopTextureActor::Release()
{
	Renderer = nullptr;
}

void LoopTextureActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void LoopTextureActor::Init()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->SetSampler("EngineBaseWRAPSampler");
}

void LoopTextureActor::SetSpeed(float _Speed)
{
	GlobalValue::GetWindowScale();
	Speed = -_Speed / GlobalValue::GetWindowScale().X;
}