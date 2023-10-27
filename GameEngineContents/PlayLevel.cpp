#include "PreCompile.h"
#include "PlayLevel.h"


// Actor
#include "Ellie.h"
#include "FadeObject.h"

// Manager
#include "CameraControler.h"
#include "UIManager.h"
#include "TimeManager.h"



std::shared_ptr<TimeManager> PlayLevel::m_TimeManager;
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	ContentsLevel::Start();

	if (nullptr == m_TimeManager)
	{
		m_TimeManager = std::make_shared<TimeManager>();
		m_TimeManager->Init();
	}
}

void PlayLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	if (nullptr != m_TimeManager)
	{
		m_TimeManager->Update(_Delta);
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	if (false == LevelInitCheck)
	{
		CreateEllie();			// 敲饭捞绢 积己
		CreateUIManager();		// UI 积己
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



// UI 概聪历 积己
void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	m_UIManager->Init();
}

// 敲饭捞绢 积己
void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	m_Ellie->Init();
}
