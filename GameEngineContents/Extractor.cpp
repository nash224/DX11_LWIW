#include "PreCompile.h"
#include "Extractor.h"


#include "UI_ProcessManager.h"

#include "ContentsEvent.h"

Extractor* Extractor::s_ExtractorPointer = nullptr;
Extractor::Extractor() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_JucierActive_02.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Machine\\Jucier");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

Extractor::~Extractor() 
{
}


void Extractor::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 150.0f , 100.0f }, float4::ZERO, ColType::AABBBOX2D);
	InteractiveActor::SetNearInteractivePositionAndRange(float4(18.0f, -16.0f), 5.0f);
	InteractiveActor::SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
	InteractiveActor::SetInteractionType(EINTERACTION_TYPE::Near);
	InteractiveActor::m_CollectionMethod = ECOLLECTION_METHOD::Juicy;
	InteractiveActor::m_CollectionTool = ETOOLTYPE::Nothing;

	InitExtractor();

	s_ExtractorPointer = this;
}

void Extractor::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
}

void Extractor::Release()
{
	StaticEntity::Release();

	m_Extractor = nullptr;
	m_ProcessManager = nullptr;
	s_ExtractorPointer = nullptr;
}

void Extractor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Extractor::InitExtractor()
{
	RendererSetting();
	UIProcessSetting();
	StateSetting();


	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Repair_Extractor");
	if (true == Quest.expired())
	{
		MsgBoxAssert("존재하지 않는 퀘스트입니다.");
		return;
	}

	if (true == Quest.lock()->isQuestComplete())
	{
		State.ChangeState(EJUICERSTATE::Idle);
	}
	else
	{
		State.ChangeState(EJUICERSTATE::Broken);
	}
}

void Extractor::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("DownFloor_Extractor_0.png"))
	{
		GameEngineSprite::CreateCut("DownFloor_Extractor_0.png", 5, 4);
		GameEngineSprite::CreateCut("DownFloor_Extractor_1.png", 5, 4);
	}

	m_Extractor = CreateComponent<GameEngineSpriteRenderer>();
	m_Extractor->AutoSpriteSizeOn();
	m_Extractor->Transform.SetLocalPosition(float4(0.0f, 46.0f));

	m_Extractor->CreateAnimation("Broken", "DownFloor_Extractor_Idle_Broken.png");
	m_Extractor->CreateAnimation("Idle", "DownFloor_Extractor_0.png", 5.0f, 1, 1, false);
	m_Extractor->CreateAnimation("Juicy", "DownFloor_Extractor_0.png", 0.1f, 2, 9, false);
	m_Extractor->FindAnimation("Juicy")->Inter = { 0.2f, 0.18f, 0.19f, 0.2f, 0.19f, 0.19f, 0.12f, 0.12f, 0.12f };


	m_Extractor->SetFrameEvent("Juicy", 3, [&](GameEngineSpriteRenderer* _Renderer)
		{
			StaticEntity::PlaySFX("SFX_JucierActive_02.wav");
		});
}

void Extractor::UIProcessSetting()
{
	m_ProcessManager = GetLevel()->CreateActor<UI_ProcessManager>();
	m_ProcessManager->Init();
}

void Extractor::StateSetting()
{
	CreateStateParameter BrokenState;
	BrokenState.Start = std::bind(&Extractor::StartBroken, this, std::placeholders::_1);
	BrokenState.Stay = std::bind(&Extractor::UpdateBroken, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EJUICERSTATE::Broken, BrokenState);

	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&Extractor::StartIdle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&Extractor::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EJUICERSTATE::Idle, IdleState);

	CreateStateParameter JuicyState;
	JuicyState.Start = std::bind(&Extractor::StartJuicy, this, std::placeholders::_1);
	JuicyState.Stay = std::bind(&Extractor::UpdateJuicy, this, std::placeholders::_1, std::placeholders::_2);
	JuicyState.End = std::bind(&Extractor::EndJuicy, this, std::placeholders::_1);
	State.CreateState(EJUICERSTATE::Juicy, JuicyState);
}


void Extractor::PullThis()
{
	State.ChangeState(EJUICERSTATE::Juicy);
}

void Extractor::ChangeExtractorAnimation(std::string_view _StateName)
{
	if (nullptr == m_Extractor)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Extractor->ChangeAnimation(_StateName.data());
}

void Extractor::StartBroken(GameEngineState* _Parent)
{
	InteractiveActor::SetInteractionType(EINTERACTION_TYPE::Far);

	if (nullptr != InteractiveActor::InteractiveCol)
	{
		InteractiveActor::InteractiveCol->Off();
	}

	ChangeExtractorAnimation("Broken");
}

void Extractor::StartIdle(GameEngineState* _Parent)
{
	ChangeExtractorAnimation("Idle");
}

void Extractor::StartJuicy(GameEngineState* _Parent)
{
	StaticEntity::PlaySFX(RandomOpenJuicySoundFilleName());
	ChangeExtractorAnimation("Juicy");
}

void Extractor::UpdateBroken(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Repair_Extractor");
		if (true == Quest.expired())
		{
			MsgBoxAssert("생성되지 않은 퀘스트를 참조하려 했습니다.");
			return;
		}

		if (true == Quest.lock()->CheckPrerequisiteQuest())
		{
			Quest.lock()->QuestComplete();

			InteractiveActor::SetInteractionType(EINTERACTION_TYPE::Near);

			State.ChangeState(EJUICERSTATE::Idle);
		}
	}
}

void Extractor::UpdateIdle(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr != m_ProcessManager)
		{
			m_ProcessManager->Open();
		}
	}
}
 
void Extractor::UpdateJuicy(float _Delta, GameEngineState* _Parent)
{
	if (true == m_Extractor->IsCurAnimationEnd())
	{
		State.ChangeState(EJUICERSTATE::Idle);
		return;
	}
}



void Extractor::EndJuicy(GameEngineState* _Parent)
{
	StaticEntity::PlaySFX("SFX_JucierClose_01.wav");
}



std::string Extractor::RandomOpenJuicySoundFilleName()
{
	GameEngineRandom RandomClass;
	int SelectValue = RandomClass.RandomInt(1, 2);

	std::string_view FileName;

	switch (SelectValue)
	{
	case 1:
		FileName = "SFX_JucierOpen_01.wav";
		break;
	case 2:
		FileName = "SFX_JucierOpen_02.wav";
		break;
	default:
		break;
	}

	return FileName.data();
}

void Extractor::ActiveInteractiveCollision()
{
	if (nullptr == s_ExtractorPointer)
	{
		MsgBoxAssert("레벨이 다른 곳에서 추출기를 사용하려 했습니다.");
		return;
	}

	
	if (nullptr == s_ExtractorPointer->InteractiveActor::InteractiveCol)
	{
		MsgBoxAssert("충돌체가 생성되지 않았습니다.");
		return;
	}
	
	s_ExtractorPointer->InteractiveActor::InteractiveCol->On();
}