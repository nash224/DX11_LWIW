#include "PreCompile.h"
#include "MongSiri.h"

#include "ContentsMath.h"

#include "BackDrop_PlayLevel.h"

#include "MongSiri_Population.h"
#include "ChubHole.h"
#include "Ellie.h"


static constexpr float MongSiri_FOVSize = 90.0f;

void MongSiri::StartIdle()
{
	if (nullptr != MongSiriParant && EPOPULATIONSTATE::Normal == MongSiriParant->GetState())
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(GlobalValue::GetSeedValue());
		switch (RandomClass.RandomInt(0, 4))
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

	if (nullptr != MongSiriParant && EPOPULATIONSTATE::Escape == MongSiriParant->GetState())
	{
		IdleCount  = 1;
	}

	ChangeAnimationByDircetion("Idle");
	ShadowRenderHelper.SetSameAnimation(BodyRenderer, ShadowRenderer);
	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}

void MongSiri::StartJump()
{
	SearchJumpLocation();
	ChangeAnimationByDircetion("Jump");
	ShadowRenderHelper.SetSameAnimation(BodyRenderer, ShadowRenderer);
	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}

void MongSiri::StartLook()
{
	LookState.ChangeState(ELOOKSTATE::Recognize);
}

void MongSiri::StartCollected()
{
	if (nullptr == InteractiveCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	InteractiveCol->Off();
	ChangeAnimation("Collected");
}

void MongSiri::StartRecognize(GameEngineState* _Parent)
{
	Emotion.ShowExpression(EMOJITYPE::Question);

	ChangeAnimationByDircetion("Look");
}

void MongSiri::StartCaught()
{
	Dir = EDIRECTION::LEFTDOWN;
	ChangeAnimationByDircetion("Idle");
}

void MongSiri::StartDisappear()
{
	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->Off();
	}

	ChangeAnimation("Disappear");
	ShadowRenderHelper.SetSameAnimation(BodyRenderer, ShadowRenderer);
	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}

void MongSiri::UpdateIdle(float _Delta)
{
	if (true == IsPlayerAround(MongSiri_FOVSize) && nullptr != MongSiriParant && EPOPULATIONSTATE::Normal == MongSiriParant->GetState())
	{
		ChangeState(EMONGSIRISTATE::Look);
		return;

	}

	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
	{
		--IdleCount;
	}

	if (IdleCount <= 0)
	{
		ChangeState(EMONGSIRISTATE::Jump);
		return;
	}

	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}

void MongSiri::UpdateJump(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
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
		if (true == ContentsActor::WallCheck(6.0f))
		{
			ResetMoveVector();
		}

		InteractiveActor::ApplyMovement(_Delta);
	}

	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}

void MongSiri::UpdateLook(float _Delta)
{
	LookState.Update(_Delta);
}


void MongSiri::UpdateRecognize(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != MongSiriParant && EPOPULATIONSTATE::Escape == MongSiriParant->GetState())
	{
		ChangeState(EMONGSIRISTATE::Idle);
		LookState.ChangeState(ELOOKSTATE::None);
		return;
	}

	if (false == IsPlayerAround(MongSiri_FOVSize))
	{
		Emotion.ShowExpression(EMOJITYPE::Question);
		LookState.ChangeState(ELOOKSTATE::NotRecognize);
		return;
	}

	if (nullptr != InteractiveActor::BodyRenderer)
	{
		if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
		{
			const std::shared_ptr<GameEngineFrameAnimation>& Animation = InteractiveActor::BodyRenderer->FindAnimation("Look");
			if (nullptr == Animation)
			{
				MsgBoxAssert("포인터가 존재하지 않습니다.");
				return;
			}

			GameEngineRandom RandomClass;
			RandomClass.SetSeed(GlobalValue::GetSeedValue());

			Animation->Inter.at(3) = RandomClass.RandomFloat(0.2f, 2.4f);
		}
	}

	AutoChangeDirAnimation("Look");
}


void MongSiri::UpdateNotRecognize(float _Delta, GameEngineState* _Parent)
{
	const float LookAtCoolTime = 1.0f;

	if (_Parent->GetStateTime() > LookAtCoolTime || (nullptr != MongSiriParant && EPOPULATIONSTATE::Escape == MongSiriParant->GetState()))
	{
		LookState.ChangeState(ELOOKSTATE::None);
		return;
	}
}


void MongSiri::UpdateCaught(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		ChangeState(EMONGSIRISTATE::Collected);
		return;
	}
}


void MongSiri::UpdateCollected(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd()
		&& true == InteractiveActor::BodyRenderer->IsCurAnimation("CollectedB"))
	{
		ChangeState(EMONGSIRISTATE::Idle);
		return;
	}
}

void MongSiri::UpdateDisappear(float _Delta)
{
	if (nullptr == InteractiveActor::BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (true == InteractiveActor::BodyRenderer->IsCurAnimationEnd())
	{
		if (nullptr == MongSiriParant)
		{
			MsgBoxAssert("몽시리 개체군이 존재하지 않습니다.");
			return;
		}

		MongSiriParant->MongSiriEntityList.remove(GetDynamic_Cast_This<MongSiri>());
		Death();
	}

	ShadowRenderHelper.UpdateHelper(BodyRenderer, ShadowRenderer);
}



void MongSiri::EndJump()
{
	ResetMoveVector();
}

void MongSiri::EndNotRecognize(GameEngineState* _Parent)
{
	ChangeState(EMONGSIRISTATE::Idle);
}

void MongSiri::EndIdle()
{
	IdleCount = 0;
}

void MongSiri::EndCollected()
{
	if (nullptr == MongSiriParant)
	{
		MsgBoxAssert("몽시리 개채군을 불러올 수 없습나다.");
		return;
	}

	MongSiriParant->EscapeHoleToOtherMonsiri();
}


// 뛸 장소를 찾아줍니다.
void MongSiri::SearchJumpLocation()
{
	if (nullptr == MongSiriParant)
	{
		MsgBoxAssert("몽시리 개체군 매니저가 존재하지 않습니다.");
		return;
	}

	if (EPOPULATIONSTATE::Normal == MongSiriParant->GetState())
	{
		GameEngineRandom RandomClass;
		RandomClass.SetSeed(GlobalValue::GetSeedValue());

		const float4 VectorToPopulation = MongSiriParant->PopulationLocation - Transform.GetLocalPosition();
		const float Degree = DirectX::XMConvertToDegrees(atan2f(VectorToPopulation.Y, VectorToPopulation.X));

		const float4 Size = DirectX::XMVector2Length(VectorToPopulation.DirectXVector);
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

			if (1 == RandomClass.RandomInt(0, 1))
			{
				JumpChangeRatio *= -1.0f;
			}

			JumpAngle = Degree + JumpChangeRatio;
		}

		const float JumpPower = RandomClass.RandomFloat(0.0f, JumpMaxPower);
		const float4 TargetUnitVector = float4::GetUnitVectorFromDeg(JumpAngle);

		SetMoveVector(TargetUnitVector * JumpPower);
	}

	if (EPOPULATIONSTATE::Escape == MongSiriParant->GetState())
	{
		if (nullptr == MongSiriParant || nullptr == MongSiriParant->Hole)
		{
			MsgBoxAssert("몽시리 개체군이 존재하지 않습니다.");
			return;
		}

		const float4 VectorToHole = MongSiriParant->Hole->Transform.GetLocalPosition() - Transform.GetLocalPosition();
		const float4 DistanceToHole = DirectX::XMVector2Length(VectorToHole.DirectXVector);

		const float4 TargetVector = DirectX::XMVector2Normalize(VectorToHole.DirectXVector);

		bool isReachHole = (DistanceToHole.X < 40.0f);
		if (isReachHole)
		{
			IsOnTheHole = true;
			SetMoveVector(TargetVector * DistanceToHole.X * 1.66f);
		}
		else
		{
			SetMoveVector(TargetVector * JumpMaxPower);
		}
	}

	Dir = DirectionFunction::GetDiagonalDirectionToVector(GetMoveVector());
}


void MongSiri::ShowEscapeEmotion()
{
	Emotion.ShowExpression(EMOJITYPE::Exclamation);
}