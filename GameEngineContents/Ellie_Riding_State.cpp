#include "PreCompile.h"
#include "Ellie.h"



void Ellie::StartRiding_Idle()
{
	if (EELLIE_STATUS::Normal == g_Status)
	{
		m_MoveVector = float4::ZERO;
		m_MoveForce = float4::ZERO;
		OnRideFx();
	}

	g_Status = EELLIE_STATUS::Riding;

	ChangeAnimationByDirection("Riding_Idle");
}

void Ellie::OnRideFx()
{
	if (nullptr == m_Fx)
	{
		MsgBoxAssert("효과 렌더러가 존재하지 않습니다.");
		return;
	}

	m_Fx->ChangeAnimation("FX", true);
	m_Fx->On();
}


void Ellie::UpdateRiding_Idle(float _Delta)
{
	if (true == IsControl)
	{
		if (true == DetectMovement())
		{
			if (true == GameEngineInput::IsDown(VK_CONTROL, this))
			{
				ChangeState(EELLIE_STATE::Idle);
				return;
			}

			if (true == GameEngineInput::IsPress(VK_SPACE, this))
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
			if (true == GameEngineInput::IsDown(VK_CONTROL, this))
			{
				ChangeState(EELLIE_STATE::Idle);
				return;
			}
		}
	}

	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovement(_Delta);
}


void Ellie::StartRiding_Move()
{
	ChangeAnimationByDirection("Riding_Move");
}

void Ellie::UpdateRiding_Move(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Boost);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	ChangeDirectionAnimation("Riding_Move");

	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	float4 MoveVector = ReturnPostMoveVector(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	EDIRECTION Direction = GetDirectionFromVector(MoveVector);
	EDIRECTION MoveDirection = ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(Direction, MoveVector);
	if (Direction == MoveDirection)
	{
		CONST_Ellie_Riding_Move_Speed;
		if (true == IsOverSpeed(MoveVector.X, CONST_Ellie_Riding_Move_Speed))
		{
			m_MoveForce.X = 0.0f;
		}
		if (true == IsOverSpeed(MoveVector.Y, CONST_Ellie_Riding_Move_Speed))
		{
			m_MoveForce.Y = 0.0f;
		}

		m_MoveVector += m_MoveForce;
	}
	else
	{
		m_MoveVector = float4::ZERO;
	}

	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovement(_Delta);
}


void Ellie::StartRiding_Boost()
{
	ChangeAnimationByDirection("Riding_Boost");
}

void Ellie::UpdateRiding_Boost(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Move);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	ChangeDirectionAnimation("Riding_Boost");


	// 방향을 넣으면 방향 기저벡터를 반환 해줍니다.
	float4 MoveVector = ReturnPostMoveVector(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	EDIRECTION Direction = GetDirectionFromVector(MoveVector);
	EDIRECTION MoveDirection = ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(Direction, MoveVector);
	if (Direction == MoveDirection)
	{
		CONST_Ellie_Riding_Boost_Speed;
		if (true == IsOverSpeed(MoveVector.X, CONST_Ellie_Riding_Boost_Speed))
		{
			m_MoveForce.X = 0.0f;
		}
		if (true == IsOverSpeed(MoveVector.Y, CONST_Ellie_Riding_Boost_Speed))
		{
			m_MoveForce.Y = 0.0f;
		}

		m_MoveVector += m_MoveForce;
	}
	else
	{
		m_MoveVector = float4::ZERO;
	}

	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	ApplyMovement(_Delta);
}


#pragma endregion 