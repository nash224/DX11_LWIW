#include "PreCompile.h"
#include "Aurea.h"

#include "ContentsEvent.h"

#include "UI_Inventory.h"

EAUREASTATE Aurea::CurState = EAUREASTATE::Curse;
Aurea::Aurea()
{
}

Aurea::~Aurea()
{
}


void Aurea::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 90.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	InteractiveActor::SetGearName("대화하기");
}

void Aurea::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	State.Update(_Delta);
}

void Aurea::Release()
{
	NPCEntity::Release();

	AureaRenderer = nullptr;
	ShadowRenderer = nullptr;
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
	ApplyDepth();
	RendererSetting();
	ConversationSetting();
	StateSetting();
}

void Aurea::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Aurea_Idle.png"))
	{
		GameEngineSprite::CreateCut("Aurea_Idle.png", 3, 2);
		GameEngineSprite::CreateCut("merchant_creature.png", 7, 1);
	}

	AureaRenderer = CreateComponent<GameEngineSpriteRenderer>();
	AureaRenderer->CreateAnimation("Idle", "Aurea_idle.png", 0.15f, 2, 5, true);
	AureaRenderer->AutoSpriteSizeOn();
	AureaRenderer->Transform.SetLocalPosition({ 0.0f, RendererCorrection });
	AureaRenderer->ChangeAnimation("Idle");

	const float Depth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer->Transform.SetLocalPosition(float4{ 0.0f, RendererCorrection , Depth });
	ShadowRenderer->SetSprite("Aurea_idle.png", 1);
}

void Aurea::StateSetting()
{
	CreateStateParameter CurseState;
	CurseState.Start = std::bind(&Aurea::StartCurse, this, std::placeholders::_1);
	CurseState.Stay = std::bind(&Aurea::UpdateCurse, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EAUREASTATE::Curse, CurseState);

	CreateStateParameter NormalState;
	NormalState.Start = std::bind(&Aurea::StartNormal, this, std::placeholders::_1);
	NormalState.Stay = std::bind(&Aurea::UpdateNormal, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EAUREASTATE::Normal, NormalState);

	State.ChangeState(CurState);
}


void Aurea::StartCurse(GameEngineState* _Parent)
{
	CheckAureaCurseEvent();
}

void Aurea::StartNormal(GameEngineState* _Parent)
{

}


void Aurea::UpdateCurse(float _Delta, GameEngineState* _Parent)
{
	if (true == InteractiveActor::IsEnalbeActive)
	{
		CheckAureaCurseConversation();
	}
}

void Aurea::UpdateNormal(float _Delta, GameEngineState* _Parent)
{

}

void Aurea::ConversationSetting()
{
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
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::Curse, CurseTopic);

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::Curse, [&]()
			{
				NPCEntity::ConverseWithEllie(EAUREATOPICTYPE::CurseAfter);
			});
	}



	{
		Topic CurseAfterTopic;

		CurseAfterTopic.Data.reserve(64);
		CurseAfterTopic.Data =
		{
			{ L"정말 자연을 좋아하는 사람인가 봐." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"대화가 안 될 정도로?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"취향은 존중해야 하지 않을까?" , ECONVERSATIONENTITY::Ellie, 1 },
			{ L"단순히 취향은 아닌 것 같은데" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"안 좋은 냄사가 났단 말이야.", ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"저주라도 걸렸다는 거야?", ECONVERSATIONENTITY::Ellie , 1},
			{ L"자연을 찬양하는 말만 할 수 있는 저주?", ECONVERSATIONENTITY::Ellie , 5},
			{ L"자연주의자의 저주? 말이 안되진 않지." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"마녀들은 이상한 사람도 많으니까." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"저주를 해제할 수 있는 저주해제 사탕은 기본 제조법에 있을 텐데...", ECONVERSATIONENTITY::Ellie , 9},
			{ L"아, 근데 지금 가공 도구를 못 쓰잖아.", ECONVERSATIONENTITY::Ellie , 1},
			{ L"채집한 걸 가공해야 물약을 만들 수 있는데 어쩌지?", ECONVERSATIONENTITY::Ellie , 9},
			{ L"아까 작업실에서 재료를 몇 개 주웠잖아." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"그 정도면 저주해제 사탕 정도는 만들 수 있을꺼야." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"그리고 저 옆에 봤어?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"옆에? 뭐가?" , ECONVERSATIONENTITY::Ellie, 1},
			{ L"착즙기 유리병으로 딱 맞는 유리병을 들고 있어." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"어디?" , ECONVERSATIONENTITY::Ellie, 9},
			{ L"와, 정말이네." , ECONVERSATIONENTITY::Ellie, 7},
			{ L"좋아, 그럼 저주해제 사탕을 만들어서 저주를 풀어주자." , ECONVERSATIONENTITY::Ellie, 10},
			{ L"그리고 보답으로 저 유리병을 받는거지." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
			{ L"그럼 좋고." , ECONVERSATIONENTITY::Ellie, 5},
			{ L"우선 도감에서 저주 해제 사탕을 확인해보자." , ECONVERSATIONENTITY::Ellie, 1},
		};

		CurseAfterTopic.Data.shrink_to_fit();
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseAfter, CurseAfterTopic);

		NPCEntity::NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseAfter, 19, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("생성하지 않은 퀘스트입니다.");
					return;
				}

				Quest.lock()->QuestAccept();
			});

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::CurseAfter, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("생성하지 않은 퀘스트입니다.");
					return;
				}

				Quest.lock()->QuestAccept();
			});
	}



	{
		Topic CurseCureTopic;
		CurseCureTopic.EntitySpriteName = CurseCureTopic.Expression_Aurea_Sprite_Name;

		CurseCureTopic.Data.reserve(64);
		CurseCureTopic.Data =
		{
			{ L"이거 한 번 드셔보시겠어요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"아, 당신께 자연의 축복을..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"안...녕...?" , ECONVERSATIONENTITY::NPC, 0 },
			{ L"네, 안녕하세요" , ECONVERSATIONENTITY::Ellie , 5},
			{ L"지금 내가 제대로 말하고 있어?" , ECONVERSATIONENTITY::NPC, 0 },
			{ L"네, 그런 거 같아요" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"와, 정말 고마워. 자연은 엿이나 먹으라지." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"정말 저주였나 보네요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"서쪽 정글에서 만난 그 영감은 딱 봐도 수상했는데." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"너무 잘 만든 그 원숭이 목상을 그냥 지나칠 수가 없어서 말야." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"그걸 산 뒤로는 모든 말이 자연을 찬양하는 말만 나와서..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"거꾸로도 말해보고, 글로 적어봐도 다 자연을 찬양하는 말 밖에 할 수 없어서 너무 힘들었어." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"정말 자연은 엿이나 먹었으면 좋겠어." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"그래도 간단하게 해제 가능한 저주라서 다행이네요." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"아, 정말 고마워. 내 이름은 아우레아야." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"얼마 만에 말해보는 이름인지..." , ECONVERSATIONENTITY::NPC, 0 },
			{ L"저는 엘리에요. 수습 마녀에요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"혹시 내가 도와줄만한게 있니? 아까의 보답을 하고 싶어." , ECONVERSATIONENTITY::NPC , 0},
			{ L"아, 그럼 부탁.. 하나 드려도 될까요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"부탁이 아니라 정당한 값이야." , ECONVERSATIONENTITY::NPC , 1},
			{ L"어떤게 필요해?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"마녀의 집 조제실을 사용하려고 하니까 도구들이 부서져 있어서." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"도구나 부품이 있으신가요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"어떤 도구나 부품이 필요해?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"착즙기에 들어가는 유리병이랑, 로스터를 돌릴 로스터 손잡이가 필요해요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"잠시만... 한 번 찾아볼게." , ECONVERSATIONENTITY::NPC , 0},
			{ L"찾아왔어." , ECONVERSATIONENTITY::NPC , 1},
			{ L"이거 받아." , ECONVERSATIONENTITY::NPC , 0},
			{ L"이건 얼마에요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"아, 괜찮아. 이건 네가 내 저주를 풀어준 답레야." , ECONVERSATIONENTITY::NPC , 1},
			{ L"와, 다행이다." , ECONVERSATIONENTITY::Ellie, 5 },
			{ L"아쉽지만 로스터에 쓸 로스터 손잡이는 가지고 있는게 없어." , ECONVERSATIONENTITY::NPC , 1},
			{ L"하지만 다음에 올 때 챙겨올게." , ECONVERSATIONENTITY::NPC , 1},
			{ L"그 때는 값을 제대로 받을 거지만 말야." , ECONVERSATIONENTITY::NPC , 1},
			{ L"좋아요, 그 때 부탁드릴게요." , ECONVERSATIONENTITY::Ellie, 5 },
		};

		CurseCureTopic.Data.shrink_to_fit();
		NPCEntity::NPCConversation.CreateTopic(EAUREATOPICTYPE::CurseCure, CurseCureTopic);

		NPCEntity::NPCConversation.SetConversationEvent(EAUREATOPICTYPE::CurseCure, 28, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("생성하지 않은 퀘스트입니다.");
					return;
				}

				Quest.lock()->QuestComplete();
			});

		NPCEntity::NPCConversation.SetConversationEndEvent(EAUREATOPICTYPE::CurseCure, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Aurea_Cure");
				if (true == Quest.expired())
				{
					MsgBoxAssert("생성하지 않은 퀘스트입니다.");
					return;
				}

				Quest.lock()->QuestComplete();

				CurState = EAUREASTATE::Normal;
				State.ChangeState(EAUREASTATE::Normal);
			});
	}


	{
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
}
