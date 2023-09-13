#include "PreCompile.h"
#include "Ellie.h"


#pragma region �⺻����
void Ellie::StartIdle()
{
	ChangeAnimationByDirection("Idle");
}

void Ellie::UpdateIdle(float _Delta)
{
	if (false == IsControl)
	{
		return;
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(EELLIE_STATE::Net);
		return;
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(EELLIE_STATE::RootUp);
		return;
	}

	if (true == GameEngineInput::IsDown('3'))
	{
		ChangeState(EELLIE_STATE::Sit);
		return;
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		ChangeState(EELLIE_STATE::MongSiri);
		return;
	}


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
	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(EELLIE_STATE::Net);
		return;
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(EELLIE_STATE::RootUp);
		return;
	}

	if (true == GameEngineInput::IsDown('3'))
	{
		ChangeState(EELLIE_STATE::Sit);
		return;
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		ChangeState(EELLIE_STATE::MongSiri);
		return;
	}


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
#pragma endregion 

#pragma region ���� ����
void Ellie::StartNet()
{
	ChangeAnimationByDirection("Net");
}

void Ellie::UpdateNet(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::StartRootUp()
{
	ChangeAnimationByDirection("RootUp");
}

void Ellie::UpdateRootUp(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::StartSit()
{
	ChangeAnimationByDirection("Sit");
}

void Ellie::UpdateSit(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::StartMongSiri()
{
	ChangeAnimationByDirection("MongSiri");
}

void Ellie::UpdateMongSiri(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}



#pragma endregion 