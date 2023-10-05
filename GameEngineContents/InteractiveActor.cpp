#include "PreCompile.h"
#include "InteractiveActor.h"

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

void InteractiveActor::SetInteractionType(EINTERACTIONTYPE _Type)
{
	m_InteractionType = _Type;
}

EINTERACTIONTYPE InteractiveActor::GetInteractionType() const
{
	return m_InteractionType;
}
