#include "PreCompile.h"
#include "AlchemyPot.h"

#include "UI_Dispensation.h"

#include "UI_Inventory.h"
#include "Ellie.h"

#include "ContentsEvent.h"
#include "CraftFireCrackerEvent.h"
#include "CraftPotionEvent.h"


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
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::AlchemyPot, ETOOLTYPE::Nothing);
	InteractiveActor::SetGearName("사용하기");

	s_PotPointer = this;
}

void AlchemyPot::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
}

void AlchemyPot::Release()
{
	PotRenderer = nullptr;
	WaterRenderer = nullptr;
	FxRenderer = nullptr;
	FireRenderer = nullptr;
	SteamRenderer = nullptr;

	InteractiveCol = nullptr;

	// 연금UI
	DispensationPage = nullptr;
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

	PotRenderer = CreateComponent<GameEngineSpriteRenderer>();
	PotRenderer->SetSprite("DownFloor_Pot_0.png");
	PotRenderer->Transform.SetLocalPosition({ 0.0f , -8.0f });


	WaterRenderer = CreateComponent<GameEngineSpriteRenderer>();
	WaterRenderer->AutoSpriteSizeOn();
	WaterRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	WaterRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21);
	WaterRenderer->ChangeAnimation("Idle");


	FxRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FxRenderer->AutoSpriteSizeOn();
	FxRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));
	FxRenderer->CreateAnimation("Idle", "Pot_Fx_IdleA.png", 0.1f, 0, 21, false);
	FxRenderer->CreateAnimation("Boil", "Pot_Fx_Boil.png", 0.1f, 0, 14, false);
	FxRenderer->CreateAnimation("Fail", "Pot_Fx_Fail.png", 0.1f, 0, 18, false);
	FxRenderer->CreateAnimation("Success", "Pot_Fx_Success.png", 0.1f, 0, 21, false);


	FxRenderer->SetStartEvent("Boil", [&](GameEngineSpriteRenderer* _Renderer)
		{
			FireRenderer->ChangeAnimation("Large");
			SteamRenderer->Off();
		});


	FxRenderer->SetFrameEvent("Fail", 9, [&](GameEngineSpriteRenderer* _Renderer)
		{
			PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->WaitDone(EELLIE_STATE::Fail);
		});
	FxRenderer->SetEndEvent("Fail", std::bind(&AlchemyPot::EndPotionCreation, this));

	FxRenderer->SetFrameEvent("Success", 16, [&](GameEngineSpriteRenderer* _Renderer)
		{
			PlayLevel::GetPlayLevelPtr()->GetPlayerPtr()->WaitDone(EELLIE_STATE::Cheer);
		});
	FxRenderer->SetEndEvent("Success", std::bind(&AlchemyPot::EndPotionCreation, this));

	FxRenderer->Off();


	FireRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FireRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -1.0f));
	FireRenderer->CreateAnimation("Small", "Pot_Fire_Small.png", 0.1f, 1, 23);
	FireRenderer->CreateAnimation("Large", "Pot_Fire_Large.png", 0.1f, 1, 23);
	FireRenderer->AutoSpriteSizeOn();
	
	FireRenderer->ChangeAnimation("Small");

	SteamRenderer = CreateComponent<GameEngineSpriteRenderer>();
	SteamRenderer->AutoSpriteSizeOn();
	SteamRenderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, -2.0f));
	SteamRenderer->CreateAnimation("Steam", "Pot_Fire_Large.png", 0.1f, 1, 23);
	SteamRenderer->ChangeAnimation("Steam");
}

void AlchemyPot::DispensationSetting()
{
	DispensationPage = GetLevel()->CreateActor<UI_Dispensation>();
	DispensationPage->Init();
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
	SuccessState.End = std::bind(&AlchemyPot::EndSuccess, this, std::placeholders::_1);
	State.CreateState(EPOTSTATE::Success, SuccessState);
}

void AlchemyPot::ChangePotAnimation(std::string_view _StateName)
{
	std::string AnimationName;
	AnimationName = _StateName.data();
	
	if (nullptr == FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	FxRenderer->ChangeAnimation(AnimationName);
}



void AlchemyPot::StartBroken(GameEngineState* _Parent)
{
	FireRenderer->Off();
	SteamRenderer->Off();
	WaterRenderer->Off();

	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}

	InteractiveActor::InteractiveCol->Off();
}

void AlchemyPot::StartIdle(GameEngineState* _Parent)
{
	ChangePotAnimation("Idle");
}

void AlchemyPot::StartBoil(GameEngineState* _Parent)
{
	if (nullptr == FxRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	FxRenderer->On();

	SFXFunction::PlaySFX("SFX_MakingPotPutIn_01.wav");
	SFXFunction::PlaySFX("SFX_MakingPotStart.wav");

	if (false == CraftedPotion.empty())
	{
		SFXFunction::PlaySFX("SFX_MakingPotSucces_02.wav");
	}

	ChangePotAnimation("Boil");
}


void AlchemyPot::StartFail(GameEngineState* _Parent)
{
	SFXFunction::PlaySFX("SFX_MakingPotFail_02.wav");

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
		if (nullptr == DispensationPage)
		{
			MsgBoxAssert("연금UI가 존재하지 않습니다.");
			return;
		}

		DispensationPage->AlchemyPotPtr = this;
		DispensationPage->Open();
	}
}

void AlchemyPot::UpdateBoil(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != FxRenderer && true == FxRenderer->IsCurAnimationEnd())
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
	if (nullptr != FxRenderer && true == FxRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(EPOTSTATE::Idle);
		return;
	}
}

void AlchemyPot::UpdateSuccess(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != FxRenderer && true == FxRenderer->IsCurAnimationEnd())
	{
		State.ChangeState(EPOTSTATE::Idle);
		return;
	}
}


void AlchemyPot::EndBroken(GameEngineState* _Parent)
{
	if (nullptr == FireRenderer
		|| nullptr == SteamRenderer
		|| nullptr == WaterRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	if (nullptr == InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("존재하지 않는 충돌체입니다.");
		return;
	}

	FireRenderer->On();
	SteamRenderer->On();
	WaterRenderer->On();
	InteractiveActor::InteractiveCol->On();
}

void AlchemyPot::EndSuccess(GameEngineState* _Parent)
{
	UI_Inventory::PushItem(CraftedPotion);

	CheckCraftPotionEvent();
	CheckCraftFireCrackerEvent();

	CraftedPotion.clear();
}



void AlchemyPot::EndPotionCreation()
{
	if (nullptr == FireRenderer
		|| nullptr == SteamRenderer
		|| nullptr == FxRenderer)
	{
		MsgBoxAssert("있을수 없는 일입니다.");
		return;
	}

	if (nullptr == DispensationPage)
	{
		MsgBoxAssert("연금페이지가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	FireRenderer->ChangeAnimation("Small");
	SteamRenderer->On();
	FxRenderer->Off();
	DispensationPage->Close();
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

void AlchemyPot::CheckCraftPotionEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Craft_Potion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest.lock()->CheckPrerequisiteQuest())
	{
		Quest.lock()->QuestComplete();
		ShowCraftPotionEvent();
	}
}

void AlchemyPot::CheckCraftFireCrackerEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Craft_Cracker_Potion");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->isQuestComplete())
	{
		if (Quest.lock()->CheckPrerequisiteQuest())
		{
			ShowFireCrackerEvent();
			Quest.lock()->QuestComplete();
		}
	}
}

void AlchemyPot::ShowCraftPotionEvent()
{
	std::shared_ptr<CraftPotionEvent> Event = GetLevel()->CreateActor<CraftPotionEvent>(EUPDATEORDER::Event);
	Event->Init();
}

void AlchemyPot::ShowFireCrackerEvent()
{
	std::shared_ptr<CraftFireCrackerEvent> Event = GetLevel()->CreateActor<CraftFireCrackerEvent>(EUPDATEORDER::Event);
	Event->Init();
}