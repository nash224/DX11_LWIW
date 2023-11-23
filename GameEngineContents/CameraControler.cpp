#include "PreCompile.h"
#include "CameraControler.h"


static constexpr float CAMERA_DEPTH = -1000.0f;

std::weak_ptr<CameraControler> CameraControler::MainCameraControler;
CameraControler::CameraControler()
	:MainCameraPointer(nullptr)
	, FocusActorPointer(nullptr)
	, CameraMode(ECAMERAMODE::None)
	, CameraPosInfo({ float4::ZERO })
{
	CameraMode = ECAMERAMODE::None;
}

CameraControler::~CameraControler() 
{
}


void CameraControler::Start()
{
	GameEngineInput::AddInputObject(this);
}

void CameraControler::Update(float _Delta)
{
	if (nullptr == MainCameraPointer)
	{
		MsgBoxAssert("메인카메라를 참조하지 않았습니다.");
		return;
	}

	if (true == MainCameraPointer->IsFreeCamera())
	{
		return;
	}

	UpdateCameraMode(_Delta);
	RenewCameraPosition();
}

void CameraControler::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}


void CameraControler::SetCameraMode(ECAMERAMODE _Mode)
{
	CameraMode = _Mode;
}

void CameraControler::SetLocalPostion(const float4& _Position)
{
	float4 Position = _Position;
	Position.Z = CAMERA_DEPTH;

	MainCameraPointer->Transform.SetLocalPosition(Position);
	RenewCameraPosition();
	CameraPosInfo.MoveDistance = 0.0f;
}

void CameraControler::SetFocusActor(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgBoxAssert("존재하지 않는 액터를 적용하려고 했습니다.");
		return;
	}

	FocusActorPointer = _Actor;
}

void CameraControler::SetBackDropScale(const float4& _Scale)
{
	BackScale = _Scale;
}

void CameraControler::AddCameraPos(const float4& _Position)
{
	const float4& CameraPos = MainCameraPointer->Transform.GetLocalPosition();
	float4 CameraMovePosition = CameraPos + _Position;
	CameraMovePosition.Z = CAMERA_DEPTH;

	MainCameraPointer->Transform.SetLocalPosition(CameraMovePosition);
}

void CameraControler::SetCameraPos(const float4& _Position)
{
	float4 Position = _Position;
	Position.Z = CAMERA_DEPTH;

	MainCameraPointer->Transform.SetLocalPosition(Position);
}

float4 CameraControler::GetCameraWorldPosition() const
{
	if (nullptr == MainCameraPointer)
	{
		MsgBoxAssert("카메라를 연결하세요");
		return float4::ZERO;
	}

	return MainCameraPointer->Transform.GetWorldPosition();
}

void CameraControler::Reset()
{
	CameraPosInfo.PrevPosition = MainCameraPointer->Transform.GetWorldPosition();
	CameraPosInfo.MoveDistance = float4::ZERO;
}

float4 CameraControler::AdjustCameraInitialPosition(const float4& _ActorPos)
{
	if (float4::ZERO == BackScale)
	{
		MsgBoxAssert("배경 넓이을 지정해주지 않고 카메라 플레이 모드를 사용하려 했습니다.");
		return float4();
	}

	if (nullptr == MainCameraPointer)
	{
		MsgBoxAssert("카메라 액터가 존재하지 않는데 사용하려고 했습니다.");
		return float4();
	}

	float4 CurCameraPos = _ActorPos;
	
	const float4& HWinScale = GlobalValue::GetWindowScale().Half();

	const float4& CameraLeftTopPoint = CurCameraPos + float4{ -HWinScale.X , HWinScale.Y };
	const float4& CameraRightBottomPoint = CurCameraPos + float4{ HWinScale.X , -HWinScale.Y };

	bool IsLeftTopCornerInBackScale = true;
	bool IsLeftBottomCornerInBackScale = true;
	bool IsRightTopCornerInBackScale = true;
	bool IsRightBottomCornerInBackScale = true;

	int CornerCountWithinScreen = 0;

	if (CameraLeftTopPoint.X < 0.0f)
	{
		IsLeftTopCornerInBackScale = false;
		IsLeftBottomCornerInBackScale = false;
	}

	if (CameraLeftTopPoint.Y > 0.0f)
	{
		IsLeftTopCornerInBackScale = false;
		IsRightTopCornerInBackScale = false;
	}

	if (CameraRightBottomPoint.X > BackScale.X)
	{
		IsRightTopCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}

	if (CameraRightBottomPoint.Y < -BackScale.Y)
	{
		IsLeftBottomCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}


	if (CameraLeftTopPoint.X > BackScale.X)
	{
		IsLeftTopCornerInBackScale = false;
		IsLeftBottomCornerInBackScale = false;
	}

	if (CameraLeftTopPoint.Y < -BackScale.Y)
	{
		IsLeftTopCornerInBackScale = false;
		IsRightTopCornerInBackScale = false;
	}

	if (CameraRightBottomPoint.X < 0.0f)
	{
		IsRightTopCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}

	if (CameraRightBottomPoint.Y > 0.0f)
	{
		IsLeftBottomCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}



	if (true == IsLeftTopCornerInBackScale)
	{
		++CornerCountWithinScreen;
	}

	if (true == IsLeftBottomCornerInBackScale)
	{
		++CornerCountWithinScreen;
	}

	if (true == IsRightTopCornerInBackScale)
	{
		++CornerCountWithinScreen;
	}

	if (true == IsRightBottomCornerInBackScale)
	{
		++CornerCountWithinScreen;
	}

	if (0 == CornerCountWithinScreen)
	{
		MsgBoxAssert("맵을 벗어난 위치에서 초기화할 수 없습니다.");
		return float4();
	}

	if (1 == CornerCountWithinScreen)
	{
		if (true == IsLeftTopCornerInBackScale)
		{
			CurCameraPos = float4{ BackScale.X - HWinScale.X  , -BackScale.Y + HWinScale.Y };
		}

		if (true == IsLeftBottomCornerInBackScale)
		{
			CurCameraPos = float4{ BackScale.X - HWinScale.X , -HWinScale.Y };
		}

		if (true == IsRightTopCornerInBackScale)
		{
			CurCameraPos = float4{ HWinScale.X , -BackScale.Y + HWinScale.Y };
		}

		if (true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos = float4{ HWinScale.X , -HWinScale.Y };
		}
	}

	if (2 == CornerCountWithinScreen)
	{
		if (true == IsLeftTopCornerInBackScale && true == IsLeftBottomCornerInBackScale)
		{
			CurCameraPos.X = BackScale.X - HWinScale.X;
		}

		if (true == IsLeftTopCornerInBackScale && true == IsRightTopCornerInBackScale)
		{
			CurCameraPos.Y = -BackScale.Y + HWinScale.Y;
		}

		if (true == IsRightTopCornerInBackScale && true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos.X = HWinScale.X;
		}

		if (true == IsLeftBottomCornerInBackScale && true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos.Y = -HWinScale.Y;
		}
	}

	if (3 == CornerCountWithinScreen)
	{
		MsgBoxAssert("있을 수 없는 버그입니다. 값을 확인해보세요.");
		return float4();
	}

	return CurCameraPos;
}


void CameraControler::SetAutoInitialPosition(const float4& _ActorPos)
{
	const float4& AdjustCameraPos = AdjustCameraInitialPosition(_ActorPos);
	MainCameraPointer->Transform.SetLocalPosition(AdjustCameraPos);
}



float4 CameraControler::GetCameraMoveDistance() const
{
	return CameraPosInfo.MoveDistance;
}

float4 CameraControler::GetCameraCurrentPostion() const
{
	return CameraPosInfo.CurPosition;
}

bool CameraControler::IsCameraMove() const
{
	return float4::ZERO != CameraPosInfo.MoveDistance;
}


#pragma region 카메라 모드 업데이트

void CameraControler::UpdateCameraMode(float _Delta)
{
	switch (CameraMode)
	{
	case ECAMERAMODE::None:
	{
		MsgBoxAssert("카메라 모드를 지정하지 않고 사용하려고 했습니다.");
	}
		break;
	case ECAMERAMODE::Play:
		UpdatePlayMode(_Delta);
		break;
	case ECAMERAMODE::Fix:
		UpdateFixMode();
		break;
	case ECAMERAMODE::Cinematic:
		UpdateCinematicMode(_Delta);
		break;
	case ECAMERAMODE::Editor:
		UpdateEditorMode(_Delta);
		break;
	default:
		break;
	}

	float4 CameraPos = MainCameraPointer->Transform.GetLocalPosition();
	CameraPos.Z = CAMERA_DEPTH;
	MainCameraPointer->Transform.SetLocalPosition(CameraPos);
}


void CameraControler::UpdatePlayMode(float _Delta)
{
	if (nullptr == MainCameraPointer)
	{
		MsgBoxAssert("레벨 카메라를 지정해주지 않았습니다.");
		return;
	}

	if (nullptr == FocusActorPointer)
	{
		CameraMode = ECAMERAMODE::Fix;
		return;
	}

	static constexpr float m_SmoothingRatio = 0.035f;

	const float4& ActorPos = FocusActorPointer->Transform.GetWorldPosition();
	const float4& CurCameraPos = MainCameraPointer->Transform.GetWorldPosition();
	
	const float4& SmoothingPos = CurCameraPos + (ActorPos - CurCameraPos) * m_SmoothingRatio;
	float4 CameraMovePos = SmoothingPos - CurCameraPos;

	LockCamera(CameraMovePos, CurCameraPos);

	CameraMovePos = CurCameraPos + CameraMovePos;
	CameraMovePos.Z = CAMERA_DEPTH;
	MainCameraPointer->Transform.SetLocalPosition(CameraMovePos);
}


void CameraControler::LockCamera(float4& _pCameraMovePos, const float4& _CurCameraPos) const
{
	const float4& HalfWinScale = GlobalValue::GetWindowScale().Half();
	float4 BackPosition = BackScale;
	BackPosition.Y *= -1.0f;

	const float4& CameraLeftTopLimitPoint = float4{ HalfWinScale.X , -HalfWinScale.Y };
	const float4& CameraRightBottomLimitPoint = float4{ BackPosition.X - HalfWinScale.X , BackPosition.Y + HalfWinScale.Y } /*+ float4{ 200.0f , -200.f }*/;

	if (_CurCameraPos.X + _pCameraMovePos.X < CameraLeftTopLimitPoint.X)
	{
		_pCameraMovePos.X = 0.0f;
	}

	if (_CurCameraPos.Y + _pCameraMovePos.Y > CameraLeftTopLimitPoint.Y)
	{
		_pCameraMovePos.Y = 0.0f;
	}

	if (_CurCameraPos.X + _pCameraMovePos.X > CameraRightBottomLimitPoint.X)
	{
		_pCameraMovePos.X = 0.0f;
	}

	if (_CurCameraPos.Y + _pCameraMovePos.Y < CameraRightBottomLimitPoint.Y)
	{
		_pCameraMovePos.Y = 0.0f;
	}
}


void CameraControler::UpdateFixMode()
{

}

void CameraControler::UpdateCinematicMode(float _Delta)
{

}

void CameraControler::UpdateEditorMode(float _Delta)
{
	static constexpr float EditorMoveSpeed = 200.0f;

	float CameraSpeed = EditorMoveSpeed * _Delta;
	if (true == GameEngineInput::IsPress(VK_SHIFT, this))
	{
		CameraSpeed = EditorMoveSpeed * 3.0f * _Delta;
	}

	float4 CameraMoveDistance = float4::ZERO;
	
	if (true == GameEngineInput::IsPress('A', this))
	{
		CameraMoveDistance += float4::LEFT * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		CameraMoveDistance += float4::UP * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		CameraMoveDistance += float4::DOWN * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		CameraMoveDistance += float4::RIGHT * CameraSpeed;
	}

	MainCameraPointer->Transform.AddLocalPosition(CameraMoveDistance);
}


#pragma endregion

void CameraControler::RenewCameraPosition()
{
	CameraPosInfo.CurPosition = MainCameraPointer->Transform.GetWorldPosition();
	CameraPosInfo.MoveDistance = CameraPosInfo.CurPosition - CameraPosInfo.PrevPosition;
	CameraPosInfo.PrevPosition = CameraPosInfo.CurPosition;
}