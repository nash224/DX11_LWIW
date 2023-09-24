#include "PreCompile.h"
#include "AlchemyPot.h"

AlchemyPot::AlchemyPot() 
{
}

AlchemyPot::~AlchemyPot() 
{
}


void AlchemyPot::Start()
{
	StartAlchemyPot();
}

void AlchemyPot::Update(float _Delta)
{
	UpdateState(_Delta);
}

void AlchemyPot::Release()
{
	m_PotRenderer = nullptr;
	m_WaterRenderer = nullptr;
	m_FireRenderer = nullptr;
	m_PotFxSteam = nullptr;
	m_InteractiveCol = nullptr;
}

void AlchemyPot::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void AlchemyPot::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void AlchemyPot::StartAlchemyPot()
{
	CreateRendererAndAnimation();
	CreateInteractiveCollision();
}

void AlchemyPot::CreateRendererAndAnimation()
{
	m_PotRenderer = CreateComponent<GameEngineSpriteRenderer>(15);
	if (nullptr == m_PotRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_PotRenderer->SetSprite("DownFloor_Pot_0.png");
	m_PotRenderer->Transform.SetLocalPosition({ 0.0f , -8.0f });


	m_WaterRenderer = CreateComponent<GameEngineSpriteRenderer>(16);
	if (nullptr == m_WaterRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_WaterRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21);
	m_WaterRenderer->CreateAnimation("Boil", "Pot_Fx_Boil.png", 0.1f, 0, 14);
	m_WaterRenderer->CreateAnimation("Fail", "Pot_Fx_Fail.png", 0.1f, 0, 18);
	m_WaterRenderer->SetEndEvent("Fail", std::bind(&AlchemyPot::EndPotionCreation, this));
	m_WaterRenderer->CreateAnimation("Success", "Pot_Fx_Success.png", 0.1f, 0, 21);
	m_WaterRenderer->SetEndEvent("Success", std::bind(&AlchemyPot::EndPotionCreation, this));

	m_WaterRenderer->AutoSpriteSizeOn();


	m_FireRenderer = CreateComponent<GameEngineSpriteRenderer>(16);
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	m_FireRenderer->CreateAnimation("Small", "Pot_Fire_Small.png", 0.1f, 1, 23);
	m_FireRenderer->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_FireRenderer->AutoSpriteSizeOn();
	
	m_FireRenderer->ChangeAnimation("Small");

	m_PotFxSteam = CreateComponent<GameEngineSpriteRenderer>(17);
	if (nullptr == m_PotFxSteam)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_PotFxSteam->CreateAnimation("Steam", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_PotFxSteam->AutoSpriteSizeOn();

	m_PotFxSteam->ChangeAnimation("Steam");

	ChangeState(EPOTSTATE::Idle);
}


void AlchemyPot::CreateInteractiveCollision()
{
	m_InteractiveCol = CreateComponent<GameEngineCollision>(ECOLLISION::Entity);
	if (nullptr == m_InteractiveCol)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_InteractiveCol->SetCollisionType(ColType::SPHERE2D);
	m_InteractiveCol->Transform.SetWorldScale({ 100.0f , 100.0f });
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
	
	if (nullptr == m_WaterRenderer)
	{
		MsgBoxAssert("믿기지 않겠지만 렌더러가 존재하지 않습니다.");
		return;
	}

	m_WaterRenderer->ChangeAnimation(AnimationName);
}



void AlchemyPot::StartIdle()
{
	ChangePotCompositionAnimation("Idle");
}

void AlchemyPot::UpdateIdle(float _Delta)
{
	if (true == IsReach)
	{
		if (true == GameEngineInput::IsDown('Z'))
		{
			ChangeState(EPOTSTATE::Boil);
			return; 
		}

		IsPotionCreationStart = false;
	}
}


void AlchemyPot::StartBoil()
{
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	m_FireRenderer->ChangeAnimation("Large");


	if (nullptr == m_PotFxSteam)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	m_PotFxSteam->Off();

	ChangePotCompositionAnimation("Boil");
}

void AlchemyPot::UpdateBoil(float _Delta)
{
	if (nullptr != m_WaterRenderer && true == m_WaterRenderer->IsCurAnimationEnd())
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
	if (nullptr != m_WaterRenderer && true == m_WaterRenderer->IsCurAnimationEnd())
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
	if (nullptr != m_WaterRenderer && true == m_WaterRenderer->IsCurAnimationEnd())
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


	if (nullptr == m_PotFxSteam)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	m_PotFxSteam->On();

	IsPotionCreated = false;
}