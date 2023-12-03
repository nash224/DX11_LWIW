#include "PreCompile.h"
#include "CheerFx.h"

CheerFx::CheerFx() 
{
}

CheerFx::~CheerFx() 
{
}


void CheerFx::Start()
{
	Init();
	FxBase::Fx->Transform.SetLocalPosition(float4(0.0f, 30.0f));
	FxBase::Fx->AutoSpriteSizeOn();
	FxBase::Fx->CreateAnimation("Cheer", "Ellie_Basic_Cheer.png", 0.1f, 28, 33, false);
	FxBase::Fx->ChangeAnimation("Cheer");
	FxBase::Fx->SetEndEvent("Cheer", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});
}

void CheerFx::Release()
{
	FxBase::Release();
}

void CheerFx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}