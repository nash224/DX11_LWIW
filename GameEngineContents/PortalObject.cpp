#include "PreCompile.h"
#include "PortalObject.h"

PortalObject::PortalObject() 
{
}

PortalObject::~PortalObject() 
{
}


void PortalObject::Start()
{

}

void PortalObject::Update(float _Delta)
{
	if (true == IsColliding)
	{
		m_CallBack();
		GameEngineCore::ChangeLevel(m_ChangeLevelName);
	}
}

void PortalObject::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void PortalObject::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void PortalObject::CreatePortalCollision(int _Order)
{
	PotalCol = CreateComponent<GameEngineCollision>(_Order);
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("컴포넌트를 생성하지 못했습니다.");
		return;
	}
}


void PortalObject::SetLocalPosition(const float4& _Location)
{
	Transform.SetLocalPosition(_Location);
}

void PortalObject::SetCollisionRange(const float4& _Scale)
{
	m_ColScale = _Scale;
	Transform.SetLocalScale(_Scale);
}

void PortalObject::SetCollisionType(ColType _Type)
{
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않는데 타입을 변경하려 했습니다.");
		return;
	}

	PotalCol->SetCollisionType(_Type);
}

void PortalObject::SetChangeLevelName(std::string_view _LevelName)
{
	m_ChangeLevelName = _LevelName.data();
}


void PortalObject::SetCollisionFlag(bool _Flag)
{
	IsColliding = _Flag;
}

bool PortalObject::GetCollisionFlag() const
{
	return IsColliding;
}



void PortalObject::ActorRelease()
{
	PotalCol = nullptr;

	Death();
}