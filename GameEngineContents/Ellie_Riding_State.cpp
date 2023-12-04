#include "PreCompile.h"
#include "Ellie.h"

#include "ContentsMath.h"
#include "AnimationHelper.h"

#include "RidingFx.h"
#include "BroomParticle.h"
#include "BackDrop_PlayLevel.h"
#include "BroomCollisionParticle.h"

void Ellie::StartRiding_Standing()
{
	if (EELLIE_STATUS::Normal == g_Status)
	{
		ResetMoveVector();

		SFXFunction::PlaySFX("SFX_Broomstick_Ride_02.wav");
		OnRideFx();
	}

	g_Status = EELLIE_STATUS::Riding;

	ChangeAnimationByDirection("Riding_Standing");
}

void Ellie::OnRideFx()
{
	std::shared_ptr<RidingFx> riding_FX = GetLevel()->CreateActor<RidingFx>(EUPDATEORDER::Objects);
	riding_FX->Init(Transform.GetLocalPosition());
}


void Ellie::UpdateRiding_Standing(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
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
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Idle);
			return;
		}
	}

	DetectMovement();

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
	BroomHeadRendererHelper.UpdateHelper(BodyRenderer, Broom.HeadBroomRenderer);
	BroomBodyRendererHelper.UpdateHelper(BodyRenderer, Broom.BodyBroomRenderer);


	DecelerateNotDir(_Delta, Riding_Boost_Speed);
	ContentsActor::ApplyOnlyMovement(_Delta);
	if (true == WallCollision())
	{
		if (true == ChecckCollideWall())
		{
			ResetMoveVector();
		}
	}

	ContentsActor::ApplyDepth();
}


void Ellie::StartRiding_Moving()
{
	StateTime = 0.0f;

	SFXFunction::PlaySFX("SFX_Broomstick_Moving_01.wav");
	ChangeAnimationByDirection("Riding_Moving");
}

void Ellie::UpdateRiding_Moving(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Boosting);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}

	ChangeDirectionAnimation("Riding_Moving");
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
	BroomHeadRendererHelper.UpdateHelper(BodyRenderer, Broom.HeadBroomRenderer);
	BroomBodyRendererHelper.UpdateHelper(BodyRenderer, Broom.BodyBroomRenderer);

	
	DecelerateNotDir(_Delta, Riding_Move_Speed);
	m_MoveVector += GetMoveForceByDir(_Delta, Riding_Move_Speed, Riding_Move_Acceleration_Time);
	LimitMoveVector(Riding_Move_Speed);
	ContentsActor::ApplyOnlyMovement(_Delta);
	if (true == WallCollision())
	{
		if (true == ChecckCollideWall())
		{
			ResetMoveVector();
		}
	}
	ContentsActor::ApplyDepth();

	ConsumeBroomFuel(_Delta);
	GenerateBroomDust(_Delta);
}


void Ellie::StartRiding_Boosting()
{
	SFXFunction::PlaySFX("SFX_Broomstick_Boosting_01.wav");
	ChangeAnimationByDirection("Riding_Boosting");
}

void Ellie::UpdateRiding_Boosting(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Moving);
			return;
		}
	}
	// 움직이지 않았다면
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			if (0.0f != CoolTime)
			{
				return;
			}

			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}


	ChangeDirectionAnimation("Riding_Boosting");
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
	BroomHeadRendererHelper.UpdateHelper(BodyRenderer, Broom.HeadBroomRenderer);
	BroomBodyRendererHelper.UpdateHelper(BodyRenderer, Broom.BodyBroomRenderer);


	DecelerateNotDir(_Delta, Riding_Boost_Speed);
	m_MoveVector += GetMoveForceByDir(_Delta, Riding_Boost_Speed, Riding_Boost_Acceleration_Time);
	LimitMoveVector(Riding_Boost_Speed);
	ContentsActor::ApplyOnlyMovement(_Delta);
	if (true == WallCollision())
	{
		if (true == ChecckCollideWall())
		{
			ResetMoveVector();
		}
	}
	ContentsActor::ApplyDepth();

	ConsumeBroomFuel(_Delta);
	GenerateBoostBroomDust(_Delta);
}

#pragma endregion 

void Ellie::DecelerateNotDir(float _Delta, const float _Force)
{
	const float4 DirVector = DirectionFunction::GetVectorToDirection(Dir);
	bool HorizontalCheck = (m_MoveVector.X * DirVector.X < 0.0f);

	if (EHORIZONTAL_KEY_STATE::Center == HorizontalInputKey || true == HorizontalCheck)
	{
		if (0.0f != m_MoveVector.X)
		{
			if (m_MoveVector.X > 0.0f)
			{
				m_MoveVector.X -= _Force * _Delta;
				if (m_MoveVector.X < 0.0f)
				{
					m_MoveVector.X = 0.0f;
				}
			}
			else
			{
				m_MoveVector.X += _Force * _Delta;
				if (m_MoveVector.X > 0.0f)
				{
					m_MoveVector.X = 0.0f;
				}
			}
		}
	}

	bool VerticalCheck = (m_MoveVector.Y * DirVector.Y < 0.0f);
	if (EVERTICAL_KEY_STATE::Center == VerticalInputKey || true == VerticalCheck)
	{
		if (0.0f != m_MoveVector.Y)
		{
			if (m_MoveVector.Y > 0.0f)
			{
				m_MoveVector.Y -= _Force * _Delta;
				if (m_MoveVector.Y < 0.0f)
				{
					m_MoveVector.Y = 0.0f;
				}
			}
			else
			{
				m_MoveVector.Y += _Force * _Delta;
				if (m_MoveVector.Y > 0.0f)
				{
					m_MoveVector.Y = 0.0f;
				}
			}
		}
	}
}

bool Ellie::WallCollision()
{
	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr == BackDropPtr)
	{
		return false;
	}

	if (0.0f == GetMoveVector().X && 0.0f == GetMoveVector().Y)
	{
		return false;
	}

	const float4 CheckUnitVector = DirectX::XMVector2Normalize(GetMoveVector().DirectXVector);
	const float4 LeftCheckUnitVector = float4::Cross3D(CheckUnitVector.DirectXVector, float4::FORWARD);
	const float4 RightCheckUnitVector = float4::Cross3D(CheckUnitVector.DirectXVector, float4::BACKWARD);
	static constexpr float CheckDistanceToMyPos = 10.0f;

	static constexpr int Max_Check_Count = 8;
	float fCount = 0.0f;

	for (; fCount < static_cast<float>(Max_Check_Count); fCount += 0.5f)
	{
		const float4 CheckPos = Transform.GetLocalPosition() + CheckUnitVector * (CheckDistanceToMyPos - fCount);
		const float4 LeftCheckPos = LeftCheckUnitVector * CheckDistanceToMyPos + CheckPos;
		const float4 RightCheckPos = RightCheckUnitVector * CheckDistanceToMyPos + CheckPos;

		GameEngineColor LeftColor = BackDropPtr->GetColor(LeftCheckPos);
		GameEngineColor RightColor = BackDropPtr->GetColor(RightCheckPos);
		bool isWall = (GameEngineColor::RED == LeftColor || GameEngineColor::RED == RightColor);
		if (false == isWall)
		{
			break;
		}
	}

	if (fCount == 0.0f)
	{
		return false;
	}
	float4 BackVector;
	BackVector.X = -CheckUnitVector.X * fCount;
	BackVector.Y = -CheckUnitVector.Y * fCount;

	Transform.AddLocalPosition(BackVector);
	return true;
}


void Ellie::CreateBroomParticle(float _ParticleDistance /*= 0.0f*/)
{
	const float4 ParticlePosition = GetBroomParticlePosition(_ParticleDistance);

	const std::shared_ptr<BroomParticle>& Particle = GetLevel()->CreateActor<BroomParticle>(EUPDATEORDER::Objects);
	Particle->Transform.SetLocalPosition(ParticlePosition);
	Particle->Init(DirectionFunction::GetVectorToDirection(Dir));
}

void Ellie::GenerateBroomDust(float _Delta)
{
	static constexpr float Particle_Cool_Time = 0.12f;

	StateTime += _Delta;

	if (StateTime > Particle_Cool_Time)
	{
		StateTime -= Particle_Cool_Time;

		// ReverseSpeedCheck
		CreateBroomParticle();
	}
}

void Ellie::GenerateBoostBroomDust(float _Delta)
{
	static constexpr float Particle_Cool_Time = 0.04f;

	StateTime += _Delta;

	if (StateTime > Particle_Cool_Time)
	{
		StateTime -= Particle_Cool_Time;

		// ReverseSpeedCheck
		static constexpr float MinParticleDistance = 0.0f;
		static constexpr float MaxParticleDistance = 20.0f;

		GameEngineRandom RandomClass;
		for (int i = 0; i < 2; i++)
		{
			RandomClass.SetSeed(GlobalValue::GetSeedValue());
			float DistanceChance = RandomClass.RandomFloat(MinParticleDistance, MaxParticleDistance);
			CreateBroomParticle(DistanceChance);
		}
	}
}

float4 Ellie::GetBroomParticlePosition(float _ParticleDistance)
{
	float4 PlusVector;
	if (0.0f != _ParticleDistance)
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(GlobalValue::GetSeedValue());
		const int ReverseChance = RandomClass.RandomInt(0, 1);
	
		PlusVector = DirectX::XMVector2Normalize(m_MoveVector.DirectXVector);
		if (ReverseChance == 0)
		{
			PlusVector = float4::Cross3D(PlusVector.DirectXVector, float4::BACKWARD);
		}
		else
		{
			PlusVector = float4::Cross3D(PlusVector.DirectXVector, float4::FORWARD);
		}
	}
	else
	{
		PlusVector = float4::ZERO;
	}

	static constexpr float YCorrection = 28.0f;

	const float4 CenterPoint = float4(8.0f, YCorrection) + Transform.GetLocalPosition() + PlusVector * _ParticleDistance;

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());
	const float ParticleDistance = RandomClass.RandomFloat(60.0f, 72.0f);

	float4 DirVector = DirectionFunction::GetVectorToDirection(Dir);
	DirVector.X = -DirVector.X;
	DirVector.Y = -DirVector.Y;

	const float4 ReturnValue = CenterPoint + DirVector * ParticleDistance;
	return ReturnValue;
}

void Ellie::ConsumeBroomFuel(float _Delta)
{
	const float PayCostCycle = 0.2f;

	BroomUsingTime += _Delta;
	if (BroomUsingTime > PayCostCycle)
	{
		BroomUsingTime -= PayCostCycle;

		if (EELLIE_STATE::Riding_Moving == State)
		{
			const float MovingCost = 2.0f;
			BroomFuel -= MovingCost;
		}
		else if (EELLIE_STATE::Riding_Boosting == State)
		{
			const float BoostingCost = 4.0f;
			BroomFuel -= BoostingCost;
		}
	}
}

bool Ellie::ChecckCollideWall()
{
	float4 CollisionForce = DirectX::XMVector2Length(GetMoveVector().DirectXVector);
	const float ParticleActivationForce = 30.0f;
	if (CollisionForce.X > ParticleActivationForce)
	{
		return true;
	}

	return false;
}
