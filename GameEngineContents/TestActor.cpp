#include "PreCompile.h"
#include "TestActor.h"

TestActor::TestActor() 
{
}

TestActor::~TestActor() 
{
}


void TestActor::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(-99);
	Renderer->SetSprite("Base-sharedassets3.assets-29.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Base-sharedassets3.assets-29.png");


	/*float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });*/

	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);
}