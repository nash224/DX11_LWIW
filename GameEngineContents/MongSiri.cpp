#include "PreCompile.h"
#include "MongSiri.h"

#include "MongSiri_Population.h"

#include "Ellie.h"

MongSiri::MongSiri() 
{
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
	DynamicEntity::LevelStart(_NextLevel);
}

void MongSiri::LevelEnd(class GameEngineLevel* _NextLevel)
{
	DynamicEntity::LevelEnd(_NextLevel);
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
	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Shadow);
	if (nullptr == m_Shadow)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Body->CreateAnimation("Idle", "Mongsiri_IdleB.png", 0.2f, 4, 6);
	m_Body->SetStartEvent("Idle", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 1);
		});
	m_Body->SetFrameEvent("Idle", 5, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 1);
		});
	m_Body->SetFrameEvent("Idle", 6, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});
	m_Body->SetFrameEvent("Idle", 7, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 3);
		});

	m_Body->CreateAnimation("Idle_Back", "Mongsiri_IdleB.png", 0.2f, 7, 9);
	m_Body->SetFrameEvent("Idle_Back", 7, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 1);
		});
	m_Body->SetFrameEvent("Idle_Back", 8, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 2);
		});
	m_Body->SetFrameEvent("Idle_Back", 9, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_IdleB.png", 3);
		});


	m_Body->CreateAnimation("Jump", "Mongsiri_Jump.png", 0.1f, 5, 14);
	m_Body->SetFrameEvent("Jump", 5, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	m_Body->SetFrameEvent("Jump", 6, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	m_Body->SetFrameEvent("Jump", 7, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	m_Body->SetFrameEvent("Jump", 8, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	m_Body->SetFrameEvent("Jump", 13, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Jump_Back", "Mongsiri_Jump.png", 0.1f, 15, 24);
	m_Body->SetFrameEvent("Jump_Back", 15, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});
	m_Body->SetFrameEvent("Jump_Back", 16, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 2);
		});
	m_Body->SetFrameEvent("Jump_Back", 17, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 3);
		});
	m_Body->SetFrameEvent("Jump_Back", 18, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 4);
		});
	m_Body->SetFrameEvent("Jump_Back", 23, [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Look", "Mongsiri_Idle.png", 0.05f, 4, 5);
	m_Body->SetStartEvent("Look", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Jump.png", 1);
		});

	m_Body->CreateAnimation("Look_Back", "Mongsiri_Idle.png", 0.2f, 6, 7);
	m_Body->SetStartEvent("Look_Back", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Idle.png", 1);
		});

	m_Body->CreateAnimation("Collected", "Mongsiri_Collected.png", 0.2f, 3, 9);
	m_Body->SetStartEvent("Collected", [=](GameEngineSpriteRenderer*)
		{
			m_Shadow->SetSprite("Mongsiri_Collected.png", 1);
		});
	m_Body->SetEndEvent("Collected", [=](GameEngineSpriteRenderer*)
		{
			m_Body->ChangeAnimation("CollectedA");
		});

	m_Body->CreateAnimation("CollectedA", "Mongsiri_CollectedA.png", 0.05f);


	m_Body->CreateAnimation("Disappear", "Mongsiri_Disappear.png", 0.2f, 10, 33, false);

	m_Body->ChangeAnimation("Collected");
	m_Body->AutoSpriteSizeOn();
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
	if (nullptr == m_Body)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Body->ChangeAnimation(_StateName);
}

void MongSiri::ChangeAnimationByDircetion(std::string_view _StateName)
{
	if (nullptr == m_Body)
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
		m_Body->LeftFlip();
		break;
	case EDIRECTION::RIGHT:
		m_Body->LeftFlip();
		break;
	case EDIRECTION::RIGHTDOWN:
		m_Body->LeftFlip();
		break;
	case EDIRECTION::DOWN:
		break;
	case EDIRECTION::LEFTDOWN:
		m_Body->RightFlip();
		break;
	case EDIRECTION::LEFT:
		m_Body->RightFlip();
		break;
	case EDIRECTION::LEFTUP:
		AnimationName += "_Back";
		m_Body->RightFlip();
		break;
	default:
		break;
	}
	
	m_Body->ChangeAnimation(AnimationName);
}




bool MongSiri::IsPlayerAround()
{
	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("엘리가 존재하지 않습니다.");
		return false;
	}

 	float4 PlayerPosition = Ellie::MainEllie->Transform.GetLocalPosition();
	float PositionSize = (Transform.GetLocalPosition() - PlayerPosition).Size();
	if (PositionSize < MongSiri_FOVSize)
	{
		return true;
	}

	return false;
}