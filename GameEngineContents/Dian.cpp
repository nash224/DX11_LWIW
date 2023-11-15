#include "PreCompile.h"
#include "Dian.h"

#include "UIManager.h"
#include "UI_Alert_Quest.h"

#include "ContentsEvent.h"


Dian::Dian()
{
}

Dian::~Dian()
{
}


void Dian::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 60.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);

	ConversationSetting();
	StateSetting();
}

void Dian::Update(float _Delta)
{
	NPCEntity::Update(_Delta);

	State.Update(_Delta);
}

void Dian::Release()
{
	NPCEntity::Release();
	DianRenderer = nullptr;
	ShadowRenderer = nullptr;
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dian::Init()
{
	ApplyDepth(Transform.GetLocalPosition());
	RendererSetting();
}


void Dian::RendererSetting()
{
	if (nullptr == GameEngineSprite::Find("Dian_idle.png"))
	{
		GameEngineSprite::CreateCut("Dian_idle.png", 3, 3);
	}

	static constexpr const int RendererOrder = 0;

	DianRenderer = CreateComponent<GameEngineSpriteRenderer>(RendererOrder);
	DianRenderer->Transform.SetLocalPosition({ 0.0f, RendererYCorrection });
	DianRenderer->CreateAnimation("Idle", "Dian_idle.png", 0.2f, 4, 7, true);
	DianRenderer->AutoSpriteSizeOn();
	DianRenderer->ChangeAnimation("Idle");


	const float ShadowDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>(RendererOrder);
	ShadowRenderer->Transform.SetLocalPosition({ 0.0f, RendererYCorrection, ShadowDepth });
	ShadowRenderer->SetSprite("Dian_idle.png", 0);
}


void Dian::StateSetting()
{
	CreateStateParameter NormalState;
	NormalState.Stay = std::bind(&Dian::NormalUpdate, this, std::placeholders::_1, std::placeholders::_2);

	State.CreateState(EDIANSTATE::Normal, NormalState);
	State.ChangeState(EDIANSTATE::Normal);
}

void Dian::NormalUpdate(float _DeltaTime, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_Catalogue");
		if (true == Quest.expired())
		{
			MsgBoxAssert("아직 생성하지 않은 퀘스트입니다.");
			return;
		}

		if (false == Quest.lock()->isQuestComplete())
		{
			NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::WitchCatalogue);
			return;
		}

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::FireCracker);
	}
}

void Dian::ConversationSetting()
{
	{
		Topic NaturalTopic;
		NaturalTopic.EntitySpriteName = NaturalTopic.Expression_Dian_Sprite_Name;

		NaturalTopic.Data.reserve(64);
		NaturalTopic.Data =
		{
			{ L"정시 퇴근이 목표에요." , ECONVERSATIONENTITY::NPC , 0},
		};

		NaturalTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::Natural, NaturalTopic);
	}



	{
		Topic WitchCatalogueTopic;
		WitchCatalogueTopic.EntitySpriteName = WitchCatalogueTopic.Expression_Dian_Sprite_Name;
		WitchCatalogueTopic.Default_Npc_Sprite_Index = 4;

		WitchCatalogueTopic.Data.reserve(64);
		WitchCatalogueTopic.Data =
		{
			{ L"안녕하세요! 가장 싸게, 가장 좋은 제품을 드리는 마녀 카탈로그 입니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"행복을 드리는 다이엔 그린윈드입니다. 반가워요!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"네, 안녕하세요. 수습 마녀 엘리에요." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"네, 반갑습니다 엘리!" , ECONVERSATIONENTITY::NPC , 0},
			{ L"제가 오늘 도와드려야 하는 일이... 처음 등록하시는군요!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"마녀 카탈로그를 안 쓰고 계셨다니 불편하셨겠네요." , ECONVERSATIONENTITY::NPC , 0},
			{ L"네, 맞아요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"지금 가입하면 선물도 드립니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"와, 선물이요? 뭔데요?" , ECONVERSATIONENTITY::Ellie , 8},
			{ L"간편하게 이용할 수 있는 마녀 빗자루입니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"마녀 빗자루! 드디어!" , ECONVERSATIONENTITY::Ellie , 8},
			{ L"여기랑 여기에 서명 해주시면 됩니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"네, 잠시만요..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"네, 됐습니다! 지금부터 마법 빗자루와 마녀 카탈로그를 이용하실 수 있습니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"매일 아침에 마녀 카탈로그 직원이, 여기선 제가, 찾아오게 됩니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"혹시 질문 있으신가요?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"아뇨, 이제 없어요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"네, 그럼 필요한 게 있으시면 언제든지 말을 걸어주세요." , ECONVERSATIONENTITY::NPC , 0},
			{ L"저기..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"네, 말씀하세요." , ECONVERSATIONENTITY::NPC , 0},
			{ L"사은품은..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"아, 지금 바로 드리겠습니다." , ECONVERSATIONENTITY::NPC , 1},
			{ L"드디어 내 개인 빗자루가!" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"행복한 하루 되세요. 마녀 카탈로그의 다이엔 그린윈드였습니다." , ECONVERSATIONENTITY::NPC , 1},
		};

		WitchCatalogueTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::WitchCatalogue, WitchCatalogueTopic);


		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::WitchCatalogue, 22, [&]()
			{
				// 마법 빗자루 get
			});
		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::WitchCatalogue, 23, [&]()
			{
				// 마법 빗자루 Frame
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::WitchCatalogue, [&]()
			{

			});
	}


	{
		Topic PotionVerificationTopic;
		PotionVerificationTopic.EntitySpriteName = PotionVerificationTopic.Expression_Dian_Sprite_Name;
		PotionVerificationTopic.Default_Npc_Sprite_Index = 4;

		PotionVerificationTopic.Data.reserve(64);
		PotionVerificationTopic.Data =
		{
			{ L"안녕하세요, 다이엔." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"흠..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"다이엔?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"끄으응..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"다이엔!!!" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"안녕하세요! 가장 싸게, 가장 좋은 제품을 드리는 마녀 카탈로그입니다!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"행복을 들리는 다이엔...아, 엘리였군요. 반갑습니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"죄송합니다, 프로답지 못한 모습을 보였네요." , ECONVERSATIONENTITY::NPC , 0},
			{ L"무슨 일이라도 있나요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"흠...만나뵌지 얼마 되지 않은 엘리에게 이런 말씀을 드려도 될런지..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"뭔데요? 제가 도울 수 있을지도 모르잖아요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"음. 마녀 행정부에서 물약 매입 서비스를 하는데요.." , ECONVERSATIONENTITY::NPC , 0},
			{ L"그런데 최근에 불량 물약 신고가 대량으로 들어와서 말이죠." , ECONVERSATIONENTITY::NPC , 0},
			{ L"물약 품질은 마녀 카탈로그의 신뢰, 마녀 카탈로그의 신뢰는 곧 행정부의 신뢰!" , ECONVERSATIONENTITY::NPC , 0},
			{ L"그때문에 행정부에서 각 카탈로그 판매원들에게 의심가는 물약 테스트를 하란 공문이 내려왔습니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"문제는 하필 제가 담당한 마녀의 집들이 해당 물약들과 관련이 있어서..." , ECONVERSATIONENTITY::NPC , 0},
			{ L"엘리도 알다시피 물약 품질은 마녀의 자신감 문제기도 하니까요." , ECONVERSATIONENTITY::NPC , 0},
			{ L"테스트 물약으로 나쁜 풀 제거 물약이 필요할 것 같습니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"괜찮다면 엘리의 도움을 받을 수 있을까요?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"보상이라기엔 약소하지만...잠자리채를 준비했습니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"잠자리채!!" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"좋아요, 제가 도울게요!" , ECONVERSATIONENTITY::Ellie , 5},
			{ L"고마워요, 엘리. 그럼 부탁드릴게요" , ECONVERSATIONENTITY::NPC , 1},
		};

		PotionVerificationTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::PotionVerification, PotionVerificationTopic);

		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::PotionVerification, 21, [&]()
			{
				// 퀘스트 수락
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::PotionVerification, [&]()
			{

			});
	}


	{
		Topic DragonFlyTopic;
		DragonFlyTopic.EntitySpriteName = DragonFlyTopic.Expression_Dian_Sprite_Name;
		DragonFlyTopic.Default_Npc_Sprite_Index = 4;

		DragonFlyTopic.Data.reserve(64);
		DragonFlyTopic.Data =
		{
			{ L"안녕하세요, 나쁜 풀 제거 물약을 가져왔어요." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"고마워요, 엘리. 덕분에 테스트를 할 수 있게 됐어요!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"여기 보상으로 약속한 잠자리채입니다." , ECONVERSATIONENTITY::NPC , 0},
			{ L"오늘도 이용해주셔서 감사합니다." , ECONVERSATIONENTITY::NPC, 1},
		};

		DragonFlyTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::DragonFly, DragonFlyTopic);

		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::DragonFly, 2, [&]()
			{
				// 잠자리채
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::DragonFly, [&]()
			{

			});
	}

	{
		Topic FireCrackerTopic;
		FireCrackerTopic.EntitySpriteName = FireCrackerTopic.Expression_Dian_Sprite_Name;
		FireCrackerTopic.Default_Npc_Sprite_Index = 4;

		FireCrackerTopic.Data.reserve(64);
		FireCrackerTopic.Data =
		{
			{ L"폭죽 물약이라. 저도 꼭 만들어보고 싶었던 물약이죠.  " , ECONVERSATIONENTITY::NPC , 1},
			{ L"다이엔도요?" , ECONVERSATIONENTITY::Ellie, 1 },
			{ L"그럼요. 별총제의 하이라이트잖아요." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"그쵸. 저도 마지막 날 불꽃놀이가 제일 좋았어요." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"이번에 쓰고 싶은 곳이 있는데 조제법을 구할 수 있을까요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"흠...조제법을 카탈로그에 등록해드리는건 어렵지 않지만 " , ECONVERSATIONENTITY::NPC , 4},
			{ L"엘리도 알다시피 마녀 학교 재학 중에는 폭죽 물약 조제가 금지되어 있습니다." , ECONVERSATIONENTITY::NPC, 0},
			{ L"수습 중인데도요?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"정확히는 제약이 있습니다." , ECONVERSATIONENTITY::NPC, 0},
			{ L"제약이 없던 시절에 폭죽 물약을 맞고 엉덩이가 터지거나 집이 불에 탄 사례가 많아서..." , ECONVERSATIONENTITY::NPC, 0},
			{ L"어떤 용도로, 몇 개 만드는지 마녀 행정부에 보고 해야 합니다." , ECONVERSATIONENTITY::NPC, 0},
			{ L"해, 행정부..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"지금 보증인을 설 수 있으신 분이 계신가요?" , ECONVERSATIONENTITY::NPC, 0},
			{ L"아, 아니요..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"정 그러시면 다른 보증인의 이름을 적으셔도 괜찮습니다." , ECONVERSATIONENTITY::NPC, 1},
			{ L"아리아..그리고 앨리. 1개. 수습 진행..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"네 확인했습니다." , ECONVERSATIONENTITY::NPC, 1},
			{ L"다이엔이었습니다. 오늘도 이용해주셔서 감사합니다." , ECONVERSATIONENTITY::NPC, 1},
		};

		FireCrackerTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCracker, FireCrackerTopic);

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCracker, [&]()
			{
				NPCConversation.StartConversation(EDIANTOPICTYPE::FireCrackerAfter);
			});
	}

	{
		Topic FireCrackerAfterTopic;

		FireCrackerAfterTopic.Data.reserve(64);
		FireCrackerAfterTopic.Data =
		{
			{ L"휴...이럴 때마다 심장이 쿵쾅거려." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"일단 당장 생각나는 게 엄마 이름이라서 적었는데...괜찮겠지?." , ECONVERSATIONENTITY::Ellie, 5 },
			{ L"우선 목적은 달성했으니 폭죽 물약을 만들러 가자고." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"걱정된다. 정말." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		};

		FireCrackerAfterTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCrackerAfter, FireCrackerAfterTopic);


		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCrackerAfter, [&]()
			{
				const std::shared_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
			});
	}
}