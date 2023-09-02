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
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	{
		std::shared_ptr<Player> Object = CreateActor<Player>();
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
	int a = 0;
}