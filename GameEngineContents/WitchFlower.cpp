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
}

void WitchFlower::Update(float _Delta)
{
	Plant::Update(_Delta);
}

void WitchFlower::Release()
{
	Plant::Release();

	m_Shadow = nullptr;
}

void WitchFlower::LevelStart(class GameEngineLevel* _NextLevel)
{
	Plant::LevelStart(_NextLevel);
}

void WitchFlower::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Plant::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void WitchFlower::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	CreateAndSetCollision(ECOLLISION::Entity, { 100.0f, }, 0.0f, ColType::SPHERE2D);
	CreateAndSetWitchFlowerRenderer();
	ChangeState(EPLANTSTATE::Idle);
}

void WitchFlower::CreateAndSetWitchFlowerRenderer()
{
	if (nullptr == GameEngineSprite::Find("WitchFlower.png"))
	{
		GameEngineSprite::CreateCut("WitchFlower.png", 4, 4);
	}

	static constexpr const int RenderOrder = 0;

	m_Plant = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Plant->CreateAnimation("Idle", "WitchFlower.png", 5.0f, 5, 5, false);
	m_Plant->CreateAnimation("UpRoot", "WitchFlower.png", 0.2f, 5, 13, false);
	m_Plant->AutoSpriteSizeOn();
	m_Plant->Transform.AddLocalPosition({ 0.0f, WitchFlowerRenderBias , 0.0f });


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Shadow->SetSprite("WitchFlower.png", 1);
	m_Shadow->Transform.AddLocalPosition({ 0.0f, WitchFlowerRenderBias, 0.0f });



	// 프레임 이벤트 설정
	m_Plant->SetFrameEvent("UpRoot", 6, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == m_Shadow)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			m_Shadow->SetSprite("WitchFlower.png", 3);
		});

	m_Plant->SetFrameEvent("UpRoot", 7, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == m_Shadow)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			m_Shadow->SetSprite("WitchFlower.png", 2);
		});

	m_Plant->SetFrameEvent("UpRoot", 8, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == m_Shadow)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			m_Shadow->SetSprite("WitchFlower.png", 2);
		});

	m_Plant->SetFrameEvent("UpRoot", 9, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == m_Shadow)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}

			m_Shadow->SetSprite("WitchFlower.png", 4);
		});

	m_Plant->SetFrameEvent("UpRoot", 10, [=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == m_Shadow)
			{
				MsgBoxAssert("그림자 렌더러가 존재하지 않습니다.");
				return;
			}
			
			m_Shadow->Off();
		});
}




// 여기 재정의
void WitchFlower::ChildUpRoot()
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		UI_Inventory::MainInventory->PushItem("WitchFlower_Collect");
	}

	Death();
}