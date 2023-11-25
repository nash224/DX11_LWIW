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
	FallTime = RandomFunction::GetRandomfValue(0.4f, 0.7f);
	const float AnimationInter = FallTime / 6.0f;

	Init();
	m_Renderer->AutoSpriteSizeOn();
	m_Renderer->SetAutoScaleRatio(3.0f);
	m_Renderer->CreateAnimation("Fall", "Title_comet", AnimationInter);
	m_Renderer->ChangeAnimation("Fall");
	m_Renderer->SetPivotType(PivotType::RightUp);

	const float4& LeftBotDirVector = float4(-1.0f, -1.0f);
	FallDirection = LeftBotDirVector.NormalizeReturn();
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
}

void Comet::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

