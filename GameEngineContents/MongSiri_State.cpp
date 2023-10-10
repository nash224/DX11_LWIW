#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"
#include "BackDrop_PlayLevel.h"


void MongSiri::StartIdle()
{
	GameEngineRandom RandomClass;
	int SelectNumber = RandomClass.RandomInt(0, 4);
	switch (SelectNumber)
	{
	case 0:
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

	ChangeAnimationByDircetion("Idle");
}

void MongSiri::UpdateIdle(float _Delta)
{
	if (true == IsPlayerAround())
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
	GameEngineRandom RandomClass;
	if (nullptr == MongSiriParant)
	{
		MsgBoxAssert("몽시리 개체군 매니저가 존재하지 않습니다.");
		return;
	}

	float4 MyPosition = Transform.GetLocalPosition();
	float4 PopulationSpawnPosition = MongSiriParant->m_PopulationLocation;
	float PopulationMinCircle = MongSiriParant->m_PopulationMinCircle;
	float PopulationMaxCircle = MongSiriParant->m_PopulationMaxCircle;

	// 스폰위치와 내 거리
	float SpawnToDistance = (MyPosition - PopulationSpawnPosition).Size();
	float Degree = (PopulationSpawnPosition - MyPosition).NormalizeReturn().Angle2DDeg();

	float JumpAngle = 0.0f;

	if (SpawnToDistance < PopulationMinCircle)
	{
		JumpAngle = RandomClass.RandomFloat(0.0f, 360.0f);
	}

	// 스폰 위치 작은 원보다 멀면 구멍 근처로 점프합니다.
	if (SpawnToDistance > PopulationMinCircle)
	{
		float JumpChangeRatio = RandomClass.RandomFloat(0.0f, 1.0f);
		JumpChangeRatio = static_cast<float>(pow(JumpChangeRatio, 2));
		JumpChangeRatio *= 180.f;
		int MultiValue = RandomClass.RandomInt(0, 1);
		if (1 == MultiValue)
		{
			JumpChangeRatio *= -1.0f;
		}

		JumpAngle = Degree + JumpChangeRatio;
	}
	
	float MongSiriJumpPower = RandomClass.RandomFloat(0.0f, MongSiri_JumpMaxSpeed);
	float4 TargetUnitVector = float4::GetUnitVectorFromDeg(JumpAngle);

	m_TargetForce = TargetUnitVector * MongSiriJumpPower;
	m_Dir = GetDirectionFromVector(m_TargetForce);
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

		if (false == BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(m_TargetForce * _Delta, GameEngineColor::RED))
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
	m_Status = EMONGSIRISTATUS::Look;
	ChangeAnimationByDircetion("Look");
}

void MongSiri::UpdateLook(float _Delta)
{
	if (false == IsPlayerAround())
	{
		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}


void MongSiri::StartCollected()
{
	ChangeAnimation("Collected");
}

void MongSiri::UpdateCollected(float _Delta)
{

}