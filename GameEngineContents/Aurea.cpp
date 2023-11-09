#include "PreCompile.h"
#include "Aurea.h"


#include "ContentsEvent.h"
#include "AureaFindEvent.h"



EAUREASTATE Aurea::CurState = EAUREASTATE::Normal;
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
	ConversationSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}

	AureaRenderer  = CreateComponent<GameEngineSpriteRenderer>();
	AureaRenderer ->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	AureaRenderer ->AutoSpriteSizeOn();
	AureaRenderer ->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	AureaRenderer ->ChangeAnimation("Idle");


	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererCorrection , GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow)});
	m_Shadow->SetSprite("Aurea_idle.png", 1);
}

void Aurea::StateSetting()
{

}


void Aurea::StartCurse(GameEngineState* _Parent)
{

}

void Aurea::StartNormal(GameEngineState* _Parent)
{

}


void Aurea::UpdateCurse(float _Delta, GameEngineState* _Parent)
{
	/*CheckAureaCurseEvent();*/

	if (true == IsEnalbeActive)
	{
		NPCEntity::InteractWithEllie(EAUREATOPICTYPE::Curse);
	}
}

void Aurea::UpdateNormal(float _Delta, GameEngineState* _Parent)
{

}



void Aurea::CheckAureaCurseEvent()
{
	const std::shared_ptr<ContentsEvent::QuestUnitBase>& Quest = ContentsEvent::FindQuest(EQUESTTYPE::Aurea_Find);
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


void Aurea::ConversationSetting()
{
	Topic CurseTopic;
	CurseTopic.EntitySpriteName = CurseTopic.Expression_Aurea_Sprite_Name;

	CurseTopic.Data.reserve(64);
	CurseTopic.Data =
	{
		{ L"안녕하세요, 혹시 마을 주민이세요?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"오, 멋진 자연이에요." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"네?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"나무가 너무 아름답지 않나요? 햇살 내린 푸른 나무..." , ECONVERSATIONENTITY::NPC , 1},
		{ L"아...네..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"정말 아름다운 자연이에요." , ECONVERSATIONENTITY::NPC , 1},
		{ L"자연을 굉장히 좋아하시나 봐요." , ECONVERSATIONENTITY::Ellie, 1},
		{ L"이렇게 아름다운 자연을 사랑하지 않을 수 없죠." , ECONVERSATIONENTITY::NPC , 1},
		{ L"그, 그럼 나중에 다시 올게요." , ECONVERSATIONENTITY::Ellie, 1},
		{ L"이 멋진 하늘 아래를 걸으며 자연을 느껴봐요!" , ECONVERSATIONENTITY::NPC , 1},
	};

	CurseTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::Curse, CurseTopic);

	NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::Curse, [&]()
		{
			NPCConversation.StartConversation(EAUREATOPICTYPE::CurseAfter);
		});

	Topic CurseAfterTopic;

	CurseAfterTopic.Data.reserve(64);
	CurseAfterTopic.Data =
	{
		{ L"정말 자연을 좋아하는 사람인가 봐." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"대화가 안 될 정도로?" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"취향은 존중해야 하지 않을까?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"단순히 취향은 아닌 것 같은데" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"안 좋은 냄사가 났단 말이야.", ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"저주라도 걸렸다는 거야?", ECONVERSATIONENTITY::Ellie , 1},
		{ L"자연을 찬양하는 말만 할 수 있는 저주?", ECONVERSATIONENTITY::Ellie , 5},
		{ L"자연주의자의 저주? 말이 안되진 않지." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"마녀들은 이상한 사람도 많으니까." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"저주를 해제할 수 있는 저주해제 사탕은 기본 제조법에 있을 텐데...", ECONVERSATIONENTITY::Ellie , 9},
		{ L"아, 근데 지금 가공 도구를 못 쓰잖아.", ECONVERSATIONENTITY::Ellie , 1},
		{ L"채집한 걸 가공해야 물약을 만들 수 있는데 어쩌지?", ECONVERSATIONENTITY::Ellie , 9},
		{ L"아까 작업실에서 재료를 몇 개 주웠잖아." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"그 정도면 저주해제 사탕 정도는 만들 수 있을꺼야." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"그리고 저 옆에 봤어?" , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"옆에? 뭐가?" , ECONVERSATIONENTITY::Ellie, 1},
		{ L"착즙기 유리병으로 딱 맞는 유리병을 들고 있어." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"어디?" , ECONVERSATIONENTITY::Ellie, 9},
		{ L"와, 정말이네." , ECONVERSATIONENTITY::Ellie, 7},
		{ L"좋아, 그럼 저주해제 사탕을 만들어서 저주를 풀어주자." , ECONVERSATIONENTITY::Ellie, 10},
		{ L"그리고 보답으로 저 유리병을 받는거지." , ECONVERSATIONENTITY::Virgil , 1, CurseAfterTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"그럼 좋고." , ECONVERSATIONENTITY::Ellie, 5},
		{ L"우선 도감에서 저주 해제 사탕을 확인해보자." , ECONVERSATIONENTITY::Ellie, 1},
	};

	CurseTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseAfter, CurseAfterTopic);

	NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseAfter, 19,[&]()
		{
			// 자연주의자의 저주
		});


	Topic CursedNaturalTopic;
	CursedNaturalTopic.EntitySpriteName = CursedNaturalTopic.Expression_Aurea_Sprite_Name;

	CursedNaturalTopic.Data.reserve(1);
	CursedNaturalTopic.Data =
	{
		{ L"오... 자연이여.." , ECONVERSATIONENTITY::NPC , 1},
	};

	CursedNaturalTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EAUREATOPICTYPE::CursedNatural, CursedNaturalTopic);
}
