#include "PreCompile.h"
#include "Extractor.h"


#include "UI_ProcessManager.h"

Extractor::Extractor() 
{
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

	UpdateState(_Delta);
}

void Extractor::Release()
{
	StaticEntity::Release();

	m_InteractiveCol = nullptr;
	m_Extractor = nullptr;
}

void Extractor::LevelStart(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelStart(_NextLevel);
}

void Extractor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	StaticEntity::LevelEnd(_NextLevel);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Extractor::InitExtractor()
{
	CreateRendererAndAnimation();
	UIProcessSetting();

}

void Extractor::CreateRendererAndAnimation()
{
	if (nullptr == GameEngineSprite::Find("DownFloor_Extractor_0.png"))
	{
		// Jucier
		GameEngineSprite::CreateCut("DownFloor_Extractor_0.png", 5, 4);
		GameEngineSprite::CreateCut("DownFloor_Extractor_1.png", 5, 4);
	}

	m_Extractor = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_Extractor)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	m_Extractor->CreateAnimation("Broken", "DownFloor_Extractor_Idle_Broken.png");
	m_Extractor->CreateAnimation("Idle", "DownFloor_Extractor_0.png", 5.0f, 1, 1, false);
	m_Extractor->CreateAnimation("Juicy", "DownFloor_Extractor_0.png", 0.1f, 2, 9, false);
	m_Extractor->FindAnimation("Juicy")->Inter = { 0.2f, 0.18f, 0.19f, 0.2f, 0.19f, 0.19f, 0.12f, 0.12f, 0.12f };
	
	m_Extractor->Transform.SetLocalPosition(float4(0.0f, 46.0f));
	m_Extractor->AutoSpriteSizeOn();

	ChangeState(EJUICERSTATE::Idle);
}

void Extractor::UIProcessSetting()
{
	m_ProcessManager = GetLevel()->CreateActor<UI_ProcessManager>();
	m_ProcessManager->Init();
}


void Extractor::PullThis()
{
	ChangeState(EJUICERSTATE::Juicy);
}




void Extractor::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case EJUICERSTATE::None:
	{
		MsgBoxAssert("None으로 세팅했습니다.");
		return;
	}
	break;
	case EJUICERSTATE::Idle:
		UpdateIdle(_Delta);
		break;
	case EJUICERSTATE::Juicy:
		UpdateJuicy(_Delta);
		break;
	default:
		break;
	}
}

void Extractor::ChangeState(EJUICERSTATE _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case EJUICERSTATE::Idle:
			StartIdle();
			break;
		case EJUICERSTATE::Juicy:
			StartJuicy();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void Extractor::ChangeExtractorCompositionAnimation(std::string_view _StateName)
{
	if (nullptr == m_Extractor)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return;
	}

	m_Extractor->ChangeAnimation(_StateName.data());
}


void Extractor::StartIdle()
{
	ChangeExtractorCompositionAnimation("Idle");
}

void Extractor::UpdateIdle(float _Delta)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr != m_ProcessManager)
		{
			m_ProcessManager->Open();
		}
	}
}
 
void Extractor::StartJuicy()
{
	ChangeExtractorCompositionAnimation("Juicy");
}

void Extractor::UpdateJuicy(float _Delta)
{
	if (true == m_Extractor->IsCurAnimationEnd())
	{
		ChangeState(EJUICERSTATE::Idle);
		return;
	}
}