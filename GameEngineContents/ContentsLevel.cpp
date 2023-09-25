#include "PreCompile.h"
#include "ContentsLevel.h"


#include "GlobalValue.h"
#include "CameraControler.h"

ContentsLevel::ContentsLevel() 
	:	
	Mode(EGAMEMODE::None)
{
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	// ī�޶� ��Ʈ�ѷ� ����
	m_LevelCameraControler = CreateActor<CameraControler>(EUPDATEORDER::CameraControler);
	if (nullptr == m_LevelCameraControler)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}
}

void ContentsLevel::Update(float _Delta)
{

}

void ContentsLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->m_MainCamera = GetMainCamera().get();
		GlobalValue::g_CameraControler = m_LevelCameraControler;
	}
}

void ContentsLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{

}




