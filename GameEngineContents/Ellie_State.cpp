#include "PreCompile.h"
#include "Ellie.h"

#include "BackDrop.h"



bool Ellie::InputTestPattern()
{
	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeState(EELLIE_STATE::Net);
		return true;
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeState(EELLIE_STATE::RootUp);
		return true;
	}

	if (true == GameEngineInput::IsDown('3'))
	{
		ChangeState(EELLIE_STATE::Sit);
		return true;
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		ChangeState(EELLIE_STATE::MongSiri);
		return true;
	}

	if (true == GameEngineInput::IsDown('5'))
	{
		ChangeState(EELLIE_STATE::Cheer);
		return true;
	}

	if (true == GameEngineInput::IsDown('6')) 
	{
		ChangeState(EELLIE_STATE::Fail);
		return true;
	}

	if (true == GameEngineInput::IsDown('7'))
	{
		ChangeState(EELLIE_STATE::Drink);
		return true;
	}

	if (true == GameEngineInput::IsDown('8'))
	{
		ChangeState(EELLIE_STATE::Throw);
		return true;
	}

	return false;
}


#pragma region 기본조작
void Ellie::StartIdle()
{
	if (EELLIE_STATUS::Riding == m_Status)
	{
		// FX
	}

	m_Status = EELLIE_STATUS::Normal;

	ChangeAnimationByDirection("Idle");
}

void Ellie::UpdateIdle(float _Delta)
{
	if (false == IsControl)
	{
		return;
	}

	if (true == InputTestPattern())
	{
		return;
	}

	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			ChangeState(EELLIE_STATE::SlowWalk);
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

	if (true == GameEngineInput::IsDown(VK_CONTROL))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}
}


void Ellie::StartSlowWalk()
{
	ChangeAnimationByDirection("SlowWalk");
}

void Ellie::UpdateSlowWalk(float _Delta)
{
	// 움직이지 않으면 Idle인 상태로 간주합니다.
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsFree(VK_LSHIFT))
		{
			if (true == GameEngineInput::IsPress(VK_SPACE))
			{
				ChangeState(EELLIE_STATE::Run);
				return;
			}

			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("SlowWalk", true, false, CurIndex);
	}


	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_SlowWalk_Speed);
	ApplyMovementToTransform(_Delta);
}


void Ellie::StartWalk()
{
	ChangeAnimationByDirection("Walk");
}

void Ellie::UpdateWalk(float _Delta)
{
	InputTestPattern();

	// 움직이지 않으면 Idle인 상태로 간주합니다.
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			ChangeState(EELLIE_STATE::SlowWalk);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Walk", true, false, CurIndex);
	}


	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Walk_Speed);
	ApplyMovementToTransform(_Delta);
}


void Ellie::StartRun()
{
	ChangeAnimationByDirection("Run");
}

void Ellie::UpdateRun(float _Delta)
{
	InputTestPattern();

	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			ChangeState(EELLIE_STATE::SlowWalk);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Run", true, false, CurIndex);
	}


	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Run_Speed);
	ApplyMovementToTransform(_Delta);
}



void Ellie::StartThrow()
{
	ChangeAnimationByDirection("Throw");
}

void Ellie::UpdateThrow(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::StartRiding_Idle()
{
	if (EELLIE_STATUS::Normal == m_Status)
	{
		m_MoveVector = float4::ZERO;
		m_MoveForce = float4::ZERO;
		// FX
	}

	m_Status = EELLIE_STATUS::Riding;

	ChangeAnimationByDirection("Riding_Idle");
}

void Ellie::UpdateRiding_Idle(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Riding_Boost);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Move);
		return;
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}
	}


	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovementToTransform(_Delta);
}


void Ellie::StartRiding_Move()
{
	ChangeAnimationByDirection("Riding_Move");
}

void Ellie::UpdateRiding_Move(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Riding_Boost);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Riding_Move", true, false, CurIndex);
	}


	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	CalculateMoveForce(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovementToTransform(_Delta);
}


void Ellie::StartRiding_Boost()
{
	ChangeAnimationByDirection("Riding_Boost");
}

void Ellie::UpdateRiding_Boost(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Riding_Move);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Riding_Boost", true, false, CurIndex);
	}


	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	CalculateMoveForce(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	ApplyMovementToTransform(_Delta);
}


#pragma endregion 





#pragma region 수집 패턴
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


#pragma region 단일 애니메이션 

void Ellie::StartCheer()
{
	ChangeAnimationByDirection("Cheer", false);
}

void Ellie::UpdateCheer(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::StartFail()
{
	ChangeAnimationByDirection("Fail", false);
}

void Ellie::UpdateFail(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}



void Ellie::StartDrink()
{
	ChangeAnimationByDirection("Drink", false);

}

void Ellie::UpdateDrink(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

#pragma endregion 