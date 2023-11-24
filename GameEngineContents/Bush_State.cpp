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
		if (nullptr == BackDrop_PlayLevel::MainBackDrop)
		{
			MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
			return;
		}

		float4 ItemPosition = Transform.GetLocalPosition();
		ItemPosition = { ItemPosition.X, ItemPosition.Y - 50.0f, DepthFunction::CalculateFixDepth(ERENDERDEPTH::RootedItem) };
		BackDrop_PlayLevel::MainBackDrop->CreateItem("Food_CranApple", ItemPosition);

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
	float4 SpawnPosition = Transform.GetLocalPosition() + float4( 5.0f, 7.0f );

	if (nullptr != BackDrop_PlayLevel::MainBackDrop)
	{
		SpawnPosition.Z = DepthFunction::CalculateObjectDepth(BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale().Y, SpawnPosition.Y);
	}

	BushBugPtr->Transform.SetLocalPosition(SpawnPosition);
	BushBugPtr->Init();
}

// 300 
// 60
