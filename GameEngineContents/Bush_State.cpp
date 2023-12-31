#include "PreCompile.h"
#include "Bush.h"

#include "BackDrop_PlayLevel.h"
#include "BushBug.h"




void Bush::StartNormal()
{
	BushType = EBUSHTYPE::Bush;
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::None);
	ChangeBushAnimation("Normal");
}

void Bush::UpdateNormal(float _Delta)
{
	// ?
}


void Bush::StartApple()
{
	ChangeBushAnimation("Apple");
}

void Bush::UpdateApple(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
		if (nullptr == BackDropPtr)
		{
			MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
			return;
		}

		const float4& MyPosition = Transform.GetLocalPosition();
		float4 ItemPosition = { MyPosition.X, MyPosition.Y - 50.0f, DepthFunction::CalculateFixDepth(ERENDERDEPTH::RootedItem) };
		BackDropPtr->CreateItem("Food_CranApple", ItemPosition);

		ChangeState(EBUSHSTATE::Shake);
		return;
	}
}


void Bush::StartShake()
{
	if (nullptr == InteractiveCol)
	{
		MsgBoxAssert("존재하지않는 충돌체를 바꾸려고 했습니다.");
		return;
	}

	InteractiveCol->Off();

	SFXFunction::PlaySFX("SFX_BushBug_BushShake_01.wav");

	ChangeBushAnimation("Shake");
}

void Bush::UpdateShake(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EBUSHSTATE::Normal);
		return;
	}
}


void Bush::StartRustle()
{
	ChangeBushAnimation("Rustle");
}

void Bush::UpdateRustle(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ChangeState(EBUSHSTATE::AppearBug);
		return;
	}
}


void Bush::StartAppearBug()
{
	if (nullptr == InteractiveCol)
	{
		MsgBoxAssert("존재하지않는 충돌체를 바꾸려고 했습니다.");
		return;
	}

	InteractiveCol->Off();

	ChangeBushAnimation("AppearBug");
}

void Bush::UpdateAppearBug(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		CreateBushBug();
		ChangeState(EBUSHSTATE::Normal);
		return;
	}
}


void Bush::CreateBushBug()
{
	// 고올든 벌레 소환
	std::shared_ptr<BushBug> BushBugPtr = GetLevel()->CreateActor<BushBug>();
	float4 SpawnPosition = Transform.GetLocalPosition() + float4( 5.0f, 27.0f );

	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr != BackDropPtr)
	{
		SpawnPosition.Z = DepthFunction::CalculateObjectDepth(BackDropPtr->GetBackGroundScale().Y, SpawnPosition.Y);
	}

	BushBugPtr->Transform.SetLocalPosition(SpawnPosition);
	BushBugPtr->Init();
}