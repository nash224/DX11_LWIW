#include "PreCompile.h"
#include "Ellie.h"

#include "ContentsMath.h"

#include "BackDrop.h"

#include "ContentsEvent.h"
#include "Extractor.h"
#include "UI_Hub_Tool.h"
#include "UI_ProcessManager.h"
#include "BaseLift.h"

static constexpr const float RunCost = 2.0f;

void Ellie::StartIdle()
{
	if (EELLIE_STATUS::Riding == g_Status)
	{
		OnRideFx();
		SFXFunction::PlaySFX("SFX_Broomstick_Ride_03.wav");
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
	StateTime = 0.0f;

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

	if (ECOLLECTION_METHOD::MongSiri == OtherEntity->GetCollectionMethod())
	{
		OtherEntity->GetCaught();
	}

	IsControl = false;	// �ٰ����� �ൿ�� �Ҷ� ������ �Ұ����մϴ�.
	IsCollected = false; // �ش� �ڿ��� �����ߴ��� Ȯ���մϴ�.

	// ������ �ٶ󺸴� ������ ���մϴ�.
	const float4 VectorToOther = OtherEntity->GetInteractiveLocalPositon() - Transform.GetLocalPosition();
	DirectionFunction::GetDirectionToVector(VectorToOther);

	ChangeAnimationByDirection("Walk");
}

void Ellie::StartLift()
{
	OtherEntity = nullptr;
	if (true == BaseLift::MainLiftPtr.expired())
	{
		MsgBoxAssert("������Ƽ� �������� �ʽ��ϴ�.");
		return;
	}
	BaseLift::MainLiftPtr.lock()->ActiveEv();
	ChangeAnimationByDirection("Idle");
}

void Ellie::StartButterflyNet()
{
	if (nullptr == NetCollision)
	{
		MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
		return;
	}
	NetCollision->On();

	const float NetCost = 5.0f;
	Stamina -= NetCost;

	ChangeAnimationByDirection("ButterflyNet");
}
void Ellie::StartRootUp()
{
	const float RootUpCost = 20.0f;
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
	const float MongsiriCost = 20.0f;
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

	OtherEntity->ReachThis();

	IsWaitDone = false;
	isFinishWork = false;

	ChangeAnimationByDirection("Idle");
}

void Ellie::StartJuicy()
{
	const float JuicyCost = 10.0f;
	Stamina -= JuicyCost;

	if (nullptr != BodyRenderer && nullptr == BodyRenderer->FindAnimation("Ellie_Basic_Juicy"))
	{
		BodyRenderer->CreateAnimation("Ellie_Basic_Juicy", "DownFloor_Extractor_0.png", 0.2f, 12, 19, false);
		BodyRenderer->FindAnimation("Ellie_Basic_Juicy")->Inter = { 0.14f, 0.14f, 0.12f, 0.18f, 0.19f, 0.2f, 0.21f, 0.2f };

		BodyRenderer->SetStartEvent("Ellie_Basic_Juicy", [&](GameEngineSpriteRenderer* _Renderer)
			{
				ShadowRenderer->SetSprite("DownFloor_Extractor_0.png", 10);
			});
		BodyRenderer->SetFrameEvent("Ellie_Basic_Juicy", 14, [&](GameEngineSpriteRenderer* _Renderer)
			{
				ShadowRenderer->ChangeCurSprite(11);
			});
		BodyRenderer->SetFrameEvent("Ellie_Basic_Juicy", 19, [&](GameEngineSpriteRenderer* _Renderer)
			{
				ShadowRenderer->ChangeCurSprite(10);
			});
	}

	isPull = false;

	ChangeAnimationByDirection("Juicy", false);
}


void Ellie::StartCheer()
{
	SFXFunction::PlaySFX("SFX_PenCompleteMelody.wav");

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


	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
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
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);

	CalulationMoveForceToNormalStatus(_Delta, SlowWalk_Speed);
	ApplyMovement(_Delta);
}


void Ellie::UpdateWalk(float _Delta)
{
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

	if (true == InputRidingMode())
	{
		return;
	}

	ChangeDirectionAnimation("Walk");
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);

	CalulationMoveForceToNormalStatus(_Delta, Walk_Speed);
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
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);

	const float RunCostCoolDown = 0.5f;

	StateTime += _Delta;
	if (StateTime > RunCostCoolDown)
	{
		StateTime -= RunCostCoolDown;
		Stamina -= RunCost;
	}

	CalulationMoveForceToNormalStatus(_Delta, Run_Speed);
	ApplyMovement(_Delta);
}


void Ellie::UpdateThrow(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
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

	float4 VectorToOther = OtherEntity->GetInteractiveLocalPositon() - Transform.GetLocalPosition();
	const float4 Size = DirectX::XMVector2Length(VectorToOther.DirectXVector);

	bool isInRange = Size.X < OtherEntity->GetInteractiveRange();
	if (isInRange)
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

		if (ECOLLECTION_METHOD::Lift == OtherEntity->GetCollectionMethod())
		{
			ChangeState(EELLIE_STATE::Lift);
			return;
		}
	}
	else
	{
		float4 TargetDircetion = DirectX::XMVector2Normalize(VectorToOther.DirectXVector);
		SetMoveVector(TargetDircetion * Walk_Speed);
		ApplyMovement(_Delta);
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateButterflyNet(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (BodyRenderer->GetCurIndex() > 2)
	{
		CheckNetCollision();
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateRootUp(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	bool isRootStart = (false == isRootup && BodyRenderer->GetCurIndex() >= 4);
	if (isRootStart)
	{
		isRootup = true;
		OtherEntity->IsReach = true;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateSit(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == IsCollected && 4 == BodyRenderer->GetCurIndex())
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("�������� �ʴ� ��ü�� �����Ϸ� �߽��ϴ�.");
			return;
		}

		OtherEntity->IsReach = true;
		IsCollected = true;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	SitShadowUpdate();

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateMongSiri(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == IsCollected && BodyRenderer->GetCurIndex() >= 3)
	{
		if (nullptr == OtherEntity)
		{
			MsgBoxAssert("�������� �ʴ� ��ü�� �����Ϸ� �߽��ϴ�.");
			return;
		}

		OtherEntity->IsReach = true;
		IsCollected = true;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateWait(float _Delta)
{
	if (true == isFinishWork)
	{
		OtherEntity = nullptr;
		IsControl = true;

		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	if (true == IsWaitDone)
	{
		ChangeState(WaitState);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateJuicy(float _Delta)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == isPull && 2 == BodyRenderer->GetCurIndex())
	{
		Extractor* ExtractorPtr = dynamic_cast<Extractor*>(OtherEntity);
		if (nullptr == ExtractorPtr)
		{
			MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
			return;
		}

		// ����⿡�� �������� ��û�մϴ�.
		ExtractorPtr->PullThis();

		isPull = true;
	}

	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Wait);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}

void Ellie::UpdateLift(float _Delta)
{
	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateCheer(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}


void Ellie::UpdateFail(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}

	VirgilRendererHelper.UpdateHelper(BodyRenderer, VirgilRenderer);
}

void Ellie::UpdateDrink(float _Delta)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
}


void Ellie::EndIdle()
{
	if (nullptr == VirgilRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	VirgilRenderer->Off();
}

void Ellie::EndApproach()
{

}

void Ellie::EndButterflyNet()
{
	NetCollision->Off();
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

}



void Ellie::SitShadowUpdate()
{
	if (nullptr == BodyRenderer || nullptr == ShadowRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	switch (BodyRenderer->GetCurIndex())
	{
	case 0:
		ShadowRenderer->ChangeCurSprite(1);
		break;
	case 1:
		ShadowRenderer->ChangeCurSprite(1);
		break;
	case 2:
		ShadowRenderer->ChangeCurSprite(2);
		break;
	case 3:
		ShadowRenderer->ChangeCurSprite(3);
		break;
	case 4:
		ShadowRenderer->ChangeCurSprite(3);
		break;
	case 5:
		ShadowRenderer->ChangeCurSprite(2);
		break;
	default:
		break;
	}
}


bool Ellie::UsingTool()
{
	if (true == GameEngineInput::IsDown('Z', this))
	{
		if (ETOOLTYPE::Dragonfly == UI_Hub_Tool::CurRenderToolType)
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
		if (CoolTime != 0.0f)
		{
			return false;
		}

		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			CoolTime = 0.8f;
			ChangeState(EELLIE_STATE::Riding_Standing);
			return true;
		}
	}

	return false;
}