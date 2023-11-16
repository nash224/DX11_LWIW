#include "PreCompile.h"
#include "Ellie.h"

#include "RidingFx.h"
#include "BroomParticle.h"

void Ellie::StartRiding_Standing()
{
	if (EELLIE_STATUS::Normal == g_Status)
	{
		m_MoveVector = float4::ZERO;
		m_MoveForce = float4::ZERO;

		Ellie::PlaySFX("SFX_Broomstick_Ride_02.wav");
		OnRideFx();
	}

	g_Status = EELLIE_STATUS::Riding;

	ChangeAnimationByDirection("Riding_Standing");
}

void Ellie::OnRideFx()
{
	std::weak_ptr<RidingFx> riding_FX = GetLevel()->CreateActor<RidingFx>(EUPDATEORDER::Objects);
	riding_FX.lock()->Init(Transform.GetLocalPosition());
}


void Ellie::UpdateRiding_Standing(float _Delta)
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
				ChangeState(EELLIE_STATE::Riding_Boosting);
				return;
			}

			ChangeState(EELLIE_STATE::Riding_Moving);
			return;
		}
		// �������� �ʾҴٸ�
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


void Ellie::StartRiding_Moving()
{
	m_StateTime = 0.0f;

	Ellie::PlaySFX("SFX_Broomstick_Moving_01.wav");
	ChangeAnimationByDirection("Riding_Moving");
}

void Ellie::UpdateRiding_Moving(float _Delta)
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
			ChangeState(EELLIE_STATE::Riding_Boosting);
			return;
		}
	}
	// �������� �ʾҴٸ�
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}

	ChangeDirectionAnimation("Riding_Moving");

	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
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

	ConsumeBroomFuel(_Delta);
	GenerateBroomParticle(_Delta);
}


void Ellie::StartRiding_Boosting()
{
	Ellie::PlaySFX("SFX_Broomstick_Boosting_01.wav");
	ChangeAnimationByDirection("Riding_Boosting");
}

void Ellie::UpdateRiding_Boosting(float _Delta)
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
			ChangeState(EELLIE_STATE::Riding_Moving);
			return;
		}
	}
	// �������� �ʾҴٸ�
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}


	ChangeDirectionAnimation("Riding_Boosting");


	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
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

	ConsumeBroomFuel(_Delta);
	GenerateBroomParticle(_Delta);
}

#pragma endregion 

void Ellie::GenerateBroomParticle(float _Delta)
{
	static constexpr float Particle_Cool_Time = 0.1f;

	m_StateTime += _Delta;

	if (m_StateTime > Particle_Cool_Time)
	{
		m_StateTime -= Particle_Cool_Time;

		// ReverseSpeedCheck
	
		const float4& ParticlePosition = GetBroomParticlePosition();

		const std::shared_ptr<BroomParticle>& Particle = GetLevel()->CreateActor<BroomParticle>(EUPDATEORDER::Objects);
		Particle->Transform.SetLocalPosition(ParticlePosition);
		Particle->Init();
	}
}

float4 Ellie::GetBroomParticlePosition()
{
	static constexpr float YCorrection = 24.0f;

	const float4& CenterPoint = float4(0.0f, YCorrection) + Transform.GetLocalPosition();

	static constexpr const float ParticleDistance = 50.0f;
	float4 DirVector = CalculateDirectionVectorToDir(m_Dir);
	DirVector.X = -DirVector.X;
	DirVector.Y = -DirVector.Y;
	const float4& ReturnValue = CenterPoint + DirVector * ParticleDistance;
	return ReturnValue;
}

void Ellie::ConsumeBroomFuel(float _Delta)
{
	static constexpr const float PayCostCycle = 0.2f;

	BroomUsingTime += _Delta;
	if (BroomUsingTime > PayCostCycle)
	{
		BroomUsingTime -= PayCostCycle;

		if (EELLIE_STATE::Riding_Moving == m_State)
		{
			static constexpr const float MovingCost = 2.0f;
			BroomFuel -= MovingCost;
		}
		else if (EELLIE_STATE::Riding_Boosting == m_State)
		{
			static constexpr const float BoostingCost = 4.0f;
			BroomFuel -= BoostingCost;
		}
	}
}