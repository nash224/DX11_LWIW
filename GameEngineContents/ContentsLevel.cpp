#include "PreCompile.h"
#include "ContentsLevel.h"

#include "GlobalValue.h"
#include "CameraControler.h"

#include "OutLineEffect.h"
#include "BGMManager.h"


std::unique_ptr<BGMManager> ContentsLevel::MainPlaySound;
ContentsLevel::ContentsLevel() 
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	GetMainCamera()->SetZSort(0);
	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	LevelCamera = CreateActor<CameraControler>(EUPDATEORDER::CameraControler);
	LevelCamera->MainCameraPointer = GetMainCamera().get();

	GameEngineLevel::IsDebug = false;
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == MainPlaySound)
	{
		MainPlaySound = std::make_unique<BGMManager>();
		MainPlaySound->Init();
	}
}

void ContentsLevel::Update(float _Delta)
{
	if (nullptr != MainPlaySound)
	{
		MainPlaySound->Update(_Delta);
	}
}

std::shared_ptr<class CameraControler> ContentsLevel::GetLevelCameraPtr() const
{
	if (nullptr == LevelCamera)
	{
		MsgBoxAssert("카메라 매니저가 존재하지 않습니다.");
		return nullptr;
	}

	return LevelCamera;
}