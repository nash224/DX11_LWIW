#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"

#include "Ellie.h"
#include "UI_Inventory.h"


MongSiri::MongSiri()
{
	if (nullptr == GameEngineSound::FindSound("SFX_MongsiriJump_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Mongsiri");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

MongSiri::~MongSiri()
{
}


void MongSiri::Start()
{
	DynamicEntity::Start();

	m_InteractionButtonType = EINTERACTION_BUTTONTYPE::Gathering;			// 버튼타입
	m_InteractionType = EINTERACTION_TYPE::Near;							// 원격
	m_CollectionMethod = ECOLLECTION_METHOD::MongSiri;						// 채집방법
	m_CollectionTool = ETOOLTYPE::Gloves;									// 채집툴
	m_Status = EMONGSIRISTATUS::Normal;
}

void MongSiri::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);

	UpdateState(_Delta);
}

void MongSiri::Release()
{
	DynamicEntity::Release();

	m_Shadow = nullptr;
}

void MongSiri::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void MongSiri::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void MongSiri::Init()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 200, 200 }, float4::ZERO, ColType::SPHERE2D);
	SetNearInteractivePositionAndRange(float4::ZERO, 1.0f);
	CreateAndSetRenderer();
	InitDirection();
	ChangeState(EMONGSIRISTATE::Idle);
}

void MongSiri::CreateAndSetRenderer()
{
	if (nullptr == GameEngineSprite::Find("Mongsiri_Collected.png"))
	{
		// MongSiri
		GameEngineSprite::CreateCut("Mongsiri_Collected.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_CollectedA.png", 4, 1);
		GameEngineSprite::CreateCut("Mongsiri_Disappear.png", 6, 6);
		GameEngineSprite::CreateCut("Mongsiri_Escape.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_Idle.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleA.png", 3, 3);
		GameEngineSprite::CreateCut("Mongsiri_IdleB.png", 4, 3);
		GameEngineSprite::CreateCut("Mongsiri_Jump.png", 5, 5);
	}

	static constexpr const int RenderOrder = 0;

	BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);

	m_Shadow->Transform.SetLocalPosition(float4(0.0f, 0.0f, GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)));

	BodyRenderer->AutoSpriteSizeOn();
	BodyRenderer->CreateAnimation("Idle", "Mongsiri_IdleB.png", 0.2f, 4, 7);
	BodyRenderer->CreateAnimation("Idle_Back", "Mongsiri_IdleB.png", 0.2f, 8, 11);
	BodyRenderer->CreateAnimation("Jump", "Mongsiri_Jump.png", 0.1f, 5, 14);
	BodyRenderer->CreateAnimation("Jump_Back", "Mongsiri_Jump.png", 0.1f, 15, 24);
	BodyRenderer->CreateAnimation("Look", "Mongsiri_Idle.png", 0.05f, 4, 5);
	BodyRenderer->CreateAnimation("Look_Back", "Mongsiri_Idle.png", 0.2f, 6, 7);
	BodyRenderer->CreateAnimation("Collected", "Mongsiri_Collected.png", 0.2f, 3, 8, false);
	BodyRenderer->FindAnimation("Collected")->Inter = { 0.1f, 0.1f, 0.1f, 0.2f, 0.3f, 0.4f };
	BodyRenderer->CreateAnimation("CollectedA", "Mongsiri_CollectedA.png", 0.06f, -1, -1, false);
	BodyRenderer->CreateAnimation("CollectedB", "Mongsiri_Collected.png", 0.12f, 6, 4, false);
	BodyRenderer->CreateAnimation("Disappear", "Mongsiri_Disappear.png", 0.1f, 10, 33, false);

	std::weak_ptr<GameEngineFrameAnimation> Animation = BodyRenderer->FindAnimation("Disappear");
	if (true == Animation.expired())
	{
		MsgBoxAssert("애니메이션을 찾지 못했습니다.");
		return;
	}

	Animation.lock()->Inter =
	{ 0.2f, 0.2f,
		0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f, 0.1f
	};


	BodyRenderer->SetStartEvent("Idle", [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 1);
		});
	BodyRenderer->SetFrameEvent("Idle", 5, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});
	BodyRenderer->SetFrameEvent("Idle", 6, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 3);
		});
	BodyRenderer->SetFrameEvent("Idle", 7, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});


	BodyRenderer->SetStartEvent("Idle_Back", [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 1);
		});
	BodyRenderer->SetFrameEvent("Idle_Back", 9, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});
	BodyRenderer->SetFrameEvent("Idle_Back", 8, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 3);
		});
	BodyRenderer->SetFrameEvent("Idle_Back", 9, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});


	BodyRenderer->SetFrameEvent("Jump", 5, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	BodyRenderer->SetFrameEvent("Jump", 6, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	BodyRenderer->SetFrameEvent("Jump", 7, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	BodyRenderer->SetFrameEvent("Jump", 8, [&](GameEngineSpriteRenderer*)
		{
			PlaySFX("SFX_MongsiriJump_01.wav");
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	BodyRenderer->SetFrameEvent("Jump", 13, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});


	BodyRenderer->SetFrameEvent("Jump_Back", 15, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	BodyRenderer->SetFrameEvent("Jump_Back", 16, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	BodyRenderer->SetFrameEvent("Jump_Back", 17, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	BodyRenderer->SetFrameEvent("Jump_Back", 18, [&](GameEngineSpriteRenderer*)
		{
			PlaySFX("SFX_MongsiriJump_01.wav");
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	BodyRenderer->SetFrameEvent("Jump_Back", 23, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});


	BodyRenderer->SetStartEvent("Look", [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});


	BodyRenderer->SetStartEvent("Look_Back", [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("Mongsiri_Idle.png", 1);
		});

	BodyRenderer->SetStartEvent("Collected", [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("Mongsiri_Collected.png", 1);
		});
	BodyRenderer->SetFrameEvent("Collected", 4, [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});

	BodyRenderer->SetFrameEvent("Collected", 7, [&](GameEngineSpriteRenderer* _Renderer)
		{
			PlaySFX("SFX_MongsiriRootUp.wav");
		});

	BodyRenderer->SetEndEvent("Collected", [&](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->ChangeAnimation("CollectedA");
		});

	BodyRenderer->SetEndEvent("CollectedA", [&](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr != UI_Inventory::MainInventory)
			{
				UI_Inventory::MainInventory->PushItem("Mongsiri_Collect");
			}

			_Renderer->ChangeAnimation("CollectedB");
		});

	BodyRenderer->SetStartEvent("Disappear", [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 1);
		});
	BodyRenderer->SetFrameEvent("Disappear", 11, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 2);
		});
	BodyRenderer->SetFrameEvent("Disappear", 12, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 3);
		});
	BodyRenderer->SetFrameEvent("Disappear", 13, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 4);
		});
	BodyRenderer->SetFrameEvent("Disappear", 18, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 6);
		});
	BodyRenderer->SetFrameEvent("Disappear", 21, [&](GameEngineSpriteRenderer*)
		{
			PlaySFX("SFX_MongsiriHoleIn_01.wav");
		});
	BodyRenderer->SetFrameEvent("Disappear", 24, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 7);
		});
	BodyRenderer->SetFrameEvent("Disappear", 25, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 8);
		});
	BodyRenderer->SetFrameEvent("Disappear", 26, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Disappear.png", 9);
		});
	BodyRenderer->SetFrameEvent("Disappear", 28, [&](GameEngineSpriteRenderer*)
		{
			m_Shadow->Off();
		});
}

void MongSiri::InitDirection()
{
	GameEngineRandom RandomClass;
	int DirctionNumber = RandomClass.RandomInt(0, 3);
	switch (DirctionNumber)
	{
	case 0:
		m_Dir = EDIRECTION::UP;
		break;
	case 1:
		m_Dir = EDIRECTION::RIGHT;
		break;
	case 2:
		m_Dir = EDIRECTION::DOWN;
		break;
	case 3:
		m_Dir = EDIRECTION::LEFT;
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////

void MongSiri::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EMONGSIRISTATE::Idle:								UpdateIdle(_Delta);				break;
	case EMONGSIRISTATE::Jump:								UpdateJump(_Delta);				break;
	case EMONGSIRISTATE::Look:								UpdateLook(_Delta);				break;
	case EMONGSIRISTATE::Caught:							UpdateCaught(_Delta);			break;
	case EMONGSIRISTATE::Collected:							UpdateCollected(_Delta);		break;
	case EMONGSIRISTATE::Disappear:							UpdateDisappear(_Delta);		break;
	case EMONGSIRISTATE::None:																break;
		break;
	default:
		break;
	}
}

void MongSiri::ChangeState(EMONGSIRISTATE _State)
{
	if (m_State != _State)
	{
		switch (m_State)
		{
		case EMONGSIRISTATE::Idle:							EndIdle();						break;
		case EMONGSIRISTATE::Jump:							EndJump();						break;
		case EMONGSIRISTATE::Look:															break;
		case EMONGSIRISTATE::Collected:						EndCollected();					break;
		case EMONGSIRISTATE::Disappear:														break;
		case EMONGSIRISTATE::None:															break;
		default:
			break;
		}

		switch (_State)
		{
		case EMONGSIRISTATE::Idle:							StartIdle();					break;
		case EMONGSIRISTATE::Jump:							StartJump();					break;
		case EMONGSIRISTATE::Look:							StartLook();					break;
		case EMONGSIRISTATE::Caught:						StartCaught();					break;
		case EMONGSIRISTATE::Collected:						StartCollected();				break;
		case EMONGSIRISTATE::Disappear:						StartDisappear();				break;
		case EMONGSIRISTATE::None:
		{
			MsgBoxAssert("행동패턴을 지정해주세요.");
		}
		break;
		default:
			break;
		}

		m_State = _State;
	}
}

void MongSiri::ChangeAnimation(std::string_view _StateName)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	BodyRenderer->ChangeAnimation(_StateName);
}

void MongSiri::ChangeAnimationByDircetion(std::string_view _StateName)
{
	if (nullptr == BodyRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	std::string AnimationName = _StateName.data();

	switch (m_Dir)
	{
	case EDIRECTION::CENTER:
		break;
	case EDIRECTION::UP:
		AnimationName += "_Back";
		break;
	case EDIRECTION::RIGHTUP:
		AnimationName += "_Back";
		BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::RIGHT:
		BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::RIGHTDOWN:
		BodyRenderer->LeftFlip();
		break;
	case EDIRECTION::DOWN:
		break;
	case EDIRECTION::LEFTDOWN:
		BodyRenderer->RightFlip();
		break;
	case EDIRECTION::LEFT:
		BodyRenderer->RightFlip();
		break;
	case EDIRECTION::LEFTUP:
		AnimationName += "_Back";
		BodyRenderer->RightFlip();
		break;
	default:
		break;
	}

	BodyRenderer->ChangeAnimation(AnimationName);
}


bool MongSiri::IsPlayerAround()
{
	if (nullptr != Ellie::MainEllie)
	{
		float4 PlayerPosition = Ellie::MainEllie->Transform.GetLocalPosition();
		float PositionSize = (Transform.GetLocalPosition() - PlayerPosition).Size();
		if (PositionSize < MongSiri_FOVSize)
		{
			return true;
		}
	}

	return false;
}