#include "PreCompile.h"
#include "AlchemyPot.h"

#include "UI_Dispensation.h"



AlchemyPot::AlchemyPot() 
{
}

AlchemyPot::~AlchemyPot() 
{
}


void AlchemyPot::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 160.0f , 100.0f }, float4(0.0f, -100.0f), ColType::SPHERE2D);
	SetInteractionType(EINTERACTION_TYPE::Far);
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
	m_CollectionTool = ETOOLTYPE::Nothing;
}

void AlchemyPot::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	UpdateState(_Delta);
}

void AlchemyPot::Release()
{
	m_PotRenderer = nullptr;
	m_WaterRenderer = nullptr;
	m_FxRenderer = nullptr;
	m_FireRenderer = nullptr;
	m_SteamRenderer = nullptr;

	m_InteractiveCol = nullptr;

	// 연금UI
	m_Dispensation = nullptr;
}

void AlchemyPot::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void AlchemyPot::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void AlchemyPot::Init()
{
	RendererSetting();
	DispensationSetting();
}

void AlchemyPot::DispensationSetting()
{
	m_Dispensation = GetLevel()->CreateActor<UI_Dispensation>();
	m_Dispensation->Init();
}

void AlchemyPot::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Pot_Fire_Large.png"))
	{
		// Pot
		GameEngineSprite::CreateCut("Pot_Fire_Large.png", 5, 5);
		GameEngineSprite::CreateCut("Pot_Fire_Small.png", 5, 5);
		GameEngineSprite::CreateCut("Pot_Fx_Boil.png", 4, 4);
		GameEngineSprite::CreateCut("Pot_Fx_Fail.png", 5, 4);
		GameEngineSprite::CreateCut("Pot_Fx_IdleA.png", 5, 5);
		GameEngineSprite::CreateCut("Pot_Fx_IdleB.png", 5, 5);
		GameEngineSprite::CreateCut("Pot_Fx_Steam.png", 5, 5);
		GameEngineSprite::CreateCut("Pot_Fx_Success.png", 5, 5);
	}

	m_PotRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_PotRenderer->SetSprite("DownFloor_Pot_0.png");
	m_PotRenderer->Transform.SetLocalPosition({ 0.0f , -8.0f });


	m_WaterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_WaterRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	m_WaterRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21);
	m_WaterRenderer->AutoSpriteSizeOn();
	m_WaterRenderer->ChangeAnimation("Idle");


	m_FxRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_FxRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));
	m_FxRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21, false);
	m_FxRenderer->CreateAnimation("Boil", "Pot_Fx_Boil.png", 0.1f, 0, 14, false);
	m_FxRenderer->SetStartEvent("Boil", [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_FireRenderer->ChangeAnimation("Large");
			m_SteamRenderer->Off();
		});


	m_FxRenderer->CreateAnimation("Fail", "Pot_Fx_Fail.png", 0.1f, 0, 18, false);
	m_FxRenderer->SetEndEvent("Fail", std::bind(&AlchemyPot::EndPotionCreation, this));
	m_FxRenderer->CreateAnimation("Success", "Pot_Fx_Success.png", 0.1f, 0, 21, false);
	m_FxRenderer->SetEndEvent("Success", std::bind(&AlchemyPot::EndPotionCreation, this));
	m_FxRenderer->AutoSpriteSizeOn();
	m_FxRenderer->Off();


	m_FireRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_FireRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	m_FireRenderer->CreateAnimation("Small", "Pot_Fire_Small.png", 0.1f, 1, 23);
	m_FireRenderer->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_FireRenderer->AutoSpriteSizeOn();
	
	m_FireRenderer->ChangeAnimation("Small");

	m_SteamRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_SteamRenderer->CreateAnimation("Steam", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_SteamRenderer->AutoSpriteSizeOn();
	m_SteamRenderer->ChangeAnimation("Steam");
	m_SteamRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));

	ChangeState(EPOTSTATE::Idle);
}


void AlchemyPot::SetCreatePotion(const bool _Value)
{
	IsPotionCreated = _Value;
}


void AlchemyPot::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EPOTSTATE::None:
	{
		MsgBoxAssert("None으로 세팅했습니다.");
		return;
	}
		break;
	case EPOTSTATE::Idle:
		UpdateIdle(_Delta);
		break;
	case EPOTSTATE::Boil:
		UpdateBoil(_Delta);
		break;
	case EPOTSTATE::Fail:
		UpdateFail(_Delta);
		break;
	case EPOTSTATE::Success:
		UpdateSuccess(_Delta);
		break;
	default:
		break;
	}
}

void AlchemyPot::ChangeState(EPOTSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EPOTSTATE::Idle:
			StartIdle();
			break;
		case EPOTSTATE::Boil:
			StartBoil();
			break;
		case EPOTSTATE::Fail:
			StartFail();
			break;
		case EPOTSTATE::Success:
			StartSuccess();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void AlchemyPot::ChangePotCompositionAnimation(std::string_view _StateName)
{
	std::string AnimationName = "";
	AnimationName += _StateName.data();
	
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_FxRenderer->ChangeAnimation(AnimationName);
}



void AlchemyPot::StartIdle()
{
	ChangePotCompositionAnimation("Idle");
}

void AlchemyPot::UpdateIdle(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr == m_Dispensation)
		{
			MsgBoxAssert("연금UI가 존재하지 않습니다.");
			return;
		}

		m_Dispensation->Open();


		/*ChangeState(EPOTSTATE::Boil);
		return; */
	}
}


void AlchemyPot::StartBoil()
{
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_FxRenderer->On();

	IsPotionCreated = true;

	ChangePotCompositionAnimation("Boil");
}

void AlchemyPot::UpdateBoil(float _Delta)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		if (true == IsPotionCreated)
		{
			ChangeState(EPOTSTATE::Success);
			return;
		}
		else
		{
			ChangeState(EPOTSTATE::Fail);
			return;
		}
	}
}


void AlchemyPot::StartFail()
{
	ChangePotCompositionAnimation("Fail");
}

void AlchemyPot::UpdateFail(float _Delta)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		ChangeState(EPOTSTATE::Idle);
		return;
	}
}


void AlchemyPot::StartSuccess()
{
	ChangePotCompositionAnimation("Success");
}

void AlchemyPot::UpdateSuccess(float _Delta)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		ChangeState(EPOTSTATE::Idle);
		return;
	}
}




void AlchemyPot::EndPotionCreation()
{
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	m_FireRenderer->ChangeAnimation("Small");


	if (nullptr == m_SteamRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	m_SteamRenderer->On();

	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_FxRenderer->Off();

	IsPotionCreated = false;
}