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
	Fx->AutoSpriteSizeOn();
	Fx->CreateAnimation("Cheer", "Ellie_Basic_Cheer.png", 0.1f, 28, 33, false);
	Fx->ChangeAnimation("Cheer");
	Fx->SetEndEvent("Cheer", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});

	Fx->Transform.SetLocalPosition(float4(0.0f, 30.0f));
}

void CheerFx::Release()
{
	FxBase::Release();
}

void CheerFx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}