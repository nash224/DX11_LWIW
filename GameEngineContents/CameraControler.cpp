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


void CameraControler::Reset()
{
	m_CameraInfo = { float4::ZERO };
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



	float4 CameraPos = float4::ZERO;
	CameraPos.X = ActorPos.X + m_WinScale.X;
	CameraPos.Y = ActorPos.Y - m_WinScale.Y;


	m_MainCamera->Transform.SetLocalPosition(CameraPos);
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