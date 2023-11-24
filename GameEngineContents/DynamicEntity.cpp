#include "PreCompile.h"
#include "DynamicEntity.h"

#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"

DynamicEntity::DynamicEntity() 
{
}

DynamicEntity::~DynamicEntity() 
{
}


void DynamicEntity::Start()
{
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gathering);
	SetInteractionType(EINTERACTION_TYPE::Near);
}

void DynamicEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void DynamicEntity::Release()
{
	InteractiveActor::Release();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


// 8방향 반환
EDIRECTION DynamicEntity::GetDirectionFromVector(const float4& _MoveVector)
{
	float4 UnitVetor = _MoveVector;
	UnitVetor.Z = 0.0f;
	UnitVetor = UnitVetor.NormalizeReturn();
	float Degree = UnitVetor.Angle2DDeg();

	return GetDirectionToDegree(Degree);
}

// 대각선 방향 반환
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

	MsgBoxAssert("잘못된 반환입니다.");
	return m_Dir;
}

EDIRECTION DynamicEntity::GetDirectionToDegree(const float _Degree)
{
	float Degree = _Degree;

	while (Degree < 0.0f || Degree >= 360.0f)
	{
		if (Degree < 0.0f)
		{
			Degree += 360.0f;
		}
		else if (Degree >= 360.0f)
		{
			Degree -= 360.0f;
		}
	}

	const float Cake16OnePieceDegree = 360.0f / 16.0f;

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

	MsgBoxAssert("잘못된 반환입니다.");
	return m_Dir;
}


// 위치 적용 (깊이 적용)
void DynamicEntity::ApplyMovement(float _Delta)
{
	const float4& MoveVector = m_MoveVector* _Delta;
	Transform.AddLocalPosition(MoveVector);

	InteractiveActor::ApplyDepth();
}

void DynamicEntity::ApplyOnlyMovement(float _Delta)
{
	const float4& MoveVector = m_MoveVector * _Delta;
	Transform.AddLocalPosition(MoveVector);
}

float DynamicEntity::GetVolumeReductionByDistance()
{
	static constexpr const float Max_Volume_Distance = 150.0f;
	static constexpr const float Min_Volume_Distance = 300.0f;

	if (true == CameraControler::MainCameraControler.expired())
	{
		MsgBoxAssert("객체가 존재하지 않습니다.");
		return 0.0f;
	}

	const float4& CameraPos = CameraControler::MainCameraControler.lock()->GetCameraCurrentPostion();
	const float4& MyPos = Transform.GetLocalPosition();
	const float4& VectorToEllie = MyPos - CameraPos;

	const float4& Size = DirectX::XMVector2Length(VectorToEllie.DirectXVector);
	float Distance = Size.X;

	if (Max_Volume_Distance > Distance)
	{
		return 1.0f;
	}
	else if (Max_Volume_Distance < Distance && Distance < Min_Volume_Distance)
	{
		float Volume = (Min_Volume_Distance - Distance) / (Min_Volume_Distance - Max_Volume_Distance);
		return Volume;
	}

	return 0.0f;
}

void DynamicEntity::PlaySFX(std::string_view _FileName)
{
	float Volume = GlobalValue::GetSFXVolume() * GetVolumeReductionByDistance();

	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(_FileName);
	SoundPlayer.SetVolume(Volume);
}