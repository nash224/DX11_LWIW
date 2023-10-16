#include "PreCompile.h"
#include "FlowerBird.h"

#include "Ellie.h"

#include "CameraControler.h"

#include "BackDrop_PlayLevel.h"



void FlowerBird::StartIdle()
{
	if (false == IsActted)
	{
		DecideAction();
	}

	m_StateTime = 0.0f;

	ChangeFlowerBirdAnimation("Idle");
}

// 행동지정
void FlowerBird::DecideAction()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	int ChoosingNumber = RandomClass.RandomInt(0, 5);

	switch (ChoosingNumber)
	{
	case 0: // 1번 턴
		m_AssignedTurnCount = 1;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 1: // 2번 턴
		m_AssignedTurnCount = 2;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 2: // 3번 턴
		m_AssignedTurnCount = 3;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 3:	// 쪼기
		m_PickCount = MaxPickCount;
		m_NextState = EFLOWERBIRDSTATE::Pick;
		break;
	case 4: // 꽃핌
		m_NextState = EFLOWERBIRDSTATE::Bloom;
		break;
	case 5: // 꽃 시듬
		m_NextState = EFLOWERBIRDSTATE::BloomFake;
		break;
	default:
		break;
	}

	// 현재 행동 On으로 하고
	IsActted = true;

	// 대기시간 할당 => 이유 : 쪼기할때 시간이 다름
	m_IdleTime = FlowerBirdIdleWaitTime;
}

void FlowerBird::UpdateIdle(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}

	m_StateTime += _Delta;
	if (m_StateTime > m_IdleTime)
	{
		ChangeState(m_NextState);
		return;
	}
}

void FlowerBird::EndIdle()
{
	m_StateTime = 0.0f;
}


void FlowerBird::StartTurn()
{
	SwapDirection();
	AssignTurnTime();

	ChangeFlowerBirdAnimation("Turn");
}

// 방향 좌우 전환
void FlowerBird::SwapDirection()
{
	if (EDIRECTION::LEFT == m_Dir)
	{
		m_Dir = EDIRECTION::RIGHT;
	}
	else if (EDIRECTION::RIGHT == m_Dir)
	{
		m_Dir = EDIRECTION::LEFT;
	}
}

// 턴 시간 할당
void FlowerBird::AssignTurnTime()
{
	if (1 == m_AssignedTurnCount)
	{
		m_TurnTime = FlowerBirdTurnFastTime;
	}

	if (2 == m_AssignedTurnCount)
	{
		switch (m_TurnCount)
		{
		case 1:
			m_TurnTime = FlowerBirdTurnFastTime;
			break;
		case 2:
			m_TurnTime = FlowerBirdTurnSlowTime;
			break;
		default:
			break;
		}
	}

	if (3 == m_AssignedTurnCount)
	{
		switch (m_TurnCount)
		{
		case 1:
			m_TurnTime = FlowerBirdTurnFastTime;
			break;
		case 2:
			m_TurnTime = FlowerBirdTurnSlowTime;
			break;
		case 3:
			m_TurnTime = FlowerBirdTurnFastTime;
			break;
		default:
			break;
		}
	}

	m_IdleTime = 0.0f;
}

void FlowerBird::UpdateTurn(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}

	m_StateTime += _Delta;
	if (m_StateTime > m_TurnTime)
	{
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndTurn()
{
	m_StateTime = 0.0f;
	--m_TurnCount;

	if (0 == m_TurnCount)
	{
		IsActted = false;
	}
}


void FlowerBird::StartPick()
{
	ChangeFlowerBirdAnimation("Pick");
}

void FlowerBird::UpdatePick(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}

	if (5 != m_PickCount)
	{
		if (true == m_Body->IsCurAnimationEnd())
		{
			m_IdleTime = 0.0f;
			ChangeState(EFLOWERBIRDSTATE::Idle);
			return;
		}
	}
	else
	{
		m_IdleTime = FlowerBirdPickWaitTime;
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndPick()
{
	m_StateTime = 0.0f;
	--m_PickCount;
	if (0 == m_PickCount)
	{
		IsActted = false;
	}
}


void FlowerBird::StartBloom()
{
	ChangeFlowerBirdAnimation("Bloom");
}

void FlowerBird::UpdateBloom(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}


	if (true == FeelThreatened())
	{
		unsigned int CurIndex = m_Body->GetCurIndex();

		if (CurIndex >= 3)
		{
			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("배경 매니저를 불러오지 못했습니다.");
				return;
			}

			BackDrop_PlayLevel::MainBackDrop->CreateItem("FlowerBird_Collect.png", Transform.GetLocalPosition());
		}

		ChangeState(EFLOWERBIRDSTATE::Fly);
		return;
	}


	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndBloom()
{
	IsActted = false;
}


void FlowerBird::StartBloomFake()
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Body->FindAnimation("BloomFake")->Inter[8] = ReturnWaitWitherInter();

	ChangeFlowerBirdAnimation("BloomFake");
}

float FlowerBird::ReturnWaitWitherInter()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	float WaitTime = RandomClass.RandomFloat(FlowerBirdMinWitherInter, FlowerBirdMaxWitherInter);

	return WaitTime;
}

void FlowerBird::UpdateBloomFake(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}
	

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndBloomFake()
{
	IsActted = false;
}


void FlowerBird::StartBloomFlowers()
{
	ChangeFlowerBirdAnimation("BloomFlowers");
}

void FlowerBird::UpdateBloomFlowers(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}
}

void FlowerBird::EndBloomFlowers()
{
	IsActted = false;
}


void FlowerBird::StartFly()
{
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Shadow->Off();

	DecideFlyDirection();

	ChangeFlowerBirdAnimation("Fly");
}

void FlowerBird::DecideFlyDirection()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("메인 앨리를 모릅니다.");
		return;
	}

	float4 ElliePosition = Ellie::MainEllie->Transform.GetLocalPosition();
	float4 MyPosition = Transform.GetLocalPosition();

	// 앨리와 새 백터 위치의 반대로 날아가게함
	if (ElliePosition.X - MyPosition.X > 0.0f)
	{
		// 날아갈 각도 및 렌더 방향지정
		float FlyDegree = 180.0f - m_FlyDegree;
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(FlyDegree);
		m_Dir = EDIRECTION::RIGHT;
	}
	else
	{
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(m_FlyDegree);
		m_Dir = EDIRECTION::LEFT;
	}

	// 속도와 깊이 지정
	m_MoveVector = m_BirdFlyDirection * FlowerBirdFlySpeed;
	m_DepthBias = 300.0f;
}

void FlowerBird::UpdateFly(float _Delta)
{
	ApplyMovement(_Delta);

	float4 MyPosition = Transform.GetLocalPosition();

	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("메인 카메라가 존재하지 않습니다.");
		return;
	}

	float4 CameraPosition = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	float4 HWinScale = GlobalValue::GetWindowScale();

	// 화면 밖으로 넘어가면 정리합니다.
	if (MyPosition.X - FlowerBirdExitCameraBias < CameraPosition.X - HWinScale.X)
	{
		Death();
	}

	if (MyPosition.X + FlowerBirdExitCameraBias > CameraPosition.X + HWinScale.X)
	{
		Death();
	}
}

// 날아갈 준비를 합니다.
bool FlowerBird::GetReadyToFly()
{
	if (true == FeelThreatened())
	{
		ChangeState(EFLOWERBIRDSTATE::Fly);
		return true;
	}

	return false;
}

// 앨리가 다가오는걸 앨리가 감지합니다.
bool FlowerBird::FeelThreatened()
{
	if (true == RecognizeEllie())
	{
		return true;
	}

	if (true == RecognizeWalkingEllie())
	{
		return true;
	}

	return false;
}

// 걸어오는 Ellie를 감지합니다.
bool FlowerBird::RecognizeWalkingEllie()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("메인 플레이어가 존재하지 않습니다.");
		return false;
	}
	
	// FlowerBird가 Ellie가 다가오는걸 확인하면 true 아니면 false
	if (EELLIE_STATE::SlowWalk != Ellie::MainEllie->GetState())
	{
		float4 MyPosition = Transform.GetLocalPosition();
		MyPosition.Z = 0.0f;
		float4 ElliePosition = Ellie::MainEllie->Transform.GetLocalPosition();
		ElliePosition.Z = 0.0f;
		float Size = (ElliePosition - MyPosition).Size();

		if (fabsf(Size) < FlowerBirdEllieWalkDetectionRange)
		{
			return true;
		}
	}

	return false;
}

// 엘리가 자신에게 특정범위 내로 다가오는걸 감지합니다.
bool FlowerBird::RecognizeEllie()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("메인 플레이어가 존재하지 않습니다.");
		return false;
	}

	// FlowerBird가 Ellie가 자세를 낮춰 다가오는걸 확인하면 true 아니면 false
	float4 MyPosition = Transform.GetLocalPosition();
	MyPosition.Z = 0.0f;
	float4 ElliePosition = Ellie::MainEllie->Transform.GetLocalPosition();
	ElliePosition.Z = 0.0f;
	float Size = (ElliePosition - MyPosition).Size();

	if (fabsf(Size) < FlowerBirdEllieDetectionRange)
	{
		return true;
	}

	return false;
}