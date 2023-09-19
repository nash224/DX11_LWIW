#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>


#include "TestMap.h"

Player::Player()
{

}

Player::~Player()
{
}

void Player::Start()
{
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("Run", "Ellie_Basic_ButterflyNet-sharedassets3.png", 0.1f);
		MainSpriteRenderer->ChangeAnimation("Run");
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);
		MainSpriteRenderer->SetAutoScaleRatio(2.0f);
		

		int a = 0;
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	
	Transform.GetLocalScale();
}

void Player::Update(float _Delta)
{
	float Speed = 500.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}



	/*GameEngineColor Color = TestMap::MainTestMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GrivityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	else
	{
		GrivityForce = 0.0f;
	}*/
	// 땅에 딱붙게하고 싶다면 while돌려서 올려주세요.


	// float4 Color = GetColor(Transform.GetWorldPosition());
}