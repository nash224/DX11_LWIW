#include "PreCompile.h"
#include "PlayLevel.h"

// GUI
#include <GameEngineCore/GameEngineCoreWindow.h>


// Manager
#include "CameraControler.h"
#include "UIManager.h"
#include "TimeManager.h"
#include "AlertManager.h"
#include "BGMManager.h"

// Actor
#include "Ellie.h"
#include "FadeObject.h"
#include "UI_Alert_Enter.h"

#include "SkyLightEffect.h"

std::unique_ptr<TimeManager> PlayLevel::s_TimeManager;
std::unique_ptr<AlertManager> PlayLevel::s_AlertManager;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	ContentsLevel::Start();

	if (nullptr == s_TimeManager)
	{
		s_TimeManager = std::make_unique<TimeManager>();
		s_TimeManager->Init();
	}

	if (nullptr == s_AlertManager)
	{
		s_AlertManager = std::make_unique<AlertManager>();
	}

	EffectSetting();
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (nullptr != s_TimeManager)
	{
		s_TimeManager->Update(_Delta);
	}

	if (nullptr != s_AlertManager)
	{
		s_AlertManager->Update(_Delta);
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	if (false == LevelInitCheck)
	{
		CreateEllie();
		CreateUIManager();
	}

	LevelInitCheck = true;

	{
		std::shared_ptr<FadeObject> Fade = CreateActor<FadeObject>(EUPDATEORDER::Fade);
		Fade->CallFadeIn(0.2f);
	}


	if (false == LocationKRName.empty())
	{
		s_AlertManager->RegisterAlert(AlertData(LocationKRName, EALERTTYPE::Enter));
	}
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

void PlayLevel::SetLocationName(std::string_view _KRName)
{
	LocationKRName = _KRName;
}

void PlayLevel::EffectSetting()
{
	{
		GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<SkyLightEffect>();
	}
}