#include "PreCompile.h"
#include "AlchemyPot.h"

#include "UI_Dispensation.h"

#include "UI_Inventory.h"
#include "Ellie.h"

#include "ContentsEvent.h"


AlchemyPot* AlchemyPot::s_PotPointer = nullptr;
AlchemyPot::AlchemyPot() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_MakingPot.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Machine\\MakingPot");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

AlchemyPot::~AlchemyPot() 
{
}


void AlchemyPot::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 160.0f , 100.0f }, float4(0.0f, -100.0f), ColType::SPHERE2D);
	SetInteractionType(EINTERACTION_TYPE::Far);
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
	m_CollectionMethod = ECOLLECTION_METHOD::AlchemyPot;
	m_CollectionTool = ETOOLTYPE::Nothing;

	s_PotPointer = this;
}

void AlchemyPot::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
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
	s_PotPointer = nullptr;
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
	StateSetting();
	DispensationSetting();

	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Craft_Potion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest.lock()->IsQuestAccepted())
	{
		State.ChangeState(EPOTSTATE::Idle);
	}
	else
	{
		State.ChangeState(EPOTSTATE::Broken);
	}
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
	m_WaterRenderer->AutoSpriteSizeOn();
	m_WaterRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	m_WaterRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21);
	m_WaterRenderer->ChangeAnimation("Idle");


	m_FxRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_FxRenderer->AutoSpriteSizeOn();
	m_FxRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));
	m_FxRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21, false);
	m_FxRenderer->CreateAnimation("Boil", "Pot_Fx_Boil.png", 0.1f, 0, 14, false);
	m_FxRenderer->CreateAnimation("Fail", "Pot_Fx_Fail.png", 0.1f, 0, 18, false);
	m_FxRenderer->CreateAnimation("Success", "Pot_Fx_Success.png", 0.1f, 0, 21, false);


	m_FxRenderer->SetStartEvent("Boil", [&](GameEngineSpriteRenderer* _Renderer)
		{
			m_FireRenderer->ChangeAnimation("Large");
			m_SteamRenderer->Off();
		});


	m_FxRenderer->SetFrameEvent("Fail", 9, [&](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == Ellie::MainEllie)
			{
				MsgBoxAssert("앨리가 존재하지 않습니다.");
				return;
			}

			Ellie::MainEllie->WaitDone(EELLIE_STATE::Fail);
		});
	m_FxRenderer->SetEndEvent("Fail", std::bind(&AlchemyPot::EndPotionCreation, this));

	m_FxRenderer->SetFrameEvent("Success", 16, [&](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr == Ellie::MainEllie)
			{
				MsgBoxAssert("앨리가 존재하지 않습니다.");
				return;
			}

			Ellie::MainEllie->WaitDone(EELLIE_STATE::Cheer);
		});
	m_FxRenderer->SetEndEvent("Success", std::bind(&AlchemyPot::EndPotionCreation, this));

	m_FxRenderer->Off();


	m_FireRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_FireRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	m_FireRenderer->CreateAnimation("Small", "Pot_Fire_Small.png", 0.1f, 1, 23);
	m_FireRenderer->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_FireRenderer->AutoSpriteSizeOn();
	
	m_FireRenderer->ChangeAnimation("Small");

	m_SteamRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_SteamRenderer->AutoSpriteSizeOn();
	m_SteamRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));
	m_SteamRenderer->CreateAnimation("Steam", "Pot_Fire_Large.png", 0.1f, 1, 23);
	m_SteamRenderer->ChangeAnimation("Steam");
}

void AlchemyPot::DispensationSetting()
{
	m_Dispensation = GetLevel()->CreateActor<UI_Dispensation>();
	m_Dispensation->Init();
}

void AlchemyPot::StateSetting()
{
	CreateStateParameter BrokenState;
	BrokenState.Start = std::bind(&AlchemyPot::StartBroken, this, std::placeholders::_1);
	BrokenState.Stay = std::bind(&AlchemyPot::UpdateBroken, this, std::placeholders::_1, std::placeholders::_2);
	BrokenState.End = std::bind(&AlchemyPot::EndBroken, this, std::placeholders::_1);
	State.CreateState(EPOTSTATE::Broken, BrokenState);

	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&AlchemyPot::StartIdle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&AlchemyPot::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPOTSTATE::Idle, IdleState);

	CreateStateParameter BoilState;
	BoilState.Start = std::bind(&AlchemyPot::StartBoil, this, std::placeholders::_1);
	BoilState.Stay = std::bind(&AlchemyPot::UpdateBoil, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPOTSTATE::Boil, BoilState);

	CreateStateParameter FailState;
	FailState.Start = std::bind(&AlchemyPot::StartFail, this, std::placeholders::_1);
	FailState.Stay = std::bind(&AlchemyPot::UpdateFail, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPOTSTATE::Fail, FailState);

	CreateStateParameter SuccessState;
	SuccessState.Start = std::bind(&AlchemyPot::StartSuccess, this, std::placeholders::_1);
	SuccessState.Stay = std::bind(&AlchemyPot::UpdateSuccess, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EPOTSTATE::Success, SuccessState);
}

void AlchemyPot::ChangePotAnimation(std::string_view _StateName)
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



void AlchemyPot::StartBroken(GameEngineState* _Parent)
{
	m_FireRenderer->Off();
	m_SteamRenderer->Off();
	m_WaterRenderer->Off();

	if (nullptr == InteractiveActor::m_InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}

	InteractiveActor::m_InteractiveCol->Off();
}

void AlchemyPot::StartIdle(GameEngineState* _Parent)
{
	ChangePotAnimation("Idle");
}

void AlchemyPot::StartBoil(GameEngineState* _Parent)
{
	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_FxRenderer->On();

	PlaySFX("SFX_MakingPotPutIn_01.wav");
	PlaySFX("SFX_MakingPotStart.wav");

	if (false == CraftedPotion.empty())
	{
		PlaySFX("SFX_MakingPotSucces_02.wav");
	}

	ChangePotAnimation("Boil");
}


void AlchemyPot::StartFail(GameEngineState* _Parent)
{
	PlaySFX("SFX_MakingPotFail_02.wav");

	ChangePotAnimation("Fail");
}

void AlchemyPot::StartSuccess(GameEngineState* _Parent)
{
	ChangePotAnimation("Success");
}



void AlchemyPot::UpdateBroken(float _Delta, GameEngineState* _Parent)
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Craft_Potion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest.lock()->IsQuestAccepted() || true == Quest.lock()->isQuestComplete())
	{
		State.ChangeState(EPOTSTATE::Idle);
	}
}

void AlchemyPot::UpdateIdle(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr == m_Dispensation)
		{
			MsgBoxAssert("연금UI가 존재하지 않습니다.");
			return;
		}

		m_Dispensation->AlchemyPotPtr = this;
		m_Dispensation->Open();
	}
}

void AlchemyPot::UpdateBoil(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		if (false == CraftedPotion.empty())
		{
			State.ChangeState(EPOTSTATE::Success);
			return;
		}
		else
		{
			State.ChangeState(EPOTSTATE::Fail);
			return;
		}
	}
}

void AlchemyPot::UpdateFail(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(EPOTSTATE::Idle);
		return;
	}
}

void AlchemyPot::UpdateSuccess(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != m_FxRenderer && true == m_FxRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(EPOTSTATE::Idle);
		return;
	}
}


void AlchemyPot::EndBroken(GameEngineState* _Parent)
{
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == m_SteamRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == m_WaterRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == InteractiveActor::m_InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}

	m_FireRenderer->On();
	m_SteamRenderer->On();
	m_WaterRenderer->On();
	InteractiveActor::m_InteractiveCol->On();
}

void AlchemyPot::EndSuccess(GameEngineState* _Parent)
{
	if (nullptr != UI_Inventory::MainInventory)
	{
		UI_Inventory::MainInventory->PushItem(CraftedPotion);
	}

	CraftedPotion.clear();
}



void AlchemyPot::EndPotionCreation()
{
	if (nullptr == m_FireRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	if (nullptr == m_SteamRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	if (nullptr == m_FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == m_Dispensation)
	{
		MsgBoxAssert("연금페이지가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	m_FireRenderer->ChangeAnimation("Small");
	m_SteamRenderer->On();
	m_FxRenderer->Off();
	m_Dispensation->Close();
}

void AlchemyPot::DispensatePotion(std::string_view _CraftedPotionName)
{
	CraftedPotion = _CraftedPotionName;
	State.ChangeState(EPOTSTATE::Boil);
}

void AlchemyPot::RepairPot()
{
	if (nullptr == s_PotPointer)
	{
		MsgBoxAssert("다른 레벨에서 솥을 참조하려 했습니다.");
		return;
	}
	
	s_PotPointer->State.ChangeState(EPOTSTATE::Idle);
}