#include "PreCompile.h"
#include "FailFx.h"

FailFx::FailFx() 
{
}

FailFx::~FailFx() 
{
}


void FailFx::Start()
{
	Init();
	FxBase::Fx->Transform.SetLocalPosition(float4(0.0f, 30.0f));
	FxBase::Fx->AutoSpriteSizeOn();
	FxBase::Fx->CreateAnimation("Fail", "Ellie_Basic_Fail.png", 0.1f, 21, 25, false);
	FxBase::Fx->ChangeAnimation("Fail");
	FxBase::Fx->SetEndEvent("Fail", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});
}

void FailFx::SetAnimationInter(const std::vector<float>& _Inters)
{
	const std::shared_ptr<GameEngineFrameAnimation>& Animation = FxBase::Fx->FindAnimation("Fail");
	if (nullptr == Animation)
	{
		MsgBoxAssert("애니메이션을 찾지못했습니다.");
		return;
	}

	if (Animation->Inter.size() != _Inters.size())
	{
		MsgBoxAssert("인덱스가 동이랗지 않습니다.");
		return;
	}

	Animation->Inter = _Inters;
}


void FailFx::Release()
{
	FxBase::Release();
}

void FailFx::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}