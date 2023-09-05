#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalUtils.h"
#include "TestMap.h"
#include "TestActor.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	{
		GlobalUtils::LoadAllFileInPath("Resources\\Texture");

		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
		GameEngineSprite::CreateSingle("TestMap.png");
		GameEngineSprite::CreateSingle("Slyas.png");
		GameEngineSprite::CreateSingle("Atlas.png");
		GameEngineSprite::CreateSingle("Sylas2_Intro2_.png");
		GameEngineSprite::CreateSingle("TestPlayerSprite.png");
		GameEngineSprite::CreateSingle("Mission8_JarvanIVArena_Mask_FireLinesSmall.png");
		GameEngineSprite::CreateSingle("sactx-0-2048x2048-BC7-Mission8Jarvan-65ffe534.png");

		GameEngineDirectory Dir;
		
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources");
		Dir.MoveChild("SlyasTest");
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
		
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	{
		TestPlayer = CreateActor<Player>();
	}

	{
		std::shared_ptr<TestMap> Object = CreateActor<TestMap>();
	}

	{
		std::shared_ptr<TestActor> Object = CreateActor<TestActor>();
	}
}

void PlayLevel::Update(float _Delta)
{
	float4 PlayerPos = TestPlayer->Transform.GetWorldPosition();

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	float4 CameraPos = PlayerPos + float4{ -HalfWindowScale.X , -HalfWindowScale.Y };

	GetMainCamera()->Transform.SetLocalPosition(PlayerPos);
}