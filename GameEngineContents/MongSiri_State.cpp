#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"
#include "BackDrop_PlayLevel.h"
#include "ChubHole.h"


void MongSiri::StartIdle()
{
	if (EMONGSIRISTATUS::Normal == m_Status)
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(reinterpret_cast<__int64>(this));
		int SelectNumber = RandomClass.RandomInt(0, 4);
		switch (SelectNumber)
		{
		case 0:
			m_IdleCount = 2;
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

	if (m_IdleCount <= 0 || EMONGSIRISTATUS::Escape == m_Status)
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
		RandomClass.SetSeed(reinterpret_cast<__int64>(this));


		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군 매니저가 존재하지 않습니다.");
			return;
		}

		float4 MyPosition = Transform.GetLocalPosition();
		MyPosition.Z = 0.0f;
		float4 PopulationSpawnPosition = MongSiriParant->m_PopulationLocation;
		PopulationSpawnPosition.Z = 0.0f;
		float PopulationMinCircle = MongSiriParant->m_PopulationMinCircle;
		float PopulationMaxCircle = MongSiriParant->m_PopulationMaxCircle;

		
		float4 TargetDistance = PopulationSpawnPosition - MyPosition;			// 스폰위치와 내 거리
		float SpawnToDistance = TargetDistance.Size();
		float Degree = TargetDistance.NormalizeReturn().Angle2DDeg();
		if (TargetDistance.Y < 0.0f)
		{
			Degree = 180.0f - Degree;
			Degree += 180.0f;
		}

		float JumpAngle = 0.0f;

		// 만약 최대 범위면 구멍으로 뛰어라
		if (SpawnToDistance > PopulationMaxCircle)
		{
			JumpAngle = Degree;
		}
		// 스폰 위치점 기준
		// 작은원 안에 있다면 완전 랜덤 
		else if (SpawnToDistance < PopulationMinCircle)
		{
			JumpAngle = RandomClass.RandomFloat(0.0f, 360.0f);
		}
		// 스폰 위치점 기준
		// 작은 원보다 밖에 있다면
		else if (SpawnToDistance > PopulationMinCircle)
		{
			// 점프력 측정
			float JumpChangeRatio = RandomClass.RandomFloat(0.0f, 1.0f);
			// 높은 확률로
			JumpChangeRatio = static_cast<float>(pow(JumpChangeRatio, 2));
			JumpChangeRatio *= 180.f;
			int MultiValue = RandomClass.RandomInt(0, 1);
			if (1 == MultiValue)
			{
				JumpChangeRatio *= -1.0f;
			}

			// 이 각도로 뛰어라
			JumpAngle = Degree + JumpChangeRatio;

			if (JumpAngle > 360.0f)
			{
				JumpAngle -= 360.0f;
			}

			if (JumpAngle < 0.0f)
			{
				JumpAngle += 360.0f;
			}
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
		float TargetDistance = TargetPosition.Size();
		
		if (TargetDistance < MongSiri_JumpMaxSpeed)
		{
			IsOnTheHole = true;
			m_TargetForce = TargetPosition.NormalizeReturn() * TargetDistance * 1.66f;
		}
		else
		{
			m_TargetForce = TargetPosition.NormalizeReturn() * MongSiri_JumpMaxSpeed;
		}
	}

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
		if (nullptr == BackDrop_PlayLevel::MainBackDrop)
		{
			MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
			return;
		}

		if (false == BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(Transform.GetLocalPosition() + m_TargetForce * _Delta, GameEngineColor::RED))
		{
			m_MoveVector = m_TargetForce;
			ApplyMovement(_Delta);
		}
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
	m_CollectionTool = ETOOLTYPE::None;

	ChangeAnimation("Collected");
}

void MongSiri::UpdateCollected(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd() && true == m_Body->IsCurAnimation("CollectedA"))
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군이 존재하지 않습니다.");
			return;
		}

		MongSiriParant->EscapeHole();

		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}

void MongSiri::EndCollected()
{
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