#include "PreCompile.h"
#include "Ellie.h"



void Ellie::StartIdle()
{
	ChangeAnimationByDirection("Idle");
}

void Ellie::UpdateIdle(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}

		ChangeState(EELLIE_STATE::Walk);
		return;
	}
}

void Ellie::StartWalk()
{
	ChangeAnimationByDirection("Walk");
}

void Ellie::UpdateWalk(float _Delta)
{
	// 움직이지 않으면 Idle인 상태로 간주합니다.
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}
	}

	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	float4 Dir = CalulateDirectionVectorToDir(m_Dir);

	Transform.AddLocalPosition(Dir * EllieWalkSpeed * _Delta);

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Walk", false, CurIndex);
	}
}


void Ellie::StartRun()
{
	ChangeAnimationByDirection("Run");
}

void Ellie::UpdateRun(float _Delta)
{
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			// 기어다니기
		}

		if (true == GameEngineInput::IsFree(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}


	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	float4 Dir = CalulateDirectionVectorToDir(m_Dir);

	Transform.AddLocalPosition(Dir * Ellie_Run_Speed * _Delta);

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Run", false, CurIndex);
	}
}