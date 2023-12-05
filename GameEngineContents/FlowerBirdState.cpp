#include "PreCompile.h"
#include "FlowerBird.h"

#include "ContentsMath.h"

#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "Ellie.h"



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
	RandomClass.SetSeed(GlobalValue::GetSeedValue());

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
		AssignedTurnCount = 1;
		TurnCount = AssignedTurnCount;
		NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::TwoTurn:
		AssignedTurnCount = 2;
		TurnCount = AssignedTurnCount;
		NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::ThreeTurn:
		AssignedTurnCount = 3;
		TurnCount = AssignedTurnCount;
		NextState = EFLOWERBIRDSTATE::Turn;
		break;
	case EBIRDACTION::Pick:
		PickCount = MaxPickCount;
		NextState = EFLOWERBIRDSTATE::Pick;
		break;
	case EBIRDACTION::Bloom:
		NextState = EFLOWERBIRDSTATE::Bloom;
		break;
	case EBIRDACTION::BloomFake:
		NextState = EFLOWERBIRDSTATE::BloomFake;
		break;
	default:
		break;
	}

	IsActted = true;

	const float IdleWaitTime = 0.6f;
	IdleTime = IdleWaitTime;
}

void FlowerBird::UpdateIdle(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}

	m_StateTime += _Delta;
	if (m_StateTime > IdleTime)
	{
		ChangeState(NextState);
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
	if (1 == AssignedTurnCount)
	{
		TurnTime = FlowerBirdTurnFastTime;
	}

	if (2 == AssignedTurnCount)
	{
		switch (TurnCount)
		{
		case 1:
			TurnTime = FlowerBirdTurnFastTime;
			break;
		case 2:
			TurnTime = FlowerBirdTurnSlowTime;
			break;
		default:
			break;
		}
	}

	if (3 == AssignedTurnCount)
	{
		switch (TurnCount)
		{
		case 1:
			TurnTime = FlowerBirdTurnFastTime;
			break;
		case 2:
			TurnTime = FlowerBirdTurnSlowTime;
			break;
		case 3:
			TurnTime = FlowerBirdTurnFastTime;
			break;
		default:
			break;
		}
	}

	IdleTime = 0.0f;
}

void FlowerBird::UpdateTurn(float _Delta)
{
	if (true == GetReadyToFly())
	{
		return;
	}

	m_StateTime += _Delta;
	if (m_StateTime > TurnTime)
	{
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndTurn()
{
	m_StateTime = 0.0f;
	--TurnCount;

	if (0 == TurnCount)
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

	if (5 != PickCount)
	{
		if (true == BodyRenderer->IsCurAnimationEnd())
		{
			IdleTime = 0.0f;
			ChangeState(EFLOWERBIRDSTATE::Idle);
			return;
		}
	}
	else
	{
		const float PickWaitTime = 0.4f;
		IdleTime = PickWaitTime;
		ChangeState(EFLOWERBIRDSTATE::Idle);
		return;
	}
}

void FlowerBird::EndPick()
{
	m_StateTime = 0.0f;
	--PickCount;
	if (0 == PickCount)
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
	const float MinInter = 0.4f;
	const float MaxInter = 1.6f;

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());
	float WaitTime = RandomClass.RandomFloat(MinInter, MaxInter);

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
		FlyDirVector = float4::GetUnitVectorFromDeg(ReverseFlyDegree);
		Dir = EDIRECTION::RIGHT;
	}
	else
	{
		FlyDirVector = float4::GetUnitVectorFromDeg(FlyDegree);
		Dir = EDIRECTION::LEFT;
	}

	const float FlySpeed = 600.0f;
	m_MoveVector = FlyDirVector * FlySpeed;
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
		if (nullptr != InteractiveActor::InteractiveCol)
		{
			InteractiveActor::InteractiveCol->Off();
		}
		
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
		Emotion.ShowExpression(EMOJITYPE::Exclamation);
		return true;
	}

	if (true == RecognizeWalkingEllie())
	{
		Emotion.ShowExpression(EMOJITYPE::Exclamation);
		return true;
	}

	return false;
}

bool FlowerBird::RecognizeWalkingEllie() const
{
	const std::shared_ptr<Ellie>& MainPlayerPtr = PlayLevel::GetCurLevel()->GetPlayerPtr();
	EELLIE_STATE CurEllieState = MainPlayerPtr->GetState();
	if (EELLIE_STATE::SlowWalk == CurEllieState && EELLIE_STATE::Idle != CurEllieState)
	{
		const float4 MyPosition = Transform.GetLocalPosition();
		const float4 ElliePosition = MainPlayerPtr->Transform.GetLocalPosition();
		const float WalkDetectionRange = 70.0f;

		return ContentMathFunction::IsAround2D(MyPosition, ElliePosition, WalkDetectionRange);
	}
	
	return false;
}

bool FlowerBird::RecognizeEllie() const
{
	const std::shared_ptr<Ellie>& MainPlayerPtr = PlayLevel::GetCurLevel()->GetPlayerPtr();
	EELLIE_STATE CurEllieState = MainPlayerPtr->GetState();
	if (EELLIE_STATE::SlowWalk != CurEllieState && EELLIE_STATE::Idle != CurEllieState)
	{
		float4 MyPosition = Transform.GetLocalPosition();
		float4 ElliePosition = MainPlayerPtr->Transform.GetLocalPosition();
		const float DetectionRange = 120.0f;

		return ContentMathFunction::IsAround2D(MyPosition, ElliePosition, DetectionRange);
	}

	return false;
}