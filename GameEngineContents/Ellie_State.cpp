#include "PreCompile.h"
#include "Ellie.h"

#include "BackDrop.h"

#include "ContentsEvent.h"
#include "Extractor.h"
#include "UI_Hub_Tool.h"
#include "UI_ProcessManager.h"


void Ellie::StartIdle()
{
	if (EELLIE_STATUS::Riding == g_Status)
	{
		OnRideFx();
		Ellie::PlaySFX("SFX_Broomstick_Ride_03.wav");
	}

	g_Status = EELLIE_STATUS::Normal;

	ChangeAnimationByDirection("Idle");
}

void Ellie::StartSlowWalk()
{
	ChangeAnimationByDirection("SlowWalk");
}

void Ellie::StartWalk()
{
	ChangeAnimationByDirection("Walk");
}


void Ellie::StartRun()
{
	m_StateTime = 0.0f;

	ChangeAnimationByDirection("Run");
}

void Ellie::StartThrow()
{
	ChangeAnimationByDirection("Throw");
}

// �����ؼ� �����ϴ� �ൿ�Դϴ�.
void Ellie::StartApproach()
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("������ ���Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	// ����Ÿ���� ���ø��϶�
	if (ECOLLECTION_METHOD::MongSiri == OtherEntity->GetCollectionMethod())
	{
		// ���߰� ��
		OtherEntity->GetCaught();
	}

	IsControl = false;					// �ٰ����� �ൿ�� �Ҷ� ������ �Ұ����մϴ�.
	IsCollected = false;					// �ش� �ڿ��� �����ߴ��� Ȯ���մϴ�.

	// ������ �ٶ󺸴� ������ ���մϴ�.
	float4 OtherPosition = OtherEntity->GetInteractiveLocalPositon();
	float4 TargetDistance = OtherPosition - Transform.GetLocalPosition();
	m_Dir = GetDirectionFromVector(TargetDistance);

	ChangeAnimationByDirection("Walk");
}

void Ellie::StartButterflyNet()
{
	static constexpr const float NetCost = 5.0f;

	Stamina -= NetCost;

	if (nullptr == m_NetCol)
	{
		MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
		return;
	}
	m_NetCol->On();

	ChangeAnimationByDirection("ButterflyNet");
}
void Ellie::StartRootUp()
{
	static constexpr const float RootUpCost = 20.0f;

	Stamina -= RootUpCost;

	isRootup = false;
	ChangeAnimationByDirection("RootUp");
}

// �������� �ݴ� �ൿ�����Դϴ�.
void Ellie::StartSit()
{
	ChangeAnimationByDirection("Sit");
}

void Ellie::StartMongSiri()
{
	static constexpr const float MongsiriCost = 20.0f;

	Stamina -= MongsiriCost;

	ChangeAnimationByDirection("MongSiri");
}

void Ellie::StartWait()
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("��ȣ�ۿ��Ϸ��� ��ü�� �������� �ʽ��ϴ�.");
		return;
	}

	IsWaitDone = false;
	isFinishWork = false;

	OtherEntity->ReachThis();

	ChangeAnimationByDirection("Idle");
}

void Ellie::StartJuicy()
{
	static constexpr const float JuicyCost = 10.0f;

	Stamina -= JuicyCost;

	if (nullptr != m_Body && nullptr == m_Body->FindAnimation("Ellie_Basic_Juicy"))
	{
		m_Body->CreateAnimation("Ellie_Basic_Juicy", "DownFloor_Extractor_0.png", 0.2f, 12, 19, false);
		m_Body->FindAnimation("Ellie_Basic_Juicy")->Inter = { 0.14f, 0.14f, 0.12f, 0.18f, 0.19f, 0.2f, 0.21f, 0.2f };
		m_Body->SetFrameEvent("Ellie_Basic_Juicy", 15, [&](GameEngineSpriteRenderer* _Renerer)
			{
				Extractor* ExtractorPtr = static_cast<Extractor*>(OtherEntity);
				if (nullptr == ExtractorPtr)
				{
					MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
					return;
				}

				// ����⿡�� �������� ��û�մϴ�.
				ExtractorPtr->PullThis();
			});

		m_Body->SetStartEvent("Ellie_Basic_Juicy", [&](GameEngineSpriteRenderer* _Renderer)
			{
				Shadow->SetSprite("DownFloor_Extractor_0.png", 10);
			});
		m_Body->SetFrameEvent("Ellie_Basic_Juicy", 14, [&](GameEngineSpriteRenderer* _Renderer)
			{
				Shadow->ChangeCurSprite(11);
			});
		m_Body->SetFrameEvent("Ellie_Basic_Juicy", 19, [&](GameEngineSpriteRenderer* _Renderer)
			{
				Shadow->ChangeCurSprite(10);
			});
	}

	ChangeAnimationByDirection("Juicy", false);
}


void Ellie::StartCheer()
{
	Ellie::PlaySFX("SFX_PenCompleteMelody.wav");

	ChangeAnimationByDirection("Cheer", false);
}

void Ellie::StartFail()
{
	ChangeAnimationByDirection("Fail", false);
}

void Ellie::StartDrink()
{
	ChangeAnimationByDirection("Drink", false);
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

		if (true == InputRidingMode())
		{
			return;
		}
	}
}


void Ellie::UpdateSlowWalk(float _Delta)
{
	if (true == UsingTool())
	{
		return;
	}

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

	if (true == InputRidingMode())
	{
		return;
	}


	ChangeDirectionAnimation("SlowWalk");

	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_SlowWalk_Speed);
	ApplyMovement(_Delta);
}


void Ellie::UpdateWalk(float _Delta)
{
	InputTestPattern();

	if (true == UsingTool())
	{
		return;
	}

	// �������� ������ Idle�� ���·� �����մϴ�.
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
		ChangeState(EELLIE_STATE::Riding_Standing);
		return;
	}

	ChangeDirectionAnimation("Walk");

	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Walk_Speed);
	ApplyMovement(_Delta);
}


void Ellie::UpdateRun(float _Delta)
{
	if (true == UsingTool())
	{
		return;
	}

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

	if (true == InputRidingMode())
	{
		return;
	}

	ChangeDirectionAnimation("Run");


	static constexpr const float RunCostCoolDown = 0.5f;

	m_StateTime += _Delta;
	if (m_StateTime > RunCostCoolDown)
	{
		static constexpr const float RunCost = 2.0f;

		m_StateTime -= RunCostCoolDown;
		Stamina -= RunCost;
	}


	CalulationMoveForceToNormalStatus(_Delta, CONST_Ellie_Run_Speed);
	ApplyMovement(_Delta);
}


void Ellie::UpdateThrow(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::UpdateApproach(float _Delta)
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("������ ���Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	float4 OtherPosition = OtherEntity->GetInteractiveLocalPositon();
	float4 TargetDistance = OtherPosition - Transform.GetLocalPosition();
	
	const float4 Dist = DirectX::XMVector2Length(TargetDistance.DirectXVector);
	bool isInInterationRange = Dist.X < OtherEntity->GetInteractiveRange();
	if (isInInterationRange)
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
			ChangeState(EELLIE_STATE::Wait);
			return;
		}
	}
	else
	{
		TargetDistance.Z = 0.0f;
		float4 TargetDircetion = TargetDistance.NormalizeReturn();
		m_MoveVector = TargetDircetion * CONST_Ellie_Walk_Speed;
		ApplyMovement(_Delta);
	}
}


void Ellie::UpdateButterflyNet(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
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


void Ellie::UpdateRootUp(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	bool isRootStart = (false == isRootup && m_Body->GetCurIndex() >= 4);
	if (isRootStart)
	{
		isRootup = true;
		OtherEntity->IsReach = true;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::UpdateSit(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == IsCollected && 4 == m_Body->GetCurIndex())
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("�������� �ʴ� ��ü�� �����Ϸ� �߽��ϴ�.");
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

	SitShadowUpdate();
}


void Ellie::UpdateMongSiri(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == IsCollected && m_Body->GetCurIndex() >= 3)
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("�������� �ʴ� ��ü�� �����Ϸ� �߽��ϴ�.");
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


void Ellie::UpdateWait(float _Delta)
{
	// ����ϸ�
	if (true == isFinishWork)
	{
		OtherEntity = nullptr;
		IsControl = true;

		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	// ������ ���� ����
	if (true == IsWaitDone)
	{
		ChangeState(WaitState);
		return;
	}
}


void Ellie::UpdateJuicy(float _Delta)
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Wait);
		return;
	}
}


void Ellie::UpdateCheer(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::UpdateFail(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}

void Ellie::UpdateDrink(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::EndIdle()
{
	if (nullptr == Virgil)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	Virgil->Off();
}

void Ellie::EndApproach()
{

}

void Ellie::EndButterflyNet()
{
	m_NetCol->Off();
}


void Ellie::EndRootUp()
{
	OtherEntity = nullptr;
	IsControl = true;
}


void Ellie::EndSit()
{
	OtherEntity = nullptr;
	IsControl = true;
}


void Ellie::EndMongSiri()
{
	OtherEntity = nullptr;
	IsControl = true;
}

void Ellie::EndWait()
{
	WaitState = EELLIE_STATE::None;
	isFinishWork = true;
	IsWaitDone = true;
}

void Ellie::EndJuicy()
{
	if (nullptr == UI_ProcessManager::ProcessManager)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	UI_ProcessManager::ProcessManager->JuicyDone();
}



void Ellie::SitShadowUpdate()
{
	if (nullptr == m_Body)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == Shadow)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	const int CurBodyIndex = m_Body->GetCurIndex();

	switch (CurBodyIndex)
	{
	case 0:
		Shadow->ChangeCurSprite(1);
		break;
	case 1:
		Shadow->ChangeCurSprite(1);
		break;
	case 2:
		Shadow->ChangeCurSprite(2);
		break;
	case 3:
		Shadow->ChangeCurSprite(3);
		break;
	case 4:
		Shadow->ChangeCurSprite(3);
		break;
	case 5:
		Shadow->ChangeCurSprite(2);
		break;
	default:
		break;
	}
}




bool Ellie::InputTestPattern()
{
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
			ChangeState(EELLIE_STATE::ButterflyNet);
			return true;
		}
	}

	return false;
}

bool Ellie::InputRidingMode()
{
	if (true == ContentsEvent::HasWitchBroom)
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Riding_Standing);
			return true;
		}
	}

	return false;
}