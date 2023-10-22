#include "PreCompile.h"
#include "Ellie.h"

#include "BackDrop.h"
#include "UI_Hub_Tool.h"
#include "Extractor.h"



bool Ellie::InputTestPattern()
{
	if (true == GameEngineInput::IsDown('5', this))
	{
		ChangeState(EELLIE_STATE::Cheer);
		return true;
	}

	if (true == GameEngineInput::IsDown('6', this))
	{
		ChangeState(EELLIE_STATE::Fail);
		return true;
	}

	if (true == GameEngineInput::IsDown('7', this))
	{
		ChangeState(EELLIE_STATE::Drink);
		return true;
	}

	if (true == GameEngineInput::IsDown('8', this))
	{
		ChangeState(EELLIE_STATE::Throw);
		return true;
	}

	return false;
}

bool Ellie::UsingTool()
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		if (ETOOLTYPE::Dragonfly == UI_Hub_Tool::m_CurrentTool)
		{
			ChangeState(EELLIE_STATE::Net);
			return true;
		}
	}

	return false;
}



#pragma region 기본조작
void Ellie::StartIdle()
{
	if (EELLIE_STATUS::Riding == g_Status)
	{
		OnRideFx();
	}

	g_Status = EELLIE_STATUS::Normal;

	ChangeAnimationByDirection("Idle");
}

void Ellie::UpdateIdle(float _Delta)
{
	if (true == IsControl && false == IsHolding)
	{
		if (true == InputTestPattern())
		{
			return;
		}

		if (true == UsingTool())
		{
			return;
		}

		if (true == DetectMovement())
		{
			if (true == GameEngineInput::IsPress(VK_LSHIFT, this))
			{
				ChangeState(EELLIE_STATE::SlowWalk);
				return;
			}

			if (true == GameEngineInput::IsPress(VK_SPACE, this))
			{
				ChangeState(EELLIE_STATE::Run);
				return;
			}

			ChangeState(EELLIE_STATE::Walk);
			return;
		}

		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Riding_Idle);
			return;
		}
	}
}


void Ellie::StartSlowWalk()
{
	ChangeAnimationByDirection("SlowWalk");
}

void Ellie::UpdateSlowWalk(float _Delta)
{
	if (true == UsingTool())
	{
		return;
	}


	// 움직이지 않으면 Idle인 상태로 간주합니다.
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsFree(VK_LSHIFT, this))
		{
			if (true == GameEngineInput::IsPress(VK_SPACE, this))
			{
				ChangeState(EELLIE_STATE::Run);
				return;
			}

			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL, this))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	ChangeDirectionAnimation("SlowWalk");

	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_SlowWalk_Speed);
	ApplyMovement(_Delta);
}


void Ellie::StartWalk()
{
	ChangeAnimationByDirection("Walk");
}

void Ellie::UpdateWalk(float _Delta)
{
	InputTestPattern();

	if (true == UsingTool())
	{
		return;
	}

	// 움직이지 않으면 Idle인 상태로 간주합니다.
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT, this))
		{
			ChangeState(EELLIE_STATE::SlowWalk);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL, this))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	ChangeDirectionAnimation("Walk");

	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Walk_Speed);
	ApplyMovement(_Delta);
}


void Ellie::StartRun()
{
	ChangeAnimationByDirection("Run");
}

void Ellie::UpdateRun(float _Delta)
{
	if (true == UsingTool())
	{
		return;
	}

	InputTestPattern();

	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT, this))
		{
			ChangeState(EELLIE_STATE::SlowWalk);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Walk);
			return;
		}
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL, this))
	{
		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	ChangeDirectionAnimation("Run");


	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Run_Speed);
	ApplyMovement(_Delta);
}



void Ellie::StartThrow()
{
	ChangeAnimationByDirection("Throw");
}

void Ellie::UpdateThrow(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


#pragma region 수집 패턴

// 접근해서 수집하는 행동입니다.
void Ellie::StartApproach()
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("참조한 액터가 존재하지 않습니다.");
		return;
	}

	// 수집타입이 몽시리일때
	if (ECOLLECTION_METHOD::MongSiri == OtherEntity->GetCollectionMethod())
	{
		// 멈추게 함
		OtherEntity->GetCaught();
	}

	IsControl = false;					// 다가가는 행동을 할땐 조작이 불가능합니다.
	IsCollected = false;					// 해당 자원을 수집했는지 확인합니다.

	// 상대방을 바라보는 방향을 구합니다.
	float4 OtherPosition = OtherEntity->GetInteractiveLocalPositon();
	float4 TargetDistance = OtherPosition - Transform.GetLocalPosition();
	m_Dir = GetDirectionFromVector(TargetDistance);

	ChangeAnimationByDirection("Walk");
}

void Ellie::UpdateApproach(float _Delta)
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("참조한 액터가 존재하지 않습니다.");
		return;
	}

	float4 OtherPosition = OtherEntity->GetInteractiveLocalPositon();
	float4 TargetDistance = OtherPosition - Transform.GetLocalPosition();

	// 목표거리까지 이동합니다.
	TargetDistance.Z = 0.0f;
	float4 TargetDircetion = TargetDistance.NormalizeReturn();
	m_MoveVector = TargetDircetion * CONST_Ellie_Walk_Speed;

	ApplyMovement(_Delta);

	// 지정범위 안으로 들어가면 실행합니다.
	if (fabs(TargetDistance.Size()) < OtherEntity->GetInteractiveRange())
	{
		if (ECOLLECTION_METHOD::Sit == OtherEntity->GetCollectionMethod())
		{
			ChangeState(EELLIE_STATE::Sit);
			return;
		}
		
		if (ECOLLECTION_METHOD::RootUp == OtherEntity->GetCollectionMethod())
		{
			ChangeState(EELLIE_STATE::RootUp);
			return;
		}
		
		if (ECOLLECTION_METHOD::MongSiri == OtherEntity->GetCollectionMethod())
		{
			ChangeState(EELLIE_STATE::MongSiri);
			return;
		}

		if (ECOLLECTION_METHOD::Juicy == OtherEntity->GetCollectionMethod())
		{
			ChangeState(EELLIE_STATE::Juicy);
			return;
		}
	}
}

void Ellie::EndApproach()
{

}

void Ellie::StartNet()
{
	if (nullptr == m_NetCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}
	m_NetCol->On();

	ChangeAnimationByDirection("Net");
}

void Ellie::UpdateNet(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (m_Body->GetCurIndex() > 2)
	{
		NetCollision();
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::EndNet()
{
	m_NetCol->Off();
}


void Ellie::StartRootUp()
{
	OtherEntity->IsReach = true;

	ChangeAnimationByDirection("RootUp");
}

void Ellie::UpdateRootUp(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::EndRootUp()
{
	OtherEntity = nullptr;
	IsControl = true;
}


// 아이템을 줍는 행동패턴입니다.
void Ellie::StartSit()
{
	ChangeAnimationByDirection("Sit");
}

void Ellie::UpdateSit(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (false == IsCollected && 4 == m_Body->GetCurIndex())
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("존재하지 않는 객체를 수집하려 했습니다.");
			return;
		}

		OtherEntity->IsReach = true;
		IsCollected = true;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::EndSit()
{
	OtherEntity = nullptr;
	IsControl = true;
}


void Ellie::StartMongSiri()
{
	ChangeAnimationByDirection("MongSiri");
}

void Ellie::UpdateMongSiri(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (false == IsCollected)
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("존재하지 않는 객체를 수집하려 했습니다.");
			return;
		}

		OtherEntity->IsReach = true;
		IsCollected = true;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{

		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::EndMongSiri()
{
	OtherEntity = nullptr;
	IsControl = true;
}


void Ellie::StartJuicy()
{
	if (nullptr != m_Body && nullptr == m_Body->FindAnimation("Juicy"))
	{
		m_Body->CreateAnimation("Juicy", "DownFloor_Extractor_0.png", 0.2f, 12, 19, false);
		m_Body->FindAnimation("Juicy")->Inter = { 0.12f, 0.12f, 0.1f, 0.16f, 0.17f, 0.18f, 0.19f, 0.19f };
		m_Body->SetFrameEvent("Juicy", 15, [&](GameEngineSpriteRenderer* _Renerer)
			{
				Extractor* ExtractorPtr = dynamic_cast<Extractor*>(OtherEntity);
				if (nullptr == ExtractorPtr)
				{
					MsgBoxAssert("다이나믹 캐스팅을 하지 못했습니다.");
					return;
				}

				// 착즙기에게 당겨지라고 요청합니다.
				ExtractorPtr->PullThis();
			});
	}


	ChangeAnimationByDirection("Juicy", false);
}

void Ellie::UpdateJuicy(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::EndJuicy()
{
	OtherEntity = nullptr;
	IsControl = true;
}


#pragma endregion


#pragma region 단일 애니메이션 

void Ellie::StartCheer()
{
	ChangeAnimationByDirection("Cheer", false);
}

void Ellie::UpdateCheer(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::StartFail()
{
	ChangeAnimationByDirection("Fail", false);
}

void Ellie::UpdateFail(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}



void Ellie::StartDrink()
{
	ChangeAnimationByDirection("Drink", false);

}

void Ellie::UpdateDrink(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

#pragma endregion 