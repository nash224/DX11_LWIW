#include "PreCompile.h"
#include "Bush.h"

#include "BackDrop_PlayLevel.h"




void Bush::StartNormal()
{
	m_BushType = EBUSHTYPE::Bush;
	m_InteractionButtonType = EINTERACTION_BUTTONTYPE::None;
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
		ItemPosition = { ItemPosition.X, ItemPosition.Y - 50.0f, GlobalUtils::CalculateDepth(ERENDERDEPTH::RootedItem) };
		BackDrop_PlayLevel::MainBackDrop->CreateItem("Food_CranApple", ItemPosition);

		ChangeState(EBUSHSTATE::Shake);
		return;
	}
}


void Bush::StartShake()
{
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("존재하지않는 충돌체를 바꾸려고 했습니다.");
		return;
	}

	m_InteractiveCol->Off();

	ChangeBushAnimation("Shake");
}

void Bush::UpdateShake(float _Delta)
{
	if (nullptr == m_Bush)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Bush->IsCurAnimationEnd())
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
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("존재하지않는 충돌체를 바꾸려고 했습니다.");
		return;
	}

	m_InteractiveCol->Off();

	ChangeBushAnimation("AppearBug");
}

void Bush::UpdateAppearBug(float _Delta)
{
	if (nullptr == m_Bush)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Bush->IsCurAnimationEnd())
	{
		// 고올든 벌레 소환

		ChangeState(EBUSHSTATE::Normal);
		return;
	}
}