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
		{ L"�ȳ��ϼ���. ���̿� ������ ���Ű� ȯ���մϴ�." , ECONVERSATIONENTITY::NPC , 2},
		{ L"����" , ECONVERSATIONENTITY::Virgil },
		{ L"�ݰ����ϴٴϴٴϴٴϴٴ� �ٴϴٴ� �ٴϴٴϴٴϴٴٴϴٴϴ�" , ECONVERSATIONENTITY::Virgil },
		{ L"�ݰ����ϴٴϴٴϴٴϴٴ� �ٴϴٴ� �ٴϴٴϴٴϴٴٴϴٴϴ� �ٴϴٴϴٴٴϴٴϴ�" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::NPC , 2},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 3},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 8},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::NPC , 2},
		{ L"�ݰ����ϴ�" , ECONVERSATIONENTITY::Ellie , 5},
		{ L"����" , ECONVERSATIONENTITY::Virgil }
	};

	HelloTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EDIANTOPICTYPE::Hello, HelloTopic);



	Topic FireCrackerTopic;
	FireCrackerTopic.EntitySpriteName = FireCrackerTopic.Expression_Dian_Sprite_Name;
	FireCrackerTopic.Default_Npc_Sprite_Index = 4;

	FireCrackerTopic.Data.reserve(64);
	FireCrackerTopic.Data =
	{
		{ L"���� �����̶�. ���� �� ������ �;��� ��������.  " , ECONVERSATIONENTITY::NPC , 1},
		{ L"���̿�����?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"�׷���. �������� ���̶���Ʈ�ݾƿ�." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"����. ���� ������ �� �Ҳɳ��̰� ���� ���Ҿ��." , ECONVERSATIONENTITY::Ellie , 5},
		{ L"�̹��� ���� ���� ���� �ִµ� �������� ���� �� �������?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��...�������� īŻ�α׿� ����ص帮�°� ����� ������ " , ECONVERSATIONENTITY::NPC , 4},
		{ L"������ �˴ٽ��� ���� �б� ���� �߿��� ���� ���� ������ �����Ǿ� �ֽ��ϴ�." , ECONVERSATIONENTITY::NPC, 0},
		{ L"���� ���ε�����?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��Ȯ���� ������ �ֽ��ϴ�." , ECONVERSATIONENTITY::NPC, 0},
		{ L"������ ���� ������ ���� ������ �°� �����̰� �����ų� ���� �ҿ� ź ��ʰ� ���Ƽ�..." , ECONVERSATIONENTITY::NPC, 0},
		{ L"� �뵵��, �� �� ������� ���� �����ο� ���� �ؾ� �մϴ�." , ECONVERSATIONENTITY::NPC, 0},
		{ L"��, ������..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"����, �� ����� �� ���� ���� �༮��." , ECONVERSATIONENTITY::Virgil , 2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"������ �������� �� ���ߴ�?." , ECONVERSATIONENTITY::Virgil , 2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"��, �װ� �����ο� ���� �ؾ� �Ѵٴµ���..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��, ���� ����� �̸����� �ص� �����մϴ�." , ECONVERSATIONENTITY::NPC, 1},
		{ L"���⿡ ���� ����� �̸��� ���� �̸�, �׸��� �뵵�� ������ �����ֽ���." , ECONVERSATIONENTITY::NPC, 1},
		{ L"��, ���� ����� ��..�̸��̿�?" , ECONVERSATIONENTITY::Ellie , 1},
		{ L"��! ���� �� ���� �и��� ���� �༮!" , ECONVERSATIONENTITY::Virgil ,2, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"�� �̸��� �� ������������ ���� �۾�ü�� ���ڴٴ� �ų�!" , ECONVERSATIONENTITY::Virgil, 2,FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan },
		{ L"���� ����� ������ ȭ���Ͻñ���." , ECONVERSATIONENTITY::NPC, 2},
		{ L"�� �׷��ø� �ٸ� �������� �̸��� �����ŵ� �������ϴ�." , ECONVERSATIONENTITY::NPC, 1},
		{ L"�Ƹ���..�׸��� �ٸ�. 1��. ���� ��Ƽ��..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"�Ƹ���..�׸��� �ٸ�. 1��. ���� ��Ƽ��..." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"Ȯ���߽��ϴ�. ���� īŻ�α׿� ����� ���ڽ��ϴ�." , ECONVERSATIONENTITY::NPC, 0},
		{ L"���̿��̾����ϴ�. ���õ� �̿����ּż� �����մϴ�." , ECONVERSATIONENTITY::NPC, 1},
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
		{ L"��...�̷� ������ ������ ����ŷ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"�߿����� �׸���. ��Ű�ھ�.  " , ECONVERSATIONENTITY::Virgil , 1, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
		{ L"��¿ �� ���ݾ�." , ECONVERSATIONENTITY::Ellie, 2 },
		{ L"�ϴ� ���� �������� �� ���� �̸��̶� �����µ�...��������?." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"������ �޼������� ���� ������ ���鷯 ���ڰ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"�����ȴ�. ����." , ECONVERSATIONENTITY::Virgil , 1, FireCrackerTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
	};

	FireCrackerAfterTopic.Data.shrink_to_fit();
	NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCrackerAfter, FireCrackerAfterTopic);


	NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCrackerAfter, [&]()
		{
			std::weak_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
			if (true == CurLevel.expired())
			{
				MsgBoxAssert("�����Ͱ� �������� �ʽ��ϴ�.");
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