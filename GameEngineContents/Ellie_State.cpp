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
	// �������� ������ Idle�� ���·� �����մϴ�.
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

	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
	float4 Dir = CalulateDirectionVectorToDir(m_Dir);

	Transform.AddLocalPosition(Dir * EllieWalkSpeed * _Delta);

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("�������� ���� �������� ����Ϸ� �߽��ϴ�.");
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
			// ���ٴϱ�
		}

		if (true == GameEngineInput::IsFree(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}


	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
	float4 Dir = CalulateDirectionVectorToDir(m_Dir);

	Transform.AddLocalPosition(Dir * Ellie_Run_Speed * _Delta);

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("�������� ���� �������� ����Ϸ� �߽��ϴ�.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Run", false, CurIndex);
	}
}