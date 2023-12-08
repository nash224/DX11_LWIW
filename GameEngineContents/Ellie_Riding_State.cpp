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
	if (EELLIE_STATUS::Normal == g_Status)
	{
		Broom.HeadBroomRenderer->On();
		Broom.BodyBroomRenderer->On();
	}
	else
	{
		Broom.HeadBroomRenderer->Off();
		Broom.BodyBroomRenderer->Off();
	}

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

	WallLogic();

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
	AddMoveVector(GetMoveForceByDir(_Delta, Riding_Move_Speed, Riding_Move_Acceleration_Time));
	LimitMoveVector(Riding_Move_Speed);
	ContentsActor::ApplyOnlyMovement(_Delta);

	WallLogic();

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
	AddMoveVector(GetMoveForceByDir(_Delta, Riding_Boost_Speed, Riding_Boost_Acceleration_Time));
	LimitMoveVector(Riding_Boost_Speed);
	ContentsActor::ApplyOnlyMovement(_Delta); 

	WallLogic();

	ContentsActor::ApplyDepth();

	ConsumeBroomFuel(_Delta);
	GenerateBoostBroomDust(_Delta);
}

#pragma endregion 

void Ellie::DecelerateNotDir(float _Delta, const float _Force)
{
	const float4 DirVector = DirectionFunction::GetVectorToDirection(Dir);
	bool HorizontalCheck = (GetMoveVector().X * DirVector.X < 0.0f);

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
		static constexpr float MinDistance = 0.0f;
		static constexpr float MaxDistance = 20.0f;

		GameEngineRandom RandomClass;
		for (int i = 0; i < 2; i++)
		{
			RandomClass.SetSeed(GlobalValue::GetSeedValue());
			float DistanceChance = RandomClass.RandomFloat(MinDistance, MaxDistance);
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

	const float4 Correction = float4(8.0f, 28.0f);

	const float4 CenterPoint = Correction + Transform.GetLocalPosition() + PlusVector * _ParticleDistance;

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

void Ellie::WallLogic()
{
	if (true == ContentsActor::WallCollision(PixelCheckDistance))
	{
		if (true == CheckCollideWall())
		{
			ResetMoveVector();
		}
	}
}

bool Ellie::CheckCollideWall()
{
	float4 CurScalar = DirectX::XMVector2Length(GetMoveVector().DirectXVector);
	const float CollideForce = 30.0f;
	if (CurScalar.X > CollideForce)
	{
		return true;
	}

	return false;
}