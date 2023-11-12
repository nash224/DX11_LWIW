#include "PreCompile.h"
#include "MongSiri.h"

#include "BackDrop_PlayLevel.h"

#include "MongSiri_Population.h"
#include "ChubHole.h"


void MongSiri::StartIdle()
{
	if (EMONGSIRISTATUS::Normal == m_Status)
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
		int SelectNumber = RandomClass.RandomInt(0, 4);
		switch (SelectNumber)
		{
		case 0:
			m_IdleCount = 2;
			break;
		case 1:
		case 2:
			m_IdleCount = 3;
			break;
		case 3:
		case 4:
			m_IdleCount = 1;
			break;
		default:
			break;
		}
	}
	if (EMONGSIRISTATUS::Escape == m_Status)
	{
		m_IdleCount = 1;
	}

	ChangeAnimationByDircetion("Idle");
}

void MongSiri::UpdateIdle(float _Delta)
{
	if (true == IsPlayerAround() && EMONGSIRISTATUS::Escape != m_Status)
	{
		ChangeState(EMONGSIRISTATE::Look);
		return;
	
	}

	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		--m_IdleCount;
	}

	if (m_IdleCount <= 0)
	{
		ChangeState(EMONGSIRISTATE::Jump);
		return;
	}
}

void MongSiri::EndIdle()
{
	m_IdleCount = 0;
}


void MongSiri::StartJump()
{
	SearchJumpLocation();
	ChangeAnimationByDircetion("Jump");
}

// 뛸 장소를 찾아줍니다.
void MongSiri::SearchJumpLocation()
{
	if (EMONGSIRISTATUS::Normal == m_Status)
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());


		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군 매니저가 존재하지 않습니다.");
			return;
		}

		const float4& MyPosition = Transform.GetLocalPosition();
		const float4& PopulationPosition = MongSiriParant->m_PopulationLocation;
		
		float4 VectorToPopulation = PopulationPosition - MyPosition;			// 스폰위치와 내 거리
		float Degree = DirectX::XMConvertToDegrees(atan2f(VectorToPopulation.Y, VectorToPopulation.X));

		const float4& Size = DirectX::XMVector2Length(VectorToPopulation.DirectXVector);
		float Distance = Size.X;

		float JumpAngle = 0.0f;

		bool isOutMaxRange = (Distance > MongSiriParant->m_PopulationMaxRange);
		if (isOutMaxRange)
		{
			JumpAngle = Degree;
		}
		// 스폰 위치점 기준
		// 작은원 안에 있다면 완전 랜덤 
		else if (Distance < MongSiriParant->m_PopulationMinCircle)
		{
			JumpAngle = RandomClass.RandomFloat(0.0f, 360.0f);
		}
		else if (Distance > MongSiriParant->m_PopulationMinCircle)
		{
			float JumpChangeRatio = RandomClass.RandomFloat(0.0f, 1.0f);
			JumpChangeRatio = static_cast<float>(pow(JumpChangeRatio, 2));
			JumpChangeRatio *= 180.f;

			int MultiValue = RandomClass.RandomInt(0, 1);

			bool isReverseJumpChange = (1 == MultiValue);
			if (isReverseJumpChange)
			{
				JumpChangeRatio *= -1.0f;
			}

			JumpAngle = Degree + JumpChangeRatio;
		}

		float MongSiriJumpPower = RandomClass.RandomFloat(0.0f, MongSiri_JumpMaxSpeed);
		float4 TargetUnitVector = float4::GetUnitVectorFromDeg(JumpAngle);

		m_TargetForce = TargetUnitVector * MongSiriJumpPower;
	}

	if (EMONGSIRISTATUS::Escape == m_Status)
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군이 존재하지 않습니다.");
			return;
		}

		if (nullptr == MongSiriParant->m_ChubHole)
		{
			MsgBoxAssert("몽시리 구덩이가 존재하지 않습니다.");
			return;
		}

		float4 HolePosition = MongSiriParant->m_ChubHole->Transform.GetLocalPosition();
		float4 TargetPosition = HolePosition - Transform.GetLocalPosition();
		TargetPosition.Z = 0.0f;
		float TargetDistance = TargetPosition.Size();
		
		static constexpr const float Last_Leaping_Power = 40.0f;
		bool isReachHole = (TargetDistance < Last_Leaping_Power);
		if (isReachHole)
		{
			IsOnTheHole = true;
			m_TargetForce = TargetPosition.NormalizeReturn() * TargetDistance * 1.66f;
		}
		else
		{
			m_TargetForce = TargetPosition.NormalizeReturn() * MongSiri_JumpMaxSpeed;
		}
	}

	m_TargetForce.Z = 0.0f;

	m_Dir = GetDiagonalDirectionFromVector(m_TargetForce);
}

void MongSiri::UpdateJump(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		if (true == IsOnTheHole)
		{
			ChangeState(EMONGSIRISTATE::Disappear);
			return;
		}

		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}

	if (m_Body->GetCurIndex() > 2 && m_Body->GetCurIndex() < 9)
	{
		if (nullptr != BackDrop_PlayLevel::MainBackDrop)
		{
			if (true == BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(Transform.GetLocalPosition() + m_TargetForce * _Delta, GameEngineColor::RED))
			{
				m_TargetForce = float4::ZERO;
			}
		}

		m_MoveVector = m_TargetForce;
		ApplyMovement(_Delta);
	}

}

void MongSiri::EndJump()
{
	m_TargetForce = float4::ZERO;
	m_MoveVector = float4::ZERO;
}


void MongSiri::StartLook()
{
	ChangeAnimationByDircetion("Look");
}

void MongSiri::UpdateLook(float _Delta)
{
	if (false == IsPlayerAround() || EMONGSIRISTATUS::Escape == m_Status)
	{
		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}


void MongSiri::GetCaught()
{
	ChangeState(EMONGSIRISTATE::Caught);
}

void MongSiri::StartCaught()
{
	m_Dir = EDIRECTION::LEFTDOWN;
	ChangeAnimationByDircetion("Idle");
}

void MongSiri::UpdateCaught(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ChangeState(EMONGSIRISTATE::Collected);
		return;
	}
}

void MongSiri::StartCollected()
{
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	

	m_InteractiveCol->Off();
	ChangeAnimation("Collected");
}

void MongSiri::UpdateCollected(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd() && true == m_Body->IsCurAnimation("CollectedB"))
	{
		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}

void MongSiri::EndCollected()
{
	if (nullptr != MongSiriParant)
	{
		MongSiriParant->EscapeHoleToOtherMonsiri();
	}

	m_Status = EMONGSIRISTATUS::Escape;
}


void MongSiri::StartDisappear()
{
	m_CollectionTool = ETOOLTYPE::None;
	ChangeAnimation("Disappear");
}

void MongSiri::UpdateDisappear(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군이 존재하지 않습니다.");
			return;
		}

		MongSiriParant->MongSiriEntityList.remove(GetDynamic_Cast_This<MongSiri>());
		Death();
	}
}
