#include "PreCompile.h"
#include "DynamicEntity.h"

#include "BackDrop_PlayLevel.h"

DynamicEntity::DynamicEntity() 
{
}

DynamicEntity::~DynamicEntity() 
{
}


void DynamicEntity::Start()
{
	m_InteractionButtonType = EINTERACTION_BUTTONTYPE::Gathering;
	m_InteractionType = EINTERACTION_TYPE::Near;
}

void DynamicEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void DynamicEntity::Release()
{
	InteractiveActor::Release();

	m_Body = nullptr;
}


void DynamicEntity::LevelStart(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelStart(_NextLevel);
}

void DynamicEntity::LevelEnd(class GameEngineLevel* _NextLevel)
{
	InteractiveActor::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// 8���� ��ȯ
EDIRECTION DynamicEntity::GetDirectionFromVector(const float4& _MoveVector)
{
	float4 UnitVetor = _MoveVector;
	UnitVetor.Z = 0.0f;
	UnitVetor = UnitVetor.NormalizeReturn();
	float Degree = UnitVetor.Angle2DDeg();
	if (UnitVetor.Y < 0)
	{
		Degree = 180.0f - Degree;
		Degree += 180.0f;
	}

	float Cake16OnePieceDegree = 360.0f / 16.0f;

	if (Degree <= Cake16OnePieceDegree || Degree >= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHT;
	}

	if (Degree > Cake16OnePieceDegree * 1.0f && Degree <= Cake16OnePieceDegree * 3.0f)
	{
		return EDIRECTION::RIGHTUP;
	}

	if (Degree > Cake16OnePieceDegree * 3.0f && Degree <= Cake16OnePieceDegree * 5.0f)
	{
		return EDIRECTION::UP;
	}

	if (Degree > Cake16OnePieceDegree * 5.0f && Degree <= Cake16OnePieceDegree * 7.0f)
	{
		return EDIRECTION::LEFTUP;
	}

	if (Degree > Cake16OnePieceDegree * 7.0f && Degree <= Cake16OnePieceDegree * 9.0f)
	{
		return EDIRECTION::LEFT;
	}

	if (Degree > Cake16OnePieceDegree * 9.0f && Degree <= Cake16OnePieceDegree * 11.0f)
	{
		return EDIRECTION::LEFTDOWN;
	}

	if (Degree > Cake16OnePieceDegree * 11.0f && Degree <= Cake16OnePieceDegree * 13.0f)
	{
		return EDIRECTION::DOWN;
	}

	if (Degree > Cake16OnePieceDegree * 13.0f && Degree <= Cake16OnePieceDegree * 15.0f)
	{
		return EDIRECTION::RIGHTDOWN;
	}

	MsgBoxAssert("�߸��� ��ȯ�Դϴ�.");
	return m_Dir;
}

// �밢�� ���� ��ȯ
EDIRECTION DynamicEntity::GetDiagonalDirectionFromVector(const float4& _MoveVector)
{
	float4 UnitVetor = _MoveVector;
	UnitVetor.Z = 0.0f;
	UnitVetor = UnitVetor.NormalizeReturn();
	float Degree = UnitVetor.Angle2DDeg();
	if (UnitVetor.Y < 0)
	{
		Degree = 180.0f - Degree;
		Degree += 180.0f;
	}
	
	if (Degree >= 0.0f && Degree < 90.0f)
	{
		return EDIRECTION::RIGHTUP;
	}
	else if (Degree >= 90.0f && Degree < 180.0f)
	{
		return EDIRECTION::LEFTUP;
	}
	else if (Degree >= 180.0f && Degree < 270.0f)
	{
		return EDIRECTION::LEFTDOWN;
	}
	else 
	{
		return EDIRECTION::RIGHTDOWN;
	}

	MsgBoxAssert("�߸��� ��ȯ�Դϴ�.");
	return m_Dir;
}




// ��ġ ���� (���� ����)
void DynamicEntity::ApplyMovement(float _Delta)
{
	float4 CurrentPosition = Transform.GetLocalPosition();					// ������ġ
	m_MoveVector.Z = 0.0f;
	float4 MoveVector = m_MoveVector* _Delta;								// �̵���
	float4 MovePosition = CurrentPosition + MoveVector;						// �̷� ��ġ
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("nullptr == BackDrop_PlayLevel::MainBackDrop");
		return;
	}

	float Depth = BackDrop_PlayLevel::MainBackDrop->ZSort(MovePosition.Y + m_DepthBias);	// ���� ���
	MovePosition.Z = Depth;
	
	Transform.SetLocalPosition(MovePosition);
}