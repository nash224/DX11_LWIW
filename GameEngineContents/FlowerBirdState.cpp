#include "PreCompile.h"
#include "FlowerBird.h"




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

}

void FlowerBird::EndBloomFlowers()
{
	IsActted = false;
}


void FlowerBird::StartFly()
{
	ChangeFlowerBirdAnimation("Fly");
}

void FlowerBird::UpdateFly(float _Delta)
{

}


