#include "PreCompile.h"
#include "Aurea.h"


#include "ContentsEvent.h"
#include "AureaFindEvent.h"

Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 180.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void Aurea::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	/*CheckAureaCurseEvent();*/
}

void Aurea::Release()
{
	NPCEntity::Release();
}

void Aurea::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void Aurea::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Aurea::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}

	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	m_Body->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	m_Body->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererCorrection , GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)});
	m_Shadow->SetSprite("Aurea_idle.png", 1);
}


void Aurea::CheckAureaCurseEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest(EEVENTTYPE::Aurea_Find);
	if (nullptr == Quest)
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest->isQuestComplete())
	{
		ShowFindAureaEvent();
		Quest->QuestComplete();
	}
}

void Aurea::ShowFindAureaEvent()
{
	std::shared_ptr<AureaFindEvent> Event = GetLevel()->CreateActor<AureaFindEvent>(EUPDATEORDER::Event);
	Event->AureaPtr = this;
	Event->Init();
}