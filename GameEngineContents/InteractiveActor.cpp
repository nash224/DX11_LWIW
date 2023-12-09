#include "PreCompile.h"
#include "InteractiveActor.h"
#include "BackDrop_PlayLevel.h"

#include "UI_InterativeMark.h"
#include "ContentsMath.h"
#include "Ellie.h"

InteractiveActor::InteractiveActor() 
{
}

InteractiveActor::~InteractiveActor() 
{
}

void InteractiveActor::Update(float _Delta)
{
	IsEnalbeActive = false;

	if (true == IsReach)
	{
		IsEnalbeActive = true;
	}

	IsReach = false;
}

void InteractiveActor::Release()
{
	if (UI_InterativeMark::Pointer == this)
	{
		UI_InterativeMark::Pointer = nullptr;
	}

	BodyRenderer = nullptr;
	InteractiveCol = nullptr;
}

void InteractiveActor::CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type)
{
	if (nullptr == InteractiveCol)
	{
		InteractiveCol = CreateComponent<GameEngineCollision>(_Order);
	}

	InteractiveCol->Transform.SetLocalScale(_Scale);
	InteractiveCol->Transform.SetLocalPosition(_Position);
	InteractiveCol->SetCollisionType(_Type);
}

void InteractiveActor::SetNearInteractivePositionAndRange(const float4& _InteractivePosition, float _Range)
{
	if (EAPPROACH_TYPE::Near != Option.ApproachType)
	{
		Option.ApproachType = EAPPROACH_TYPE::Near;
	}

	InteractiveLocalPosition = _InteractivePosition;

	InteractiveRange = _Range;

	if (_Range < 3.0f)
	{
		InteractiveRange = 3.0f;
	}
}


void InteractiveActor::SetInteractionOption(
	const EINTERACTION_BUTTONTYPE _BUTTONTYPE,
	const EAPPROACH_TYPE _Type,
	const EINTERACTIONTYPE _METHODType,
	const ETOOLTYPE _TOOLType
)
{
	Option.ButtonType = _BUTTONTYPE;
	Option.ApproachType = _Type;
	Option.InteractionType = _METHODType;
	Option.InteractionTool = _TOOLType;
}

EAPPROACH_TYPE InteractiveActor::GetApproachType() const
{
	return Option.ApproachType;
}

EINTERACTION_BUTTONTYPE InteractiveActor::GetInteractionButtonType() const
{
	return Option.ButtonType;
}

EINTERACTIONTYPE InteractiveActor::GetInteractionType() const
{
	return Option.InteractionType;
}

EINTERACTION_INPUTTYPE InteractiveActor::GetInteractionInputType() const
{
	return Option.InputType;
}

ETOOLTYPE InteractiveActor::GetInteractionToolType() const
{
	return Option.InteractionTool;
}


float InteractiveActor::GetDistance2DToEllie()
{
	const float4 ElliePos = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();
	const float4 MyPos = Transform.GetLocalPosition();
	const float4 Result = DirectX::XMVector2Length((MyPos - ElliePos).DirectXVector);
	return Result.X;
}