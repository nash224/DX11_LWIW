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
	Renderer->SetSprite("sactx-0-2048x2048-BC7-Mission8Jarvan-65ffe534.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("sactx-0-2048x2048-BC7-Mission8Jarvan-65ffe534.png");


	/*float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });*/

	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);
}