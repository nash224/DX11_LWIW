#include "PreCompile.h"
#include "CameraControler.h"


CameraControler::CameraControler()
	:m_MainCamera(nullptr)
	, m_FocusActor(nullptr)
	, m_Mode(ECAMERAMODE::None)
	, m_CameraInfo({ float4::ZERO })
{
}

CameraControler::~CameraControler() 
{
}


void CameraControler::Start()
{
	m_Mode = ECAMERAMODE::None;

	m_WinScale = GlobalValue::GetWindowScale();
}

void CameraControler::Update(float _Delta)
{
	UpdateCameraMode(_Delta);
	RenewCameraPosition();
}

void CameraControler::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}

void CameraControler::LevelEnd(class GameEngineLevel* _NextLevel)
{

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void CameraControler::SetCameraMode(ECAMERAMODE _Mode)
{
	m_Mode = _Mode;
}

void CameraControler::SetLocalPostion(const float4& _Position)
{
	m_MainCamera->Transform.SetLocalPosition(_Position);
	RenewCameraPosition();
	m_CameraInfo.MoveDistance = 0.0f;
}

void CameraControler::SetFocusActor(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgBoxAssert("존재하지 않는 액터를 적용하려고 했습니다.");
		return;
	}

	m_FocusActor = _Actor;
}

void CameraControler::SetBackDropScale(const float4& _Scale)
{
	m_BackScale = _Scale;
}


void CameraControler::Reset()
{
	m_CameraInfo.PrevPosition = m_MainCamera->Transform.GetWorldPosition();
	m_CameraInfo.MoveDistance = float4::ZERO;
}

void CameraControler::SetAutoInitialPosition(const float4& _Location)
{
	if (float4::ZERO == m_BackScale)
	{
		MsgBoxAssert("배경 넓이을 지정해주지 않고 카메라 매니저를 사용하려 했습니다.");
		return;
	}

	if (nullptr == m_MainCamera)
	{
		MsgBoxAssert("카메라 액터가 존재하지 않는데 사용하려고 했습니다.");
		return;
	}

 	float4 CurCameraPos = _Location;


	float4 HWinScale = m_WinScale.Half();

	float4 CameraLeftTopPoint = CurCameraPos + float4{ -HWinScale.X , HWinScale.Y };
	float4 CameraRightBottomPoint = CurCameraPos + float4{ HWinScale.X , -HWinScale.Y };

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

	if (CameraRightBottomPoint.X > m_BackScale.X)
	{
		IsRightTopCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}

	if (CameraRightBottomPoint.Y < -m_BackScale.Y)
	{
		IsLeftBottomCornerInBackScale = false;
		IsRightBottomCornerInBackScale = false;
	}


	if (CameraLeftTopPoint.X > m_BackScale.X)
	{
		IsLeftTopCornerInBackScale = false;
		IsLeftBottomCornerInBackScale = false;
	}

	if (CameraLeftTopPoint.Y < -m_BackScale.Y)
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
		return;
	}

	if (1 == CornerCountWithinScreen)
	{
		// 왼쪽 위 모서리가 배경 스케일 안에 있으면
		if (true == IsLeftTopCornerInBackScale)
		{
			CurCameraPos = float4{ m_BackScale.X - HWinScale.X  , -m_BackScale.Y + HWinScale.Y };
		}

		// 왼쪽 아래 모서리가 배경 스케일 안에 있으면
		if (true == IsLeftBottomCornerInBackScale)
		{
			CurCameraPos = float4{ m_BackScale.X - HWinScale.X , -HWinScale.Y };
		}

		// 오른쪽 위 모서리가 배경 스케일 안에 있으면
		if (true == IsRightTopCornerInBackScale)
		{
			CurCameraPos = float4{ HWinScale.X , -m_BackScale.Y + HWinScale.Y };
		}

		// 오른쪽 아래 모서리가 배경 스케일 안에 있으면
		if (true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos = float4{ HWinScale.X , -HWinScale.Y };
		}
	}

	// 모서리가 배경 밖으로 2개 나갔을 때
	if (2 == CornerCountWithinScreen)
	{
		// 왼쪽 면이 배경 스케일 안에 있으면
		if (true == IsLeftTopCornerInBackScale && true == IsLeftBottomCornerInBackScale)
		{
			CurCameraPos.X = m_BackScale.X - HWinScale.X;
		}

		// 위쪽 면이 배경 스케일 안에 있으면
		if (true == IsLeftTopCornerInBackScale && true == IsRightTopCornerInBackScale)
		{
			CurCameraPos.Y = -m_BackScale.Y + HWinScale.Y;
		}

		// 오른쪽 면이 배경 스케일 안에 있으면
		if (true == IsRightTopCornerInBackScale && true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos.X = HWinScale.X;
		}

		// 아래쪽 면이 배경 스케일 안에 있으면
		if (true == IsLeftBottomCornerInBackScale && true == IsRightBottomCornerInBackScale)
		{
			CurCameraPos.Y = -HWinScale.Y;
		}
	}

	// 있을 수 없는 일입니다. 만약 들어오면 터집니다.
	if (3 == CornerCountWithinScreen)
	{
		MsgBoxAssert("있을 수 없는 버그입니다. 값을 확인해보세요.");
		return;
	}

	if (4 == CornerCountWithinScreen)
	{
		return;
	}

	m_MainCamera->Transform.SetLocalPosition(CurCameraPos);
}



float4 CameraControler::GetCameraMoveDistance() const
{
	return m_CameraInfo.MoveDistance;
}

float4 CameraControler::GetCameraCurrentPostion() const
{
	return m_CameraInfo.CurPosition;
}

bool CameraControler::IsCameraMove() const
{
	return float4::ZERO != m_CameraInfo.MoveDistance;
}


#pragma region 카메라 모드 업데이트

void CameraControler::UpdateCameraMode(float _Delta)
{
	switch (m_Mode)
	{
	case ECAMERAMODE::None:
	{
		MsgBoxAssert("카메라 모드를 지정하지 않고 사용하려고 했습니다.");
	}
		break;
	case ECAMERAMODE::Play:
		UpdateCameraPlayMode(_Delta);
		break;
	case ECAMERAMODE::Fix:
		break;
	case ECAMERAMODE::Editor:
		UpdateCameraEditorMode(_Delta);
		break;
	default:
		break;
	}
}


void CameraControler::UpdateCameraPlayMode(float _Delta)
{
	if (nullptr == m_MainCamera)
	{
		MsgBoxAssert("레벨 카메라를 지정해주지 않았습니다.");
		return;
	}

	if (nullptr == m_FocusActor)
	{
		return;
	}


	float4 ActorPos = m_FocusActor->Transform.GetWorldPosition();
	float4 CurCameraPos = m_MainCamera->Transform.GetWorldPosition();

	float4 SmoothingPos = CurCameraPos + (ActorPos - CurCameraPos) * m_SmoothingRatio;
	float4 CameraMovePos = SmoothingPos - CurCameraPos;

	LockCamera(CameraMovePos, CurCameraPos);

	m_MainCamera->Transform.AddLocalPosition(CameraMovePos);
}


void CameraControler::LockCamera(float4& _pCameraMovePos, const float4& _CurCameraPos)
{
	float4 HalfWinScale = m_WinScale.Half();
	float4 BackScale = m_BackScale;
	BackScale.Y *= -1.0f;

	float4 CameraLeftTopLimitPoint = float4{ HalfWinScale.X , -HalfWinScale.Y } /*+ float4{ -200.0f , 200.f }*/;
	float4 CameraRightBottomLimitPoint = float4{ BackScale.X - HalfWinScale.X , BackScale.Y + HalfWinScale.Y } /*+ float4{ 200.0f , -200.f }*/;

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



void CameraControler::UpdateCameraEditorMode(float _Delta)
{
	float CameraSpeed = m_EditorModeSpeed * _Delta;
	float4 CameraMoveDistance = float4::ZERO;
	
	if (true == GameEngineInput::IsPress('W'))
	{
		CameraMoveDistance = float4::UP * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		CameraMoveDistance = float4::DOWN * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		CameraMoveDistance = float4::LEFT * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		CameraMoveDistance = float4::RIGHT * CameraSpeed;

	}

	m_MainCamera->Transform.AddLocalPosition(CameraMoveDistance);
}


#pragma endregion


void CameraControler::RenewCameraPosition()
{
	m_CameraInfo.CurPosition = m_MainCamera->Transform.GetWorldPosition();
	m_CameraInfo.MoveDistance = m_CameraInfo.CurPosition - m_CameraInfo.PrevPosition;
	m_CameraInfo.PrevPosition = m_CameraInfo.CurPosition;
}