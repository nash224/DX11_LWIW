#include "PreCompile.h"
#include "PlayLevel.h"

#include "GlobalUtils.h"


#include "BackDrop_PlayLevel.h"
#include "CameraControler.h"
#include "Ellie.h"
#include "UIManager.h"



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
		CreateEllie();
		CreateUIManager();
	}

	LevelInitCheck = true;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void PlayLevel::CreateUIManager()
{
	m_UIManager = CreateActor<UIManager>(EUPDATEORDER::UIMagnaer);
	if (nullptr == m_UIManager)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_UIManager->Init();
}

void PlayLevel::CreateEllie()
{
	m_Ellie = CreateActor<Ellie>(EUPDATEORDER::Player);
	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Ellie->Init();
}

void PlayLevel::ChangeDebugMode()
{
	if (true == IsDebug)
	{
		if (true == GameEngineInput::IsDown(VK_F2, this))
		{
			PixelDebugMode = !PixelDebugMode;
			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("글로벌 액터가 존재하지 않습니다.");
				return;
			}

			BackDrop_PlayLevel::MainBackDrop->EnableDebugMode(PixelDebugMode);
		}
	}
	else
	{
		if (true == PixelDebugMode)
		{
			PixelDebugMode = false;

			if (nullptr == BackDrop_PlayLevel::MainBackDrop)
			{
				MsgBoxAssert("글로벌 액터가 존재하지 않습니다.");
				return;
			}
			BackDrop_PlayLevel::MainBackDrop->EnableDebugMode(PixelDebugMode);
		}
	}
}