#include "PreCompile.h"
#include "WitchFlower.h"

#include "BackDrop_PlayLevel.h"
#include "UI_Inventory.h"

WitchFlower::WitchFlower() 
{
}

WitchFlower::~WitchFlower() 
{
}


void WitchFlower::Start()
{
	Plant::Start();

	CreateAndSetCollision(ECOLLISION::Entity, { 100.0f, }, 0.0f, ColType::SPHERE2D);

}

void WitchFlower::Update(float _Delta)
{
	Plant::Update(_Delta);
}

void WitchFlower::Release()
{
	Plant::Release();

	ShadowRenderer = nullptr;
}


void WitchFlower::Init()
{
	ApplyDepth();
	RendererSetting();
	Plant::State.ChangeState(EPLANTSTATE::Idle);
}

void WitchFlower::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("WitchFlower.png"))
	{
		GameEngineSprite::CreateCut("WitchFlower.png", 4, 4);
	}

	static constexpr const int RenderOrder = 0;

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	BodyRenderer->Transform.AddLocalPosition({ 0.0f, RenderYCorrection , 0.0f });
	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->CreateAnimation("Idle", "WitchFlower.png", 5.0f, 5, 5, false);
	BodyRenderer->CreateAnimation("UpRoot", "WitchFlower.png", 0.12f, 6, 13, false);
	BodyRenderer->FindAnimation("UpRoot")->Inter[7] = 0.24f;


	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	ShadowRenderer->SetSprite("WitchFlower.png", 1);
	ShadowRenderer->Transform.AddLocalPosition({ 0.0f, RenderYCorrection, DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)});



	// 프레임 이벤트 설정
	BodyRenderer->SetFrameEvent("UpRoot", 6, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == ShadowRenderer)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			ShadowRenderer->SetSprite("WitchFlower.png", 3);
		});

	BodyRenderer->SetFrameEvent("UpRoot", 7, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == ShadowRenderer)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			ShadowRenderer->SetSprite("WitchFlower.png", 2);
		});

	BodyRenderer->SetFrameEvent("UpRoot", 8, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == ShadowRenderer)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			ShadowRenderer->SetSprite("WitchFlower.png", 2);
		});

	BodyRenderer->SetFrameEvent("UpRoot", 9, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == ShadowRenderer)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			ShadowRenderer->SetSprite("WitchFlower.png", 4);
		});

	BodyRenderer->SetFrameEvent("UpRoot", 10, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == ShadowRenderer)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}
			
			ShadowRenderer->Off();
		});
}

// 여기 재정의
void WitchFlower::RootInternal()
{
	UI_Inventory::PushItem("WitchFlower_Collect");
	Death();
}