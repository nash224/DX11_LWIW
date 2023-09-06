#include "PreCompile.h"
#include "CameraControler.h"


CameraControler::CameraControler()
	:m_MainCamera(nullptr)
	, m_FocusActor(nullptr)
	, m_Mode(ECAMERAMODE::None)
	, m_CameraInfo({ float4::ZERO })
	, m_Speed(500.0f)
{
}

CameraControler::~CameraControler() 
{
}


void CameraControler::Start()
{
	m_Mode = ECAMERAMODE::None;
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

void CameraControler::SetCameraMode(ECAMERAMODE _Mode)
{
	m_Mode = _Mode;
}

void CameraControler::SetWorldPostion(const float4& _Position)
{
	m_MainCamera->Transform.SetLocalPosition(_Position);
	RenewCameraPosition();
	m_CameraInfo.MoveDistance = 0.0f;
}


void CameraControler::Reset()
{
	m_CameraInfo = { float4::ZERO };
}

const float4& CameraControler::GetCameraMoveDistance() const
{
	return m_CameraInfo.MoveDistance;
}

const float4& CameraControler::GetCameraCurrentPostion() const
{
	return m_CameraInfo.CurPosition;
}

bool CameraControler::IsCameraMove()
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
	case ECAMERAMODE::Movie:
		break;
	case ECAMERAMODE::Cinematic:
		break;
	case ECAMERAMODE::Play:
		break;
	case ECAMERAMODE::Setting:
		break;
	case ECAMERAMODE::Editor:
		UpdateCameraEditorMode(_Delta);
		break;
	default:
		break;
	}
}


void CameraControler::UpdateCameraEditorMode(float _Delta)
{
	float CameraSpeed = m_Speed * _Delta;
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