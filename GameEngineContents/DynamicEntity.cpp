#include "PreCompile.h"
#include "DynamicEntity.h"

#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "ContentsMath.h"

DynamicEntity::DynamicEntity() 
{
}

DynamicEntity::~DynamicEntity() 
{
}


void DynamicEntity::Start()
{
	InteractiveActor::SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gathering);
	InteractiveActor::SetInteractionType(EINTERACTION_TYPE::Near);
}

void DynamicEntity::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);
}

void DynamicEntity::Release()
{
	InteractiveActor::Release();
}


// 위치 적용 (깊이 적용)
void DynamicEntity::ApplyMovement(float _Delta)
{
	const float4 Vector = GetMoveVector()* _Delta;
	Transform.AddLocalPosition(Vector);

	InteractiveActor::ApplyDepth();
}

void DynamicEntity::ApplyOnlyMovement(float _Delta)
{
	const float4 Vector = m_MoveVector * _Delta; // 확인용
	Transform.AddLocalPosition(Vector);
}

float DynamicEntity::GetVolumeReductionByDistance() const
{
	const float MaxVolume = 150.0f;
	const float MinVolume = 300.0f;

	const float4 VectorToCamera = Transform.GetLocalPosition() - PlayLevel::GetPlayLevelPtr()->GetLevelCameraPtr()->GetCameraCurrentPostion();
	const float4 Size = DirectX::XMVector2Length(VectorToCamera.DirectXVector);
	const float Distance = Size.X;

	if (MaxVolume > Distance)
	{
		return 1.0f;
	}
	else if (MaxVolume < Distance && Distance < MinVolume)
	{
		float VolumeRatio = (MinVolume - Distance) / (MinVolume - MaxVolume);
		return VolumeRatio;
	}

	return 0.0f;
}

void DynamicEntity::UpdateSoundVolumeByDistance()
{
	if (true == SoundPlayer.IsPlaying())
	{
		float Volume = GlobalValue::GetSFXVolume() * GetVolumeReductionByDistance();
		SoundPlayer.SetVolume(Volume);
	}
}

void DynamicEntity::StopSFX()
{
	if (true == SoundPlayer.IsPlaying())
	{
		SoundPlayer.Stop();
	}
}