#include "PreCompile.h"
#include "ContentsLevel.h"


#include "GlobalValue.h"
#include "CameraControler.h"

ContentsLevel::ContentsLevel() 
	: m_LevelCameraControler(nullptr)
	, CurrentLevelSpriteCreateCheck(false)
	, LevelType(ELEVELTYPE::None)
	, Mode(EGAMEMODE::None)
{
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	// 카메라 컨트롤러 생성
	m_LevelCameraControler = CreateActor<CameraControler>(EUPDATEORDER::CameraControler);
}

void ContentsLevel::Update(float _Delta)
{

}

void ContentsLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	CurrentLevelSpriteCreateCheck = true;

	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->m_MainCamera = GetMainCamera().get();
		GlobalValue::g_CameraControler = m_LevelCameraControler;
	}
}

void ContentsLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	CurrentLevelSpriteCreateCheck = false;
}




