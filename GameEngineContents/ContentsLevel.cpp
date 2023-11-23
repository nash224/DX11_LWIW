#include "PreCompile.h"
#include "ContentsLevel.h"

#include "GlobalValue.h"
#include "CameraControler.h"

#include "OutLineEffect.h"
#include "BGMManager.h"


bool ContentsLevel::PixelDebugMode = false;
std::unique_ptr<BGMManager> ContentsLevel::MainPlaySound;
ContentsLevel::ContentsLevel() 
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	GetMainCamera()->SetZSort(0);
	GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	LevelCamera = CreateActor<CameraControler>(EUPDATEORDER::CameraControler);

	GameEngineLevel::IsDebug = false;
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<OutLineEffect>();

	if (nullptr == MainPlaySound)
	{
		MainPlaySound = std::make_unique<BGMManager>();
		MainPlaySound->Init();
	}
}

void ContentsLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		IsDebug = !IsDebug;
	}

	ChangeDebugMode();

	if (nullptr != MainPlaySound)
	{
		MainPlaySound->Update(_Delta);
	}
}

void ContentsLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	if (nullptr != LevelCamera)
	{
		LevelCamera->m_MainCamera = GetMainCamera().get();
		GlobalValue::g_CameraControler = LevelCamera;
	}
}


// 디버그 모드 전환
void ContentsLevel::ChangeDebugMode()
{
	if (true == IsDebug)
	{
		if (true == GameEngineInput::IsDown(VK_F2, this))
		{
			PixelDebugMode = !PixelDebugMode;
		}
	}
	else
	{
		if (true == PixelDebugMode)
		{
			PixelDebugMode = false;
		}
	}
}