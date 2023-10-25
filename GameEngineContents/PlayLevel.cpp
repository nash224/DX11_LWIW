#include "PreCompile.h"
#include "PlayLevel.h"

#include "GlobalUtils.h"


#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "UIManager.h"
#include "FadeObject.h"


bool PlayLevel::PixelDebugMode = false;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	ContentsLevel::Start();

	GetMainCamera()->SetZSort(0);
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	ChangeDebugMode();
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	if (false == LevelInitCheck)
	{
		CreateEllie();			// 플레이어 생성
		CreateUIManager();		// UI 생성
	}

	std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade->CallFadeIn(0.2f);

	LevelInitCheck = true;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// UI 매니저 생성
void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	m_UIManager->Init();
}

// 플레이어 생성
void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	m_Ellie->Init();
}

// 디버그 모드 전환
void PlayLevel::ChangeDebugMode()
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