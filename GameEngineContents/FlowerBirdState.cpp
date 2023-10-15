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

void FlowerBird::DecideAction()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	int ChoosingNumber = RandomClass.RandomInt(0, 5);

	switch (ChoosingNumber)
	{
	case 0:
		m_TurnCount = 1;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 1:
		m_TurnCount = 2;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 2:
		m_TurnCount = 3;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case 3:
		m_NextState = EFLOWERBIRDSTATE::Pick;
		break;
	case 4:
		m_NextState = EFLOWERBIRDSTATE::Bloom;
		break;
	case 5:
		m_NextState = EFLOWERBIRDSTATE::BloomFake;
		break;
	default:
		break;
	}

	IsActted = true;
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
	ChangeFlowerBirdAnimation("Turn");
}

void FlowerBird::UpdateTurn(float _Delta)
{

}


void FlowerBird::StartPick()
{
	ChangeFlowerBirdAnimation("Pick");
}

void FlowerBird::UpdatePick(float _Delta)
{

}


void FlowerBird::StartBloom()
{
	ChangeFlowerBirdAnimation("Bloom");
}

void FlowerBird::UpdateBloom(float _Delta)
{

}


void FlowerBird::StartBloomFake()
{
	ChangeFlowerBirdAnimation("BloomFake");
}

void FlowerBird::UpdateBloomFake(float _Delta)
{

}


void FlowerBird::StartBloomFlowers()
{
	ChangeFlowerBirdAnimation("BloomFlowers");
}

void FlowerBird::UpdateBloomFlowers(float _Delta)
{

}

void FlowerBird::StartFly()
{
	ChangeFlowerBirdAnimation("Fly");
}

void FlowerBird::UpdateFly(float _Delta)
{

}


