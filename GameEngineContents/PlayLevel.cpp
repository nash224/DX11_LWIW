#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalUtils.h"

#include "CameraControler.h"
#include "BackDrop.h"



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

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		PixelDebugMode = !PixelDebugMode;
		if (nullptr == BackDrop::MainBackDrop)
		{
			MsgBoxAssert("글로벌 액터가 존재하지 않습니다.");
			return;
		}
		
		BackDrop::MainBackDrop->EnableBackDropDebugMode(PixelDebugMode);
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}







void PlayLevel::InitPlayLevel()
{

}


