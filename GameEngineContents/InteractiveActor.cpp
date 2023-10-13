#include "PreCompile.h"
#include "InteractiveActor.h"
#include "BackDrop_PlayLevel.h"

InteractiveActor::InteractiveActor() 
{
}

InteractiveActor::~InteractiveActor() 
{
}


void InteractiveActor::Start()
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
	m_InteractiveCol = nullptr;
}

void InteractiveActor::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void InteractiveActor::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void InteractiveActor::CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type)
{
	m_InteractiveCol = CreateComponent<GameEngineCollision>(_Order);
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_InteractiveCol->Transform.SetLocalScale(_Scale);
	m_InteractiveCol->Transform.SetLocalPosition(_Position);
	m_InteractiveCol->SetCollisionType(_Type);
}

void InteractiveActor::SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type)
{
	m_InteractionButtonType = _Type;
}

void InteractiveActor::SetInteractionType(const EINTERACTION_TYPE _Type)
{
	m_InteractionType = _Type;
}

EINTERACTION_TYPE InteractiveActor::GetInteractionType() const
{
	return m_InteractionType;
}

EINTERACTION_BUTTONTYPE InteractiveActor::GetInteractionButtonType() const
{
	return m_InteractionButtonType;
}

ECOLLECTION_METHOD InteractiveActor::GetCollectionMethod() const
{
	return m_CollectionMethod;
}


void InteractiveActor::InitialDepth(const float4& _Position)
{
	float4 Position = _Position;
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("nullptr == BackDrop_PlayLevel::MainBackDrop");
		return;
	}

	float ZSort = BackDrop_PlayLevel::MainBackDrop->ZSort(Position.Y);
	Position.Z = ZSort;

	Transform.SetLocalPosition(Position);
}


void InteractiveActor::SetInteractivePositionAndRange(const float4& _InteractivePosition, float _Range)
{
	m_InteractiveLocalPosition = _InteractivePosition;
	m_InteractiveRange = _Range;
}