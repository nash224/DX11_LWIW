#include "PreCompile.h"
#include "TestActor2.h"

TestActor2::TestActor2() 
{
}

TestActor2::~TestActor2() 
{
}


void TestActor2::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(-99);
	Renderer->SetSprite("Atlas.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Atlas.png");


	/*float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });*/

	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);

}

void TestActor2::Update(float _Delta)
{

}

void TestActor2::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void TestActor2::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////