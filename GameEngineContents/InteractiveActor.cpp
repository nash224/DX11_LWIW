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

// ��ȣ�ۿ� ���� ����, ��ġ ����
void InteractiveActor::CreateAndSetCollision(ECOLLISION _Order, const float4& _Scale, const float4& _Position, ColType _Type)
{
	m_InteractiveCol = CreateComponent<GameEngineCollision>(_Order);
	m_InteractiveCol->Transform.SetLocalScale(_Scale);
	m_InteractiveCol->Transform.SetLocalPosition(_Position);
	m_InteractiveCol->SetCollisionType(_Type);
}

// ���� ��ȣ�ۿ� ����
void InteractiveActor::SetNearInteractivePositionAndRange(const float4& _InteractivePosition, float _Range)
{
	if (EINTERACTION_TYPE::Near != m_InteractionType)
	{
		m_InteractionType = EINTERACTION_TYPE::Near;
	}

	m_InteractiveLocalPosition = _InteractivePosition;

	m_InteractiveRange = _Range;

	if (_Range < 0.0f)
	{
		m_InteractiveRange = 0.0f;
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
	return m_PressType;
}

ETOOLTYPE InteractiveActor::GetCollectionToolType() const
{
	return m_CollectionTool;
}

// ��������� ���Ե� ���� ���� 
void InteractiveActor::ApplyDepth(const float4& _Position)
{
	float4 Position = _Position;
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("��� �Ŵ����� ���� ���մϴ�");
		return;
	}

	float ZSort = BackDrop_PlayLevel::MainBackDrop->ZSort(Position.Y + m_DepthBias);
	Position.Z = ZSort;

	Transform.SetLocalPosition(Position);
}
