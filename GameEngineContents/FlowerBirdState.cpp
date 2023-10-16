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

// �ൿ����
void FlowerBird::DecideAction()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	int ChoosingNumber = RandomClass.RandomInt(0, 5);

	switch (ChoosingNumber)
	{
	case 0: // 1�� ��
		m_AssignedTurnCount = 1;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 1: // 2�� ��
		m_AssignedTurnCount = 2;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 2: // 3�� ��
		m_AssignedTurnCount = 3;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 3:	// �ɱ�
		m_PickCount = MaxPickCount;
		m_NextState = EFLOWERBIRDSTATE::Pick;
		break;
	case 4: // ����
		m_NextState = EFLOWERBIRDSTATE::Bloom;
		break;
	case 5: // �� �õ�
		m_NextState = EFLOWERBIRDSTATE::BloomFake;
		break;
	default:
		break;
	}

	// ���� �ൿ On���� �ϰ�
	IsActted = true;

	// ���ð� �Ҵ� => ���� : �ɱ��Ҷ� �ð��� �ٸ�
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

// ���� �¿� ��ȯ
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

// �� �ð� �Ҵ�
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}


	if (true == FeelThreatened())
	{
		unsigned int CurIndex = m_Body->GetCurIndex();

		if (CurIndex >= 3)
		{
			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("��� �Ŵ����� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("���� �ٸ��� �𸨴ϴ�.");
		return;
	}

	float4 ElliePosition = Ellie::MainEllie->Transform.GetLocalPosition();
	float4 MyPosition = Transform.GetLocalPosition();

	// �ٸ��� �� ���� ��ġ�� �ݴ�� ���ư�����
	if (ElliePosition.X - MyPosition.X > 0.0f)
	{
		// ���ư� ���� �� ���� ��������
		float FlyDegree = 180.0f - m_FlyDegree;
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(FlyDegree);
		m_Dir = EDIRECTION::RIGHT;
	}
	else
	{
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(m_FlyDegree);
		m_Dir = EDIRECTION::LEFT;
	}

	// �ӵ��� ���� ����
	m_MoveVector = m_BirdFlyDirection * FlowerBirdFlySpeed;
	m_DepthBias = 300.0f;
}

void FlowerBird::UpdateFly(float _Delta)
{
	ApplyMovement(_Delta);

	float4 MyPosition = Transform.GetLocalPosition();

	if (nullptr == GlobalValue::g_CameraControler)
	{
		MsgBoxAssert("���� ī�޶� �������� �ʽ��ϴ�.");
		return;
	}

	float4 CameraPosition = GlobalValue::g_CameraControler->GetCameraCurrentPostion();
	float4 HWinScale = GlobalValue::GetWindowScale();

	// ȭ�� ������ �Ѿ�� �����մϴ�.
	if (MyPosition.X - FlowerBirdExitCameraBias < CameraPosition.X - HWinScale.X)
	{
		Death();
	}

	if (MyPosition.X + FlowerBirdExitCameraBias > CameraPosition.X + HWinScale.X)
	{
		Death();
	}
}

// ���ư� �غ� �մϴ�.
bool FlowerBird::GetReadyToFly()
{
	if (true == FeelThreatened())
	{
		ChangeState(EFLOWERBIRDSTATE::Fly);
		return true;
	}

	return false;
}

// �ٸ��� �ٰ����°� �ٸ��� �����մϴ�.
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

// �ɾ���� Ellie�� �����մϴ�.
bool FlowerBird::RecognizeWalkingEllie()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("���� �÷��̾ �������� �ʽ��ϴ�.");
		return false;
	}
	
	// FlowerBird�� Ellie�� �ٰ����°� Ȯ���ϸ� true �ƴϸ� false
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

// ������ �ڽſ��� Ư������ ���� �ٰ����°� �����մϴ�.
bool FlowerBird::RecognizeEllie()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("���� �÷��̾ �������� �ʽ��ϴ�.");
		return false;
	}

	// FlowerBird�� Ellie�� �ڼ��� ���� �ٰ����°� Ȯ���ϸ� true �ƴϸ� false
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