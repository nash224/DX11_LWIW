#include "PreCompile.h"
#include "PortalObject.h"

#include "FadeObject.h"

PortalObject::PortalObject()
{
}

PortalObject::~PortalObject()
{
}


void PortalObject::Start()
{
	m_PortalType = PortalType::Instant;
}

void PortalObject::Update(float _Delta)
{
	PortalUpdate();
}


void PortalObject::Release()
{
	PotalCol = nullptr;
}


void PortalObject::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void PortalObject::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void PortalObject::CreatePortalCollision(int _Order)
{
	PotalCol = CreateComponent<GameEngineCollision>(_Order);
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다..");
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
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}

	PotalCol->SetCollisionType(_Type);
}

void PortalObject::SetCollisionData(PortalCollisionParameter _ColParameter)
{
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않습니다.");
		return;
	}

	m_ColScale = _ColParameter.Scale;

	Transform.SetLocalPosition(_ColParameter.Position);
	Transform.SetLocalScale(_ColParameter.Scale);

	PotalCol->SetCollisionType(_ColParameter.CollisionType);
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





void PortalObject::PortalUpdate()
{
	if (true == IsColliding)
	{
		CallFadeOut();
		IsColliding = false;

		if (nullptr == PotalCol)
		{
			MsgBoxAssert("충돌체가 존재하지 않습니다.");
			return;
		}

		PotalCol->Off();
	}
}


void PortalObject::CallFadeOut()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	FadeObject::CallFadeOut(CurLevel, m_ChangeLevelName, 0.4f);
}
