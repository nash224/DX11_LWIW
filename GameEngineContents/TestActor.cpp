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
	Renderer->SetSprite("TestPlayerSprite.png");

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("TestPlayerSprite.png");

	float4 HScale = Tex->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);
}