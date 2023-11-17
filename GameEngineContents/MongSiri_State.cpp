#include "PreCompile.h"
#include "MongSiri.h"

#include "BackDrop_PlayLevel.h"

#include "MongSiri_Population.h"
#include "ChubHole.h"
#include "Ellie.h"


void MongSiri::StartIdle()
{
	if (EMONGSIRISTATUS::Normal == Status )
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
		int SelectNumber = RandomClass.RandomInt(0, 4);
		switch (SelectNumber)
		{
		case 0:
			IdleCount  = 2;
			break;
		case 1:
		case 2:
			IdleCount  = 3;
			break;
		case 3:
		case 4:
			IdleCount  = 1;
			break;
		default:
			break;
		}
	}
	if (EMONGSIRISTATUS::Escape == Status )
	{
		IdleCount  = 1;
	}

	ChangeAnimationByDircetion("Idle");
}

void MongSiri::UpdateIdle(float _Delta)
{
	if (true == IsPlayerAround() && EMONGSIRISTATUS::Escape != Status)
	{
		ChangeState(EMONGSIRISTATE::Look);
		return;
	
	}

	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
	{
		--IdleCount ;
	}

	if (IdleCount  <= 0)
	{
		ChangeState(EMONGSIRISTATE::Jump);
		return;
	}
}

void MongSiri::EndIdle()
{
	IdleCount  = 0;
}


void MongSiri::StartJump()
{
	SearchJumpLocation();
	ChangeAnimationByDircetion("Jump");
}

// �� ��Ҹ� ã���ݴϴ�.
void MongSiri::SearchJumpLocation()
{
	if (EMONGSIRISTATUS::Normal == Status )
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());


		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("���ø� ��ü�� �Ŵ����� �������� �ʽ��ϴ�.");
			return;
		}

		const float4& MyPosition = Transform.GetLocalPosition();
		const float4& PopulationPosition = MongSiriParant->m_PopulationLocation;
		
		const float4& VectorToPopulation = PopulationPosition - MyPosition;			// ������ġ�� �� �Ÿ�
		const float Degree = DirectX::XMConvertToDegrees(atan2f(VectorToPopulation.Y, VectorToPopulation.X));

		const float4& Size = DirectX::XMVector2Length(VectorToPopulation.DirectXVector);
		float Distance = Size.X;

		float JumpAngle = 0.0f;

		bool isOutMaxRange = (Distance > MongSiriParant->PopulationMaxRange);
		if (isOutMaxRange)
		{
			JumpAngle = Degree;
		}
		else if (Distance < MongSiriParant->PopulationMinCircle)
		{
			JumpAngle = RandomClass.RandomFloat(0.0f, 360.0f);
		}
		else if (Distance > MongSiriParant->PopulationMinCircle)
		{
			float JumpChangeRatio = RandomClass.RandomFloat(0.0f, 1.0f);
			JumpChangeRatio = static_cast<float>(pow(JumpChangeRatio, 2));
			JumpChangeRatio *= 180.f;

			int MultiValue = RandomClass.RandomInt(0, 1);

			bool isReverseJumpChange = (1 == MultiValue);
			if (isReverseJumpChange)
			{
				JumpChangeRatio *= -1.0f;
			}

			JumpAngle = Degree + JumpChangeRatio;
		}

		const float MongSiriJumpPower = RandomClass.RandomFloat(0.0f, MongSiri_JumpMaxSpeed);
		const float4& TargetUnitVector = float4::GetUnitVectorFromDeg(JumpAngle);

		TargetForce = TargetUnitVector * MongSiriJumpPower;
	}

	if (EMONGSIRISTATUS::Escape == Status )
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("���ø� ��ü���� �������� �ʽ��ϴ�.");
			return;
		}

		if (nullptr == MongSiriParant->Hole)
		{
			MsgBoxAssert("���ø� �����̰� �������� �ʽ��ϴ�.");
			return;
		}

		const float4& HolePosition = MongSiriParant->Hole->Transform.GetLocalPosition();
		float4 TargetPosition = HolePosition - Transform.GetLocalPosition();
		TargetPosition.Z = 0.0f;
		float TargetDistance = TargetPosition.Size();
		
		static constexpr const float Last_Leaping_Power = 40.0f;
		bool isReachHole = (TargetDistance < Last_Leaping_Power);
		if (isReachHole)
		{
			IsOnTheHole = true;
			TargetForce = TargetPosition.NormalizeReturn() * TargetDistance * 1.66f;
		}
		else
		{
			TargetForce = TargetPosition.NormalizeReturn() * MongSiri_JumpMaxSpeed;
		}
	}

	TargetForce.Z = 0.0f;

	m_Dir = GetDiagonalDirectionFromVector(TargetForce);
}

void MongSiri::UpdateJump(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
	{
		if (true == IsOnTheHole)
		{
			ChangeState(EMONGSIRISTATE::Disappear);
			return;
		}

		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}

	bool isJumpFrame = (InteractiveActor::BodyRenderer->GetCurIndex() > 2 && InteractiveActor::BodyRenderer->GetCurIndex() < 9);
	if (isJumpFrame)
	{
		if (nullptr != BackDrop_PlayLevel::MainBackDrop)
		{
			if (true == BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(Transform.GetLocalPosition() + TargetForce * _Delta, GameEngineColor::RED))
			{
				TargetForce = float4::ZERO;
			}
		}

		m_MoveVector = TargetForce;
		DynamicEntity::ApplyMovement(_Delta);
	}
}

void MongSiri::EndJump()
{
	TargetForce = float4::ZERO;
	m_MoveVector = float4::ZERO;
}


// ������ ���� ����
// �������� ���� �����ϴ� ����
// �� �в�
// 

void MongSiri::StartLook()
{
	LookState.ChangeState(ELOOKSTATE::Recognize);
}

void MongSiri::UpdateLook(float _Delta)
{
	LookState.Update(_Delta);
}

void MongSiri::StartRecognize(GameEngineState* _Parent)
{
	Emotion.ShowExclamation();

	ChangeAnimationByDircetion("Look");
}

void MongSiri::UpdateRecognize(float _Delta, GameEngineState* _Parent)
{
	if (EMONGSIRISTATUS::Escape == Status)
	{
		ChangeState(EMONGSIRISTATE::Idle);
		LookState.ChangeState(ELOOKSTATE::None);
		return;
	}

	if (false == IsPlayerAround())
	{
		LookState.ChangeState(ELOOKSTATE::NotRecognize);
		return;
	}

	if (nullptr != InteractiveActor::BodyRenderer)
	{
		if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
		{
			std::weak_ptr<GameEngineFrameAnimation> Animation = InteractiveActor::BodyRenderer->FindAnimation("Look");
			if (true == Animation.expired())
			{
				MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
				return;
			}

			static constexpr float MIN_Inter = 0.2f;
			static constexpr float MAX_Inter = 2.4f;

			GameEngineRandom RandomClass;
			RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
			const float fChance = RandomClass.RandomFloat(MIN_Inter, MAX_Inter);

			Animation.lock()->Inter[3] = fChance;
		}
	}

	AutoChangeDirAnimation("Look");
}


void MongSiri::StartNotRecognize(GameEngineState* _Parent)
{
	// �̸���
}

void MongSiri::UpdateNotRecognize(float _Delta, GameEngineState* _Parent)
{
	static constexpr float LookAtCoolTime = 1.0f;

	if (_Parent->GetStateTime() > LookAtCoolTime || EMONGSIRISTATUS::Escape == Status)
	{
		LookState.ChangeState(ELOOKSTATE::None);
		return;
	}
}

void MongSiri::EndNotRecognize(GameEngineState* _Parent)
{
	ChangeState(EMONGSIRISTATE::Idle);
}


void MongSiri::GetCaught()
{
	ChangeState(EMONGSIRISTATE::Caught);
}

void MongSiri::StartCaught()
{
	m_Dir = EDIRECTION::LEFTDOWN;
	ChangeAnimationByDircetion("Idle");
}

void MongSiri::UpdateCaught(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ChangeState(EMONGSIRISTATE::Collected);
		return;
	}
}

void MongSiri::StartCollected()
{
	if (nullptr == InteractiveCol)
	{
		MsgBoxAssert("�浹ü�� �������� �ʴµ� ����Ϸ� �߽��ϴ�.");
		return;
	}

	

	InteractiveCol->Off();
	ChangeAnimation("Collected");
}

void MongSiri::UpdateCollected(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd() && true == InteractiveActor::BodyRenderer->IsCurAnimation("CollectedB"))
	{
		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}

void MongSiri::EndCollected()
{
	Status = EMONGSIRISTATUS::Escape;

	if (nullptr != MongSiriParant)
	{
		Emotion.UseOnlyExclamation();
		MongSiriParant->EscapeHoleToOtherMonsiri();
	}
}


void MongSiri::StartDisappear()
{
	m_CollectionTool = ETOOLTYPE::None;
	ChangeAnimation("Disappear");
}

void MongSiri::UpdateDisappear(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("���ø� ��ü���� �������� �ʽ��ϴ�.");
			return;
		}

		MongSiriParant->MongSiriEntityList.remove(GetDynamic_Cast_This<MongSiri>());
		Death();
	}
}

void MongSiri::AutoChangeDirAnimation(std::string_view _StateName)
{
	if (nullptr == Ellie::MainEllie)
	{
		return;
	}

	const float4& ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();
	const float4& MyPos = Transform.GetLocalPosition();
	const float4& VectorToEllie = ElliePos - MyPos;
	const float Radian = std::atan2f(VectorToEllie.Y, VectorToEllie.X);
	DynamicEntity::m_Dir = DynamicEntity::GetDirectionToDegree(Radian* GameEngineMath::R2D);

	if (RenderDir != DynamicEntity::m_Dir)
	{
		std::weak_ptr<GameEngineFrameAnimation> Animation = InteractiveActor::BodyRenderer->CurAnimation();
		if (true == Animation.expired())
		{
			MsgBoxAssert("�ִϸ��̼��� �������� �ʽ��ϴ�.");
			return;
		}

		const int currentIndex = Animation.lock()->CurIndex;
		ChangeAnimationByDircetion(_StateName, static_cast<unsigned int>(currentIndex));
	}
}

void MongSiri::ShowEscapeEmotion()
{
	Emotion.ShowExclamation();
	Emotion.UseOnlyExclamation();
}