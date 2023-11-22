#include "PreCompile.h"
#include "InteractiveActor.h"
#include "BackDrop_PlayLevel.h"

#include "UI_InterativeMark.h"

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
	if (UI_InterativeMark::Pointer == this)
	{
		UI_InterativeMark::Pointer = nullptr;
	}

	BodyRenderer = nullptr;
	InteractiveCol = nullptr;
}

void InteractiveActor::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void InteractiveActor::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// ��ȣ�ۿ� ���� ����, ��ġ ����
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

// ���� ��ȣ�ۿ� ����
void InteractiveActor::SetNearInteractivePositionAndRange(const float4& _InteractivePosition, float _Range)
{
	if (EINTERACTION_TYPE::Near != m_InteractionType)
	{
		m_InteractionType = EINTERACTION_TYPE::Near;
	}

	m_InteractiveLocalPosition = _InteractivePosition;

	InteractiveRange = _Range;

	if (_Range < 3.0f)
	{
		InteractiveRange = 3.0f;
	}
}


// ��ȣ�ۿ� �ɼ�
void InteractiveActor::SetInteractionButtonType(const EINTERACTION_BUTTONTYPE _Type)
{
	m_InteractionButtonType = _Type;
}

void InteractiveActor::SetInteractionType(const EINTERACTION_TYPE _Type)
{
	m_InteractionType = _Type;
}

// EINTERACTION_BUTTONTYPE  : ��ư
// EINTERACTION_TYPE,		: ��ȣ�ۿ� �Ÿ� (�����̳�, ���Ÿ���)
// ECOLLECTION_METHOD,		: ä�� ���(Ellie)
// ETOOLTYPE				: ����
void InteractiveActor::SetInteractionOption(
	const EINTERACTION_BUTTONTYPE _BUTTONTYPE,
	const EINTERACTION_TYPE _Type,
	const ECOLLECTION_METHOD _METHODType,
	const ETOOLTYPE _TOOLType
)
{
	m_InteractionButtonType = _BUTTONTYPE;
	m_InteractionType = _Type;
	m_CollectionMethod = _METHODType;
	m_CollectionTool = _TOOLType;
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

EINTERACTION_PRESSTYPE InteractiveActor::GetInteractionPressType() const
{
	return PressType;
}

ETOOLTYPE InteractiveActor::GetCollectionToolType() const
{
	return m_CollectionTool;
}

void InteractiveActor::ApplyDepth()
{
	float4 MyPosition = Transform.GetLocalPosition();
	float BackYScale = 0.0f;
	if (nullptr != BackDrop_PlayLevel::MainBackDrop)
	{
		BackYScale = BackDrop_PlayLevel::MainBackDrop->GetBackGroundScale().Y;
	}
	else
	{
		BackYScale = GlobalValue::GetWindowScale().Y;
	}

	float MyDepth = DepthFunction::CalculateObjectDepth(BackYScale, MyPosition.Y + PlusDepth);
	MyPosition.Z = MyDepth;
	
	Transform.SetLocalPosition(MyPosition);
}
