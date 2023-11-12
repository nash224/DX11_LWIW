#include "PreCompile.h"
#include "Extractor.h"


#include "UI_ProcessManager.h"

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
	StaticEntity::Start();

	CreateAndSetCollision(ECOLLISION::Entity, { 150.0f , 100.0f }, float4::ZERO, ColType::AABBBOX2D);
	SetNearInteractivePositionAndRange(float4(18.0f, -16.0f), 5.0f);
	SetInteractionButtonType(EINTERACTION_BUTTONTYPE::Gear);
	SetInteractionType(EINTERACTION_TYPE::Near);
	m_CollectionMethod = ECOLLECTION_METHOD::Juicy;
	m_CollectionTool = ETOOLTYPE::Nothing;

	InitExtractor();
}

void Extractor::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	State.Update(_Delta);
}

void Extractor::Release()
{
	StaticEntity::Release();

	m_InteractiveCol = nullptr;
	m_Extractor = nullptr;

	m_ProcessManager = nullptr;
}

void Extractor::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Extractor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);

	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Extractor::InitExtractor()
{
	RendererSetting();
	UIProcessSetting();
	StateSetting();

}

void Extractor::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("DownFloor_Extractor_0.png"))
	{
		// Jucier
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
			PlaySFX("SFX_JucierActive_02.wav");
		});
}

void Extractor::UIProcessSetting()
{
	m_ProcessManager = GetLevel()->CreateActor<UI_ProcessManager>();
	m_ProcessManager->Init();
}

void Extractor::StateSetting()
{
	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&Extractor::StartIdle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&Extractor::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EJUICERSTATE::Idle, IdleState);

	CreateStateParameter JuicyState;
	JuicyState.Start = std::bind(&Extractor::StartJuicy, this, std::placeholders::_1);
	JuicyState.Stay = std::bind(&Extractor::UpdateJuicy, this, std::placeholders::_1, std::placeholders::_2);
	JuicyState.End = std::bind(&Extractor::EndJuicy, this, std::placeholders::_1);
	State.CreateState(EJUICERSTATE::Juicy, JuicyState);

	/*CreateStateParameter ConverseState;
	ConverseState.Start = std::bind(&Extractor::StartConverse, this, std::placeholders::_1);
	ConverseState.End = std::bind(&Extractor::EndConverse, this, std::placeholders::_1);
	State.CreateState(EJUICERSTATE::Converse, ConverseState);*/

	State.ChangeState(EJUICERSTATE::Idle);
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


void Extractor::StartIdle(GameEngineState* _Parent)
{
	ChangeExtractorAnimation("Idle");
}

void Extractor::StartJuicy(GameEngineState* _Parent)
{
	PlaySFX(RandomOpenJuicySoundFilleName());
	ChangeExtractorAnimation("Juicy");
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
	PlaySFX("SFX_JucierClose_01.wav");
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