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
	GameEngineInput::AddInputObject(this);

	m_Mode = ECAMERAMODE::None;

	m_WinScale = GlobalValue::GetWindowScale();
}

void CameraControler::Update(float _Delta)
{
	if (nullptr == m_MainCamera)
	{
		MsgBoxAssert("메인카메라를 참조하지 않았습니다.");
		return;
	}

	if (true == m_MainCamera->IsFreeCamera())
	{
		return;
	}

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



// 카메라 모드
void CameraControler::SetCameraMode(ECAMERAMODE _Mode)
{
	m_Mode = _Mode;
}

void CameraControler::SetLocalPostion(const float4& _Position)
{
	float4 Position = _Position;
	Position.Z = CameraDepth;

	m_MainCamera->Transform.SetLocalPosition(Position);
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

float4 CameraControler::GetCameraWorldPosition() const
{
	if (nullptr == m_MainCamera)
	{
		MsgBoxAssert("카메라를 연결하세요");
		return float4::ZERO;
	}

	return m_MainCamera->Transform.GetWorldPosition();
}

void CameraControler::Reset()
{
	m_CameraInfo.PrevPosition = m_MainCamera->Transform.GetWorldPosition();
	m_CameraInfo.MoveDistance = float4::ZERO;
}

// 플레이 모드 전용
// 카메라 첫위치 조정
void CameraControler::SetAutoInitialPosition(const float4& _Location)
{
	if (ECAMERAMODE::Play != m_Mode)
	{
		return;
	}

	if (float4::ZERO == m_BackScale)
	{
		MsgBoxAssert("배경 넓이을 지정해주지 않고 카메라 플레이 모드를 사용하려 했습니다.");
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

	// 배경 안에 4점이 위치해있다는 것으로 아무것도 해주지 않습니다.
	if (4 == CornerCountWithinScreen)
	{

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
		UpdateCameraFixMode();
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
		// 카메라의 포커싱액터가 존재하지 않을때 고정모드
		m_Mode = ECAMERAMODE::Fix;
		return;
	}


	float4 ActorPos = m_FocusActor->Transform.GetWorldPosition();
	float4 CurCameraPos = m_MainCamera->Transform.GetWorldPosition();
	
	float4 SmoothingPos = CurCameraPos + (ActorPos - CurCameraPos) * m_SmoothingRatio;		// 매프레임마다 일정비율로 조정
	float4 CameraMovePos = SmoothingPos - CurCameraPos;

	LockCamera(CameraMovePos, CurCameraPos);

	CameraMovePos = CurCameraPos + CameraMovePos;
	CameraMovePos.Z = CameraDepth;					// 카메라 깊이 고정
	m_MainCamera->Transform.SetLocalPosition(CameraMovePos);
}



// PlayMode 기능
// 카메라 잠금
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


void CameraControler::UpdateCameraFixMode()
{

}

// 카메라 에디터 모드
void CameraControler::UpdateCameraEditorMode(float _Delta)
{
	float CameraSpeed = m_EditorModeSpeed * _Delta;
	float4 CameraMoveDistance = float4::ZERO;
	
	if (true == GameEngineInput::IsPress('W', this))
	{
		CameraMoveDistance = float4::UP * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		CameraMoveDistance = float4::DOWN * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('A', this))
	{
		CameraMoveDistance = float4::LEFT * CameraSpeed;
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		CameraMoveDistance = float4::RIGHT * CameraSpeed;
	}

	m_MainCamera->Transform.AddLocalPosition(CameraMoveDistance);
}


#pragma endregion


// 카메라 위치, 이동값 갱신 : 
// 목적) 원근감 표현
void CameraControler::RenewCameraPosition()
{
	m_CameraInfo.CurPosition = m_MainCamera->Transform.GetWorldPosition();
	m_CameraInfo.MoveDistance = m_CameraInfo.CurPosition - m_CameraInfo.PrevPosition;
	m_CameraInfo.PrevPosition = m_CameraInfo.CurPosition;
}