#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalUtils.h"

#include "TestMap.h"
#include "TestActor.h"
#include "CameraControler.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	ContentsLevel::Start();
	{
		GlobalUtils::LoadAllFileInPath("Resources\\Texture");

		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
		GameEngineSprite::CreateCut("Ellie_Basic_ButterflyNet-sharedassets3.png", 12, 11);
		GameEngineSprite::CreateCut("Ellie_Basic_Colleciton_RootUp-sharedassets3.png", 10, 9);
		GameEngineSprite::CreateSingle("TestMap.png");
		GameEngineSprite::CreateSingle("Slyas.png");
		GameEngineSprite::CreateSingle("Base-sharedassets3.assets-29.png");
		GameEngineSprite::CreateSingle("Atlas.png");
		GameEngineSprite::CreateSingle("Sylas2_Intro2_.png");
		GameEngineSprite::CreateSingle("TestPlayerSprite.png");
		GameEngineSprite::CreateSingle("Mission8_JarvanIVArena_Mask_FireLinesSmall.png");
		GameEngineSprite::CreateSingle("sactx-0-2048x2048-BC7-Mission8Jarvan-65ffe534.png");
		
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	


	{
		TestPlayer = CreateActor<Player>();
	}

	{
		std::shared_ptr<TestMap> Object = CreateActor<TestMap>();
	}
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('T'))
	{
		GameEngineCore::ChangeLevel("MainMenu");
	}


	float4 PlayerPos = TestPlayer->Transform.GetWorldPosition();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	float4 CameraPos = PlayerPos + float4{ -HalfWindowScale.X , -HalfWindowScale.Y };

	GetMainCamera()->Transform.SetLocalPosition(PlayerPos);
}

void PlayLevel::LevelStart(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	GlobalValue::g_CameraControler->SetCameraMode(ECAMERAMODE::Play);
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelEnd(_NextLevel);
}