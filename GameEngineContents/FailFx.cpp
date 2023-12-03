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
		MsgBoxAssert("�ִϸ��̼��� ã�����߽��ϴ�.");
		return;
	}

	if (Animation->Inter.size() != _Inters.size())
	{
		MsgBoxAssert("�ε����� ���̶��� �ʽ��ϴ�.");
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