#include "PreCompile.h"
#include "PotalObject.h"

PotalObject::PotalObject() 
{
}

PotalObject::~PotalObject() 
{
}


void PotalObject::Start()
{

}

void PotalObject::Update(float _Delta)
{
	UpdateCollision();
}

void PotalObject::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void PotalObject::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void PotalObject::CreateCollision(int _Order)
{
	PotalCol = CreateComponent<GameEngineCollision>(_Order);
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("컴포넌트를 생성하지 못했습니다.");
		return;
	}
}


void PotalObject::SetLocalPosition(const float4& _Location)
{
	Transform.SetLocalPosition(_Location);
}

void PotalObject::SetCollisionRange(const float4& _Scale)
{
	m_ColScale = _Scale;
}




void PotalObject::UpdateCollision()
{
	if (nullptr == PotalCol)
	{
		MsgBoxAssert("충돌체가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	if (true == PotalCol->Collision(EUPDATEORDER::Player))
	{
		Func_();
	}
}




void PotalObject::ActorRelease()
{
	PotalCol = nullptr;

	Death();
}