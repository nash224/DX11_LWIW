#include "PreCompile.h"
#include "Ellie.h"



void Ellie::StartIdle()
{
	ChangeAnimationByDirection("Idle");
}

void Ellie::UpdateIdle(float _Delta)
{
	if (true == DetectMovement())
	{
		if (true == GameEngineInput::IsPress(VK_LSHIFT))
		{
			return;
		}

		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}

		ChangeState(EELLIE_STATE::Walk);
		return;
	}
}

void Ellie::StartWalk()
{
	ChangeAnimationByDirection("Walk");
}

void Ellie::UpdateWalk(float _Delta)
{
	if (false == DetectMovement())
	{
		ChangeState(EELLIE_STATE::Idle);
		return;
	}
	else
	{
		if (true == GameEngineInput::IsPress(VK_SPACE))
		{
			ChangeState(EELLIE_STATE::Run);
			return;
		}
	}

	float4 Dir = float4::ZERO;

	switch (m_Dir)
	{
	case EDIRECTION::UP:
		Dir = { 0.0f , 1.0f };
		break;
	case EDIRECTION::LEFTUP:
		Dir = { -1.0f , 1.0f };
		Dir.Normalize();
		break;
	case EDIRECTION::LEFT:
		Dir = { -1.0f , 0.0f };
		break;
	case EDIRECTION::LEFTDOWN:
		Dir = { -1.0f , -1.0f };
		Dir.Normalize();
		break;
	case EDIRECTION::RIGHTUP:
		Dir = { 1.0f , 1.0f };
		Dir.Normalize();
		break;
	case EDIRECTION::RIGHT:
		Dir = { 1.0f , 0.0f };
		break;
	case EDIRECTION::RIGHTDOWN:
		Dir = { 1.0f , -1.0f };
		Dir.Normalize();
		break;
	case EDIRECTION::DOWN:
		Dir = { 0.0f , -1.0f };
		break;
	default:
		break;
	}

	Transform.AddLocalPosition(Dir * EllieWalkSpeed * _Delta);

	if (m_Dir != m_RenderDir)
	{
		if (nullptr == m_Body)
		{
			MsgBoxAssert("생성하지 않은 렌더러를 사용하려 했습니다.");
			return;
		}

		unsigned int CurIndex = m_Body->GetCurIndex();
		ChangeAnimationByDirection("Walk", false, CurIndex);
	}
}

void Ellie::StartRun()
{
	ChangeAnimationByDirection("Run");
}

void Ellie::UpdateRun(float _Delta)
{

}