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
	if (EINTERACTION_TYPE::Near != Option.InteractionType)
	{
		Option.InteractionType = EINTERACTION_TYPE::Near;
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
	const EINTERACTION_TYPE _Type,
	const ECOLLECTION_METHOD _METHODType,
	const ETOOLTYPE _TOOLType
)
{
	Option.ButtonType = _BUTTONTYPE;
	Option.InteractionType = _Type;
	Option.CollectionMethod = _METHODType;
	Option.CollectionTool = _TOOLType;
}

EINTERACTION_TYPE InteractiveActor::GetInteractionType() const
{
	return Option.InteractionType;
}

EINTERACTION_BUTTONTYPE InteractiveActor::GetInteractionButtonType() const
{
	return Option.ButtonType;
}

ECOLLECTION_METHOD InteractiveActor::GetCollectionMethod() const
{
	return Option.CollectionMethod;
}

EINTERACTION_PRESSTYPE InteractiveActor::GetInteractionPressType() const
{
	return Option.InputType;
}

ETOOLTYPE InteractiveActor::GetCollectionToolType() const
{
	return Option.CollectionTool;
}


float InteractiveActor::GetDistance2DToEllie()
{
	const float4 ElliePos = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();
	const float4 MyPos = Parent->Transform.GetLocalPosition();
	const float4 Result = DirectX::XMVector2Length((MyPos - ElliePos).DirectXVector);
	return Result.X;
}