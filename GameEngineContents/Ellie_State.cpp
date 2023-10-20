#include "PreCompile.h"
#include "Ellie.h"

#include "BackDrop.h"



bool Ellie::InputTestPattern()
{
	if (true == GameEngineInput::IsDown('1', this))
	{
		ChangeState(EELLIE_STATE::Net);
		return true;
	}

	if (true == GameEngineInput::IsDown('2', this))
	{
		ChangeState(EELLIE_STATE::RootUp);
		return true;
	}

	if (true == GameEngineInput::IsDown('3', this))
	{
		ChangeState(EELLIE_STATE::Sit);
		return true;
	}

	if (true == GameEngineInput::IsDown('4', this))
	{
		ChangeState(EELLIE_STATE::MongSiri);
		return true;
	}

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


#pragma region �⺻����
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
	// �������� ������ Idle�� ���·� �����մϴ�.
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

void Ellie::StartRiding_Idle()
{
	if (EELLIE_STATUS::Normal == g_Status)
	{
		m_MoveVector = float4::ZERO;
		m_MoveForce = float4::ZERO;
		OnRideFx();
	}

	g_Status = EELLIE_STATUS::Riding;

	ChangeAnimationByDirection("Riding_Idle");
}

void Ellie::OnRideFx()
{
	if (nullptr == m_Fx)
	{
		MsgBoxAssert("ȿ�� �������� �������� �ʽ��ϴ�.");
		return;
	}
	
	m_Fx->ChangeAnimation("FX", true);
	m_Fx->On();
}


void Ellie::UpdateRiding_Idle(float _Delta)
{
	if (true == IsControl)
	{
		if (true == DetectMovement())
		{
			if (true == GameEngineInput::IsDown(VK_CONTROL, this))
			{
				ChangeState(EELLIE_STATE::Idle);
				return;
			}

			if (true == GameEngineInput::IsPress(VK_SPACE, this))
			{
				ChangeState(EELLIE_STATE::Riding_Boost);
				return;
			}

			ChangeState(EELLIE_STATE::Riding_Move);
			return;
		}
		// �������� �ʾҴٸ�
		else
		{
			if (true == GameEngineInput::IsDown(VK_CONTROL, this))
			{
				ChangeState(EELLIE_STATE::Idle);
				return;
			}
		}
	}
	
	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovement(_Delta);
}


void Ellie::StartRiding_Move()
{
	ChangeAnimationByDirection("Riding_Move");
}

void Ellie::UpdateRiding_Move(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Boost);
			return;
		}
	}
	// �������� �ʾҴٸ�
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}

	ChangeDirectionAnimation("Riding_Move");

	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
	float4 MoveVector = ReturnPostMoveVector(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	EDIRECTION Direction = GetDirectionFromVector(MoveVector);
	EDIRECTION MoveDirection = ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(Direction, MoveVector);
	if (Direction == MoveDirection)
	{
		CONST_Ellie_Riding_Move_Speed;
		if (true == IsOverSpeed(MoveVector.X , CONST_Ellie_Riding_Move_Speed))
		{
			m_MoveForce.X = 0.0f;
		}
		if (true == IsOverSpeed(MoveVector.Y, CONST_Ellie_Riding_Move_Speed))
		{
			m_MoveForce.Y = 0.0f;
		}

		m_MoveVector += m_MoveForce;
	}
	else
	{
		m_MoveVector = float4::ZERO;
	}

	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Move_Speed, CONST_Ellie_Riding_Move_Acceleration_Time);
	ApplyMovement(_Delta);
}


void Ellie::StartRiding_Boost()
{
	ChangeAnimationByDirection("Riding_Boost");
}

void Ellie::UpdateRiding_Boost(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		if (true == GameEngineInput::IsFree(VK_SPACE, this))
		{
			ChangeState(EELLIE_STATE::Riding_Move);
			return;
		}
	}
	// �������� �ʾҴٸ�
	else
	{
		if (true == GameEngineInput::IsDown(VK_CONTROL, this))
		{
			ChangeState(EELLIE_STATE::Idle);
			return;
		}

		ChangeState(EELLIE_STATE::Riding_Idle);
		return;
	}


	ChangeDirectionAnimation("Riding_Boost");
	

	// ������ ������ ���� �������͸� ��ȯ ���ݴϴ�.
	float4 MoveVector = ReturnPostMoveVector(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	EDIRECTION Direction = GetDirectionFromVector(MoveVector);
	EDIRECTION MoveDirection = ReturnPixelCollisionMoveDirectionToCurrentCheckPoint(Direction, MoveVector);
	if (Direction == MoveDirection)
	{
		CONST_Ellie_Riding_Boost_Speed;
		if (true == IsOverSpeed(MoveVector.X, CONST_Ellie_Riding_Boost_Speed))
		{
			m_MoveForce.X = 0.0f;
		}
		if (true == IsOverSpeed(MoveVector.Y, CONST_Ellie_Riding_Boost_Speed))
		{
			m_MoveForce.Y = 0.0f;
		}

		m_MoveVector += m_MoveForce;
	}
	else
	{
		m_MoveVector = float4::ZERO;
	}

	DecelerateAtMidpoint(_Delta, CONST_Ellie_Riding_Boost_Speed, CONST_Ellie_Riding_Boosting_Acceleration_Time);
	ApplyMovement(_Delta);
}


#pragma endregion 


#pragma region ���� ����

// �����ؼ� �����ϴ� �ൿ�Դϴ�.
void Ellie::StartApproach()
{
	if (nullptr == OtherEntity)
	{
		MsgBoxAssert("������ ���Ͱ� �������� �ʽ��ϴ�.");
		return;
	}
	IsControl = false;					// �ٰ����� �ൿ�� �Ҷ� ������ �Ұ����մϴ�.
	IsCollected = false;					// �ش� �ڿ��� �����ߴ��� Ȯ���մϴ�.

	// ������ �ٶ󺸴� ������ ���մϴ�.
	float4 OtherPosition = OtherEntity->GetInteractiveLocalPositon();
	float4 TargetDistance = OtherPosition - Transform.GetLocalPosition();
	m_Dir = GetDirectionFromVector(TargetDistance);

	ChangeAnimationByDirection("Walk");
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

	// ��ǥ�Ÿ����� �̵��մϴ�.
	TargetDistance.Z = 0.0f;
	float4 TargetDircetion = TargetDistance.NormalizeReturn();
	m_MoveVector = TargetDircetion * CONST_Ellie_Walk_Speed;

	ApplyMovement(_Delta);

	// �������� ������ ���� �����մϴ�.
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
	}
}

void Ellie::EndApproach()
{

}

void Ellie::StartNet()
{
	ChangeAnimationByDirection("Net");
}

void Ellie::UpdateNet(float _Delta)
{
	if (true == m_Body->IsCurAnimationEnd())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
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


// �������� �ݴ� �ൿ�����Դϴ�.
void Ellie::StartSit()
{
	ChangeAnimationByDirection("Sit");
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
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (false == IsCollected)
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

void Ellie::EndMongSiri()
{
	OtherEntity = nullptr;
	IsControl = true;
}

#pragma endregion


#pragma region ���� �ִϸ��̼� 

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