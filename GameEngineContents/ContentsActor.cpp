#include "PreCompile.h"
#include "ContentsActor.h"

#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "ContentsMath.h"
#include "Ellie.h"

ContentsActor::ContentsActor() 
{
}

ContentsActor::~ContentsActor() 
{
}


// 위치 적용 (깊이 적용)
void ContentsActor::ApplyMovement(float _Delta)
{
	ApplyOnlyMovement(_Delta);
	ApplyDepth();
}

void ContentsActor::ApplyOnlyMovement(float _Delta)
{
	const float4 Vector = m_MoveVector * _Delta; // 확인용
	Transform.AddLocalPosition(Vector);
}

void ContentsActor::ApplyDepth()
{
	float4 MyPosition = Transform.GetLocalPosition();

	float BackYScale = 0.0f;
	const std::shared_ptr<BackDrop>& BackPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr != BackPtr)
	{
		BackYScale = BackPtr->GetBackGroundScale().Y;
	}
	else
	{
		BackYScale = GlobalValue::GetWindowScale().Y;
	}

	float Depth = DepthFunction::CalculateObjectDepth(BackYScale, MyPosition.Y + PlusDepth);
	MyPosition.Z = Depth;

	Transform.SetLocalPosition(MyPosition);
}

bool ContentsActor::IsPlayerAround(float _Range) const
{
	const float4 PlayerPosition = PlayLevel::GetCurLevel()->GetPlayerPtr()->Transform.GetLocalPosition();

	return ContentMathFunction::IsAround2D(Transform.GetLocalPosition(), PlayerPosition, _Range);
}


void ContentsActor::StopSFX()
{
	if (true == SoundPlayer.IsPlaying())
	{
		SoundPlayer.Stop();
	}
}

void ContentsActor::UpdateSoundVolumeByDistance()
{
	if (true == SoundPlayer.IsPlaying())
	{
		const float Volume = GlobalValue::GetSFXVolume() * GetVolumeReductionByDistance();
		SoundPlayer.SetVolume(Volume);
	}
}

float ContentsActor::GetVolumeReductionByDistance() const
{
	const float MaxVolume = 150.0f;
	const float MinVolume = 370.0f;

	const float4 VectorToCamera = Transform.GetLocalPosition() - PlayLevel::GetCurLevel()->GetLevelCameraPtr()->GetCameraCurrentPostion();
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


std::vector<float4> ContentsActor::GetPixelCheckPoint(float _CheckDistance, const float4& _DirVector)
{
	std::vector<float4> Result;
	Result.reserve(2);

	// 3:1 
	const float4 CheckPoint = _DirVector * _CheckDistance;
	const float4 CrossVector = float4::Cross3D(_DirVector, float4::FORWARD);

	const float4 CheckCrossVector = CrossVector * _CheckDistance / 3.0f;
	const float4 LeftCheckPoint = CheckPoint - CheckCrossVector;
	const float4 RightCheckPoint = CheckPoint + CheckCrossVector;
	Result.push_back(LeftCheckPoint);
	Result.push_back(RightCheckPoint);

	return Result;
}


bool ContentsActor::WallCollision(float _CheckDistance)
{
	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr == BackDropPtr)
	{
		return false;
	}

	if (0.0f == GetMoveVector().X && 0.0f == GetMoveVector().Y)
	{
		return false;
	}

	const float4 DirVector = DirectX::XMVector2Normalize(GetMoveVector().DirectXVector);
	std::vector<float4> PixelCheckPos = GetPixelCheckPoint(_CheckDistance, DirVector);
	if (2 != PixelCheckPos.size())
	{
		MsgBoxAssert("반환값이 잘못된 함수입니다.");
		return false;
	}

	enum class ECHECKENUM
	{
		Left = 0,
		Right = 1,
	};


	const float4 CheckUnitVector = DirectX::XMVector2Normalize(GetMoveVector().DirectXVector);
	const float4 LeftCheckVector = PixelCheckPos.at(static_cast<int>(ECHECKENUM::Left));
	const float4 RightCheckVector = PixelCheckPos.at(static_cast<int>(ECHECKENUM::Right));

	static constexpr int Max_Check_Count = 8;
	float fCount = 0.0f;

	for (; fCount < static_cast<float>(Max_Check_Count); fCount += 0.5f)
	{
		const float4 CheckPos = Transform.GetLocalPosition() + CheckUnitVector * (-fCount);
		const float4 LeftCheckPos = LeftCheckVector + CheckPos;
		const float4 RightCheckPos = RightCheckVector + CheckPos;

		const GameEngineColor LeftColor = BackDropPtr->GetColor(LeftCheckPos);
		const GameEngineColor RightColor = BackDropPtr->GetColor(RightCheckPos);
		bool isWall = (WALLCOLOR == LeftColor || WALLCOLOR == RightColor);
		if (false == isWall)
		{
			break;
		}
		else
		{
			int a = 0;
		}
	}

	if (fCount == 0.0f)
	{
		return false;
	}
	float4 BackVector;
	BackVector.X = -CheckUnitVector.X * fCount;
	BackVector.Y = -CheckUnitVector.Y * fCount;

	Transform.AddLocalPosition(BackVector);
	return true;
}

bool ContentsActor::WallCheck(float _CheckDistance)
{
	const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
	if (nullptr == BackDropPtr)
	{
		return false;
	}

	const float4 DirVector = DirectX::XMVector2Normalize(GetMoveVector().DirectXVector);
	std::vector<float4> PixelCheckPos = GetPixelCheckPoint(_CheckDistance, DirVector);
	if (2 != PixelCheckPos.size())
	{
		MsgBoxAssert("반환값이 잘못된 함수입니다.");
		return false;
	}

	enum class ECHECKENUM
	{
		Left = 0,
		Right = 1,
	};

	const float4 MyPos = Transform.GetLocalPosition();
	const float4 LeftCheckPos = PixelCheckPos.at(static_cast<int>(ECHECKENUM::Left)) + MyPos;
	const float4 RightCheckPos = PixelCheckPos.at(static_cast<int>(ECHECKENUM::Right)) + MyPos;

	const GameEngineColor LeftColor = BackDropPtr->GetColor(LeftCheckPos);
	const GameEngineColor RightColor = BackDropPtr->GetColor(RightCheckPos);
	bool isWall = (WALLCOLOR == LeftColor || WALLCOLOR == RightColor);
	if (false == isWall)
	{
		return false;
	}

	return true;
}