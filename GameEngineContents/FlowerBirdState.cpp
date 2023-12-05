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
	enum class EBIRDACTION
	{
		OneTurn,
		TwoTurn,
		ThreeTurn,
		Pick,
		Bloom,
		BloomFake,
	};

	EBIRDACTION Chance = static_cast<EBIRDACTION>(ChoosingNumber);

	switch (Chance)
	{
	case EBIRDACTION::OneTurn:
		m_AssignedTurnCount = 1;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::TwoTurn:
		m_AssignedTurnCount = 2;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::ThreeTurn:
		m_AssignedTurnCount = 3;
		m_TurnCount = m_AssignedTurnCount;
		m_NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::Pick:
		m_PickCount = MaxPickCount;
		m_NextState = EFLOWERBIRDSTATE::Pick;
		break;
	case EBIRDACTION::Bloom:
		m_NextState = EFLOWERBIRDSTATE::Bloom;
		break;
	case EBIRDACTION::BloomFake:
		m_NextState = EFLOWERBIRDSTATE::BloomFake;
		break;
	default:
		break;
	}

	IsActted = true;

	constexpr float FlowerBirdIdleWaitTime = 0.6f;

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

	InteractiveActor::StopSFX();
	SoundPlayer = SFXFunction::PlaySFX(RandomBirdCrySoundName());

	ChangeFlowerBirdAnimation("Turn");
}

// 방향 좌우 전환
void FlowerBird::SwapDirection()
{
	if (EDIRECTION::LEFT == Dir)
	{
		Dir = EDIRECTION::RIGHT;
	}
	else if (EDIRECTION::RIGHT == Dir)
	{
		Dir = EDIRECTION::LEFT;
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
	constexpr float FlowerBirdPickWaitTime = 0.4f;

	if (true == GetReadyToFly())
	{
		return;
	}

	if (5 != m_PickCount)
	{
		if (true == BodyRenderer->IsCurAnimationEnd())
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
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}


	if (true == FeelThreatened())
	{
		unsigned int CurIndex = BodyRenderer->GetCurIndex();

		if (CurIndex >= 3)
		{
			const std::shared_ptr<BackDrop_PlayLevel>& MainBackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
			if (nullptr == MainBackDropPtr)
			{
				MsgBoxAssert("배경 매니저를 불러오지 못했습니다.");
				return;
			}

			MainBackDropPtr->CreateItem("FlowerBird_Collect", Transform.GetLocalPosition());
		}

		ChangeState(EFLOWERBIRDSTATE::Fly);
		return;
	}


	if (true == BodyRenderer->IsCurAnimationEnd())
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
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BodyRenderer->FindAnimation("BloomFake")->Inter[8] = ReturnWaitWitherInter();

	ChangeFlowerBirdAnimation("BloomFake");
}

float FlowerBird::ReturnWaitWitherInter()
{
	constexpr float FlowerBirdMinWitherInter = 0.4f;
	constexpr float FlowerBirdMaxWitherInter = 1.6f;

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
	

	if (true == BodyRenderer->IsCurAnimationEnd())
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
	if (nullptr == ShadowRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	ShadowRenderer->Off();

	DecideFlyDirection();

	InteractiveActor::StopSFX();
	SoundPlayer = SFXFunction::PlaySFX("SFX_BirdFly_01.wav");

	ChangeFlowerBirdAnimation("Fly");
}

void FlowerBird::DecideFlyDirection()
{
	float4 ElliePosition = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();
	float4 MyPosition = Transform.GetLocalPosition();

	if (ElliePosition.X - MyPosition.X > 0.0f)
	{
		float ReverseFlyDegree = 180.0f - FlyDegree;
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(ReverseFlyDegree);
		Dir = EDIRECTION::RIGHT;
	}
	else
	{
		m_BirdFlyDirection = float4::GetUnitVectorFromDeg(FlyDegree);
		Dir = EDIRECTION::LEFT;
	}

	const float FlySpeed = 600.0f;
	m_MoveVector = m_BirdFlyDirection * FlySpeed;
	PlusDepth = 300.0f;
}

void FlowerBird::UpdateFly(float _Delta)
{
	constexpr float ExitCameraCorrection = 50.0f;

	ApplyMovement(_Delta);
	float4 MyPosition = Transform.GetLocalPosition();
	float4 CameraPosition = PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	float4 HWinScale = GlobalValue::GetWindowScale();

	bool isExitOutOfCamera = (MyPosition.X - ExitCameraCorrection < CameraPosition.X - HWinScale.X);
	if (isExitOutOfCamera)
	{
		Death();
	}

	bool isExitOutOfRightCamera = (MyPosition.X + ExitCameraCorrection > CameraPosition.X + HWinScale.X);
	if (isExitOutOfRightCamera)
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
		Emotion.ShowExclamation();
		return true;
	}

	if (true == RecognizeWalkingEllie())
	{
		Emotion.ShowExclamation();
		return true;
	}

	return false;
}

bool FlowerBird::RecognizeWalkingEllie()
{
	static constexpr float DetectionEllieWalkRange = 70.0f;

	const std::shared_ptr<Ellie>& MainPlayerPtr = PlayLevel::GetCurLevel()->GetPlayerPtr();
	EELLIE_STATE CurEllieState = MainPlayerPtr->GetState();
	if (EELLIE_STATE::SlowWalk == CurEllieState && EELLIE_STATE::Idle != CurEllieState)
	{
		const float4 MyPosition = Transform.GetLocalPosition();
		const float4 ElliePosition = MainPlayerPtr->Transform.GetLocalPosition();
		const float4 Size = DirectX::XMVector2Length((ElliePosition - MyPosition).DirectXVector);

		if (Size.X < DetectionEllieWalkRange)
		{
			return true;
		}
	}
	
	return false;
}

bool FlowerBird::RecognizeEllie()
{
	static constexpr float DetectionEllieRange = 120.0f;

	const std::shared_ptr<Ellie>& MainPlayerPtr = PlayLevel::GetCurLevel()->GetPlayerPtr();
	EELLIE_STATE CurEllieState = MainPlayerPtr->GetState();
	if (EELLIE_STATE::SlowWalk != CurEllieState && EELLIE_STATE::Idle != CurEllieState)
	{
		float4 MyPosition = Transform.GetLocalPosition();
		float4 ElliePosition = MainPlayerPtr->Transform.GetLocalPosition();
		float4 Size = DirectX::XMVector2Length((ElliePosition - MyPosition).DirectXVector);

		if (Size.X < DetectionEllieRange)
		{
 			return true;
		}
	}

	return false;
}