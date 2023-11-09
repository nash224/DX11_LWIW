#include "PreCompile.h"
#include "Dian.h"

#include "UIManager.h"
#include "UI_Alert_Quest.h"

#include "ContentsEvent.h"

#include "FadeObject.h"


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

void Dian::StateSetting()
{
	CreateStateParameter NormalState;
	NormalState.Stay = std::bind(&Dian::NormalUpdate, this, std::placeholders::_1, std::placeholders::_2);

	State.CreateState(EDIANSTATE::Normal, NormalState);
	State.ChangeState(EDIANSTATE::Normal);
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
	m_Shadow = nullptr;
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void Dian::ConversationSetting()
{
	Topic HelloTopic;
	HelloTopic.EntitySpriteName = HelloTopic.Expression_Dian_Sprite_Name;

	HelloTopic.Data.reserve(64);
	HelloTopic.Data =
	{
		{ L"안녕하세요. 다이엔 상점에 오신걸 환영합니다." , ECONVERSATIONENTITY::NPC , 2},
		{ L"ㅎㅇ" , ECONVERSATIONENTITY::Virgil },
		{ L"반갑습니다니다니다니다니 다니다니 다니다니다니다다니다니다" , ECONVERSATIONENTITY::Virgil },
		{ L"반갑습니다니다니다니다니 다니다니 다니다니다니다다니다니다 다니다니다다니다니다" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"반갑습니다" , ECONVERSATIONENTITY::NPC , 2},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 3},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"반갑습니다" , ECONVERSATIONENTITY::NPC , 2},
		{ L"반갑습니다" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"ㅎㅇ" , ECONVERSATIONENTITY::Virgil }
	};

	HelloTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EDIANTOPICTYPE::Hello, HelloTopic);



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
		{ L"엘리, 이 만들다 만 모자 같은 녀석아." , ECONVERSATIONENTITY::Virgil , 2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"아직도 조제법을 못 구했니?." , ECONVERSATIONENTITY::Virgil , 2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"그, 그게 행정부에 보고를 해야 한다는데요..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"아, 주인 마녀님 이름으로 해도 무관합니다." , ECONVERSATIONENTITY::NPC, 1},
		{ L"여기에 주인 마녀님 이름과 엘리 이름, 그리고 용도와 개수를 적어주시죠." , ECONVERSATIONENTITY::NPC, 1},
		{ L"주, 주인 마녀님 이..이름이요?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"뭐! 엘리 이 터진 털모자 같은 녀석!" , ECONVERSATIONENTITY::Virgil ,2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"내 이름을 네 불지옥지렁이 같은 글씨체로 쓰겠다는 거냐!" , ECONVERSATIONENTITY::Virgil, 2,FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan },
		{ L"주인 마녀님 성격이 화통하시군요." , ECONVERSATIONENTITY::NPC, 2},
		{ L"정 그러시면 다른 보증인의 이름을 적으셔도 괜찮습니다." , ECONVERSATIONENTITY::NPC, 1},
		{ L"아리아..그리고 앨리. 1개. 마을 파티용..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"아리아..그리고 앨리. 1개. 마을 파티용..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"확인했습니다. 마녀 카탈로그에 등록해 놓겠습니다." , ECONVERSATIONENTITY::NPC, 0},
		{ L"다이엔이었습니다. 오늘도 이용해주셔서 감사합니다." , ECONVERSATIONENTITY::NPC, 1},
	};

	FireCrackerTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCracker, FireCrackerTopic);

	NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCracker, [&]()
		{
			NPCConversation.StartConversation(EDIANTOPICTYPE::FireCrackerAfter);
		});


	Topic FireCrackerAfterTopic;

	FireCrackerAfterTopic.Data.reserve(64);
	FireCrackerAfterTopic.Data =
	{
		{ L"휴...이럴 때마다 심장이 쿵쾅거려." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"발연기좀 그만해. 들키겠어.  " , ECONVERSATIONENTITY::Virgil , 1, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"어쩔 수 없잖아." , ECONVERSATIONENTITY::Ellie, 2 },
		{ L"일단 당장 생각나는 게 엄마 이름이라서 적었는데...괜찮겠지?." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"목적은 달성했으니 폭죽 물약을 만들러 가자고." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"걱정된다. 정말." , ECONVERSATIONENTITY::Virgil , 1, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
	};

	FireCrackerAfterTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCrackerAfter, FireCrackerAfterTopic);


	NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCrackerAfter, [&]()
		{
			std::weak_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
			if (true == CurLevel.expired())
			{
				MsgBoxAssert("포인터가 존재하지 않습니다.");
				return;
			}

			std::shared_ptr<FadeObject> FadeOutObject = CurLevel.lock().get()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
			FadeOutObject->CallFadeOut("EndLevel");
			
			const std::shared_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest(EQUESTTYPE::Dian_Cracker);
		});
}


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
	DianRenderer->Transform.SetLocalPosition({0.0f, RendererYCorrection });
	DianRenderer->CreateAnimation("Idle", "Dian_idle.png", 0.2f, 4, 7, true);
	DianRenderer->AutoSpriteSizeOn();
	DianRenderer->ChangeAnimation("Idle");
	

	const float ShadowDepth = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>(RendererOrder);
	m_Shadow->Transform.SetLocalPosition({ 0.0f, RendererYCorrection, ShadowDepth });
	m_Shadow->SetSprite("Dian_idle.png", 0);
}

void Dian::NormalUpdate(float _DeltaTime, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		NPCEntity::InteractWithEllie(EDIANTOPICTYPE::FireCracker);
	}
}