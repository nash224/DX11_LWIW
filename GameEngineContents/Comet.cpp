#include "PreCompile.h"
#include "Comet.h"

Comet::Comet() 
{
}

Comet::~Comet() 
{
}

void Comet::Start()
{
	const float AnimationInter = FallTime / 6.0f;

	Init();
	m_Renderer->AutoSpriteSizeOn();
	m_Renderer->SetAutoScaleRatio(3.0f);
	m_Renderer->CreateAnimation("Fall", "Title_comet", AnimationInter);
	m_Renderer->ChangeAnimation("Fall");
	m_Renderer->SetPivotType(PivotType::RightUp);

	FallTime = RandomFunction::GetRandomfValue(0.4f, 0.7f);
	FallDirection = float4(-1.0f, -1.0f).NormalizeReturn();
}

void Comet::Update(float _Delta)
{
	static constexpr float FallDistance = 500.0f;

	if (GetLiveTime() > FallTime)
	{
		Death();
		return;
	}

	const float FallSpeed = FallDistance / FallTime * _Delta;
	Transform.AddLocalPosition(FallDirection * FallSpeed);
}

void Comet::Release()
{
	RendererActor::Release();
}

void Comet::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

