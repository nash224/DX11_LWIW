#include "PreCompile.h"
#include "Dian.h"

#include "UIManager.h"
#include "UI_Alert_Quest.h"
#include "UI_Frame.h"

#include "ContentsEvent.h"


Dian::Dian()
{
}

Dian::~Dian()
{
}


void Dian::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 90.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
	InteractiveActor::SetGearName("��ȭ�ϱ�");

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

	UIFrame = nullptr;
}

void Dian::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Dian::Init()
{
	ApplyDepth();
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


	const float ShadowDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow);

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
		if (true == CheckWitchCatalogueEvent())
		{
			return;
		}

		if (true == CheckPotionVerificationEvent())
		{
			return;
		}

		if (true == CheckDian_CrackerEvent())
		{
			return;
		}

		NPCEntity::ConverseWithEllie(EDIANTOPICTYPE::Natural);
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
			{ L"���� ����� ��ǥ����." , ECONVERSATIONENTITY::NPC , 0},
		};

		NaturalTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::Natural, NaturalTopic);
	}



	{
		Topic WitchCatalogueTopic;
		WitchCatalogueTopic.EntitySpriteName = WitchCatalogueTopic.Expression_Dian_Sprite_Name;

		WitchCatalogueTopic.Data.reserve(64);
		WitchCatalogueTopic.Data =
		{
			{ L"�ȳ��ϼ���! ���� �ΰ�, ���� ���� ��ǰ�� �帮�� ���� īŻ�α� �Դϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"�ູ�� �帮�� ���̿� �׸������Դϴ�. �ݰ�����!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"��, �ȳ��ϼ���. ���� ���� ��������." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"��, �ݰ����ϴ� ����!" , ECONVERSATIONENTITY::NPC , 0},
			{ L"���� ���� ���͵���� �ϴ� ����... ó�� ����Ͻô±���!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"���� īŻ�α׸� �� ���� ��̴ٴ� �����ϼ̰ڳ׿�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"��, �¾ƿ�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"���� �����ϸ� ������ �帳�ϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"��, �����̿�? ������?" , ECONVERSATIONENTITY::Ellie , 8},
			{ L"�����ϰ� �̿��� �� �ִ� ���� ���ڷ��Դϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"���� ���ڷ�! ����!" , ECONVERSATIONENTITY::Ellie , 8},
			{ L"����� ���⿡ ���� ���ֽø� �˴ϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"��, ��ø���..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, �ƽ��ϴ�! ���ݺ��� ���� ���ڷ�� ���� īŻ�α׸� �̿��Ͻ� �� �ֽ��ϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"���� ��ħ�� ���� īŻ�α� ������, ���⼱ ����, ã�ƿ��� �˴ϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"Ȥ�� ���� �����Ű���?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"�ƴ�, ���� �����." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, �׷� �ʿ��� �� �����ø� �������� ���� �ɾ��ּ���." , ECONVERSATIONENTITY::NPC , 0},
			{ L"����..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, �����ϼ���." , ECONVERSATIONENTITY::NPC , 0},
			{ L"����ǰ��..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, ���� �ٷ� �帮�ڽ��ϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"��, �����մϴ�!" , ECONVERSATIONENTITY::Ellie , 5},
			{ L"���� �� ���� ���ڷ簡!" , ECONVERSATIONENTITY::Ellie , 8},
			{ L"�ູ�� �Ϸ� �Ǽ���. ���� īŻ�α��� ���̿� �׸����忴���ϴ�." , ECONVERSATIONENTITY::NPC , 1},
		};

		WitchCatalogueTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::WitchCatalogue, WitchCatalogueTopic);


		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::WitchCatalogue, 22, [&]()
			{
				if (nullptr != UI_Inventory::MainInventory)
				{
					UI_Inventory::MainInventory->PushItem("Item_Etc_12");
					UI_Inventory::MainInventory->UnlockSlot();
				}

				ContentsEvent::HasWitchBroom = true;
			});
		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::WitchCatalogue, 23, [&]()
			{
				UIFrame = GetLevel()->CreateActor<UI_Frame>(EUPDATEORDER::UIComponent);
				UIFrame->Init(EFRAMETYPE::BroomStick);
			});
		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::WitchCatalogue, 24, [&]()
			{
				if (nullptr != UIFrame)
				{
					UIFrame->Death();
					UIFrame = nullptr;
				}
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::WitchCatalogue, [&]()
			{
				if (nullptr != UI_Inventory::MainInventory)
				{
					if (false == UI_Inventory::MainInventory->IsItem("Item_Etc_12"))
					{
						UI_Inventory::MainInventory->PushItem("Item_Etc_12");
						UI_Inventory::MainInventory->UnlockSlot();
						ContentsEvent::HasWitchBroom = true;
					}
				}

				if (nullptr != UIFrame)
				{
					UIFrame->Death();
					UIFrame = nullptr;
				}

				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_Catalogue");
				if (true == Quest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestComplete();
			});
	}


	{
		Topic PotionVerificationTopic;
		PotionVerificationTopic.EntitySpriteName = PotionVerificationTopic.Expression_Dian_Sprite_Name;

		PotionVerificationTopic.Data.reserve(64);
		PotionVerificationTopic.Data =
		{
			{ L"�ȳ��ϼ���, ���̿�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"���̿�?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"������..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"���̿�!!!" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"�ȳ��ϼ���! ���� �ΰ�, ���� ���� ��ǰ�� �帮�� ���� īŻ�α��Դϴ�!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"�ູ�� �鸮�� ���̿�...��, ����������. �ݰ����ϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"�˼��մϴ�, ���δ��� ���� ����� �����׿�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"���� ���̶� �ֳ���?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��...�������� �� ���� ���� �������� �̷� ������ ����� �ɷ���..." , ECONVERSATIONENTITY::NPC , 4},
			{ L"������? ���� ���� �� �������� ���ݾƿ�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��. ���� �����ο��� ���� ���� ���񽺸� �ϴµ���.." , ECONVERSATIONENTITY::NPC , 0},
			{ L"�׷��� �ֱٿ� �ҷ� ���� �Ű� �뷮���� ���ͼ� ������." , ECONVERSATIONENTITY::NPC , 0},
			{ L"���� ǰ���� ���� īŻ�α��� �ŷ�, ���� īŻ�α��� �ŷڴ� �� �������� �ŷ�!" , ECONVERSATIONENTITY::NPC , 0},
			{ L"�׶����� �����ο��� �� īŻ�α� �Ǹſ��鿡�� �ǽɰ��� ���� �׽�Ʈ�� �϶� ������ �����Խ��ϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"������ ���� ���� ����� ������ ������ �ش� ������ ������ �־..." , ECONVERSATIONENTITY::NPC , 0},
			{ L"������ �˴ٽ��� ���� ǰ���� ������ �ڽŰ� �����⵵ �ϴϱ��." , ECONVERSATIONENTITY::NPC , 0},
			{ L"�׽�Ʈ �������� ���� Ǯ ���� ������ �ʿ��� �� �����ϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"�����ٸ� ������ ������ ���� �� �������?" , ECONVERSATIONENTITY::NPC , 0},
			{ L"�����̶�⿣ ���������...���ڸ�ä�� �غ��߽��ϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"���ڸ�ä!!" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"���ƿ�, ���� ����Կ�!" , ECONVERSATIONENTITY::Ellie , 5},
			{ L"������, ����. �׷� ��Ź�帱�Կ�" , ECONVERSATIONENTITY::NPC , 1},
		};

		PotionVerificationTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::PotionVerification, PotionVerificationTopic);

		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::PotionVerification, 22, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
				if (true == Quest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestAccept();
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::PotionVerification, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
				if (true == Quest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestAccept();
			});
	}


	{
		Topic DragonFlyTopic;
		DragonFlyTopic.EntitySpriteName = DragonFlyTopic.Expression_Dian_Sprite_Name;

		DragonFlyTopic.Data.reserve(64);
		DragonFlyTopic.Data =
		{
			{ L"�ȳ��ϼ���, ���� Ǯ ���� ������ �����Ծ��." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"������, ����. ���п� �׽�Ʈ�� �� �� �ְ� �ƾ��!" , ECONVERSATIONENTITY::NPC , 1},
			{ L"���� �������� ����� ���ڸ�ä�Դϴ�." , ECONVERSATIONENTITY::NPC , 0},
			{ L"���õ� �̿����ּż� �����մϴ�." , ECONVERSATIONENTITY::NPC, 1},
		};

		DragonFlyTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::DragonFly, DragonFlyTopic);

		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::DragonFly, 2, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
				if (true == Quest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestComplete();
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::DragonFly, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("Dian_BadWeedPotion");
				if (true == Quest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				Quest.lock()->QuestComplete();
			});
	}

	{
		Topic FireCrackerTopic;
		FireCrackerTopic.EntitySpriteName = FireCrackerTopic.Expression_Dian_Sprite_Name;

		FireCrackerTopic.Data.reserve(64);
		FireCrackerTopic.Data =
		{
			{ L"���̿�, īŻ�α׿� ���׹��� ������ �־��?" , ECONVERSATIONENTITY::Ellie, 1 },
			{ L"���� �����̶�. ���� �� ������ �;��� ��������.  " , ECONVERSATIONENTITY::NPC , 1},
			{ L"���̿�����?" , ECONVERSATIONENTITY::Ellie, 1 },
			{ L"�׷���. �������� ���̶���Ʈ�ݾƿ�." , ECONVERSATIONENTITY::NPC, 1 },
			{ L"����. ���� ������ �� �Ҳɳ��̰� ���� ���Ҿ��." , ECONVERSATIONENTITY::Ellie , 5},
			{ L"�̹��� ���� ���� ���� �ִµ� �������� ���� �� �������?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��...�̹����� ���� �׽�Ʈ�� �����ֽø� �ǰ� �������� īŻ�α׿� ����ص帮�°� ����� ������" , ECONVERSATIONENTITY::NPC , 4},
			{ L"������ �˴ٽ��� ���� �б� ���� �߿��� ���� ���� ������ �����Ǿ� �ֽ��ϴ�." , ECONVERSATIONENTITY::NPC, 0},
			{ L"���� ���ε�����?" , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��Ȯ���� ������ �ֽ��ϴ�." , ECONVERSATIONENTITY::NPC, 0},
			{ L"������ ���� ������ ���� ������ �°� �����̰� �����ų� ���� �ҿ� ź ��ʰ� ���Ƽ�..." , ECONVERSATIONENTITY::NPC, 0},
			{ L"� �뵵��, �� �� ������� ���� �����ο� ���� �ؾ� �մϴ�." , ECONVERSATIONENTITY::NPC, 0},
			{ L"��, ������..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"���� �������� �� �� ������ ���� ��Ű���?" , ECONVERSATIONENTITY::NPC, 0},
			{ L"��, �ƴϿ�..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"�� �׷��ø� �ٸ� �������� �̸��� �����ŵ� �������ϴ�." , ECONVERSATIONENTITY::NPC, 1},
			{ L"�Ƹ���..�׸��� �ٸ�. 1��. ���� ����..." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"��, Ȯ���߽��ϴ�." , ECONVERSATIONENTITY::NPC, 1},
			{ L"�׸��� �׽�Ʈ �������� ���� ���� ������ �غ����ֽø� �˴ϴ�." , ECONVERSATIONENTITY::NPC, 0},
			{ L"���̿��̾����ϴ�. ���õ� �̿����ּż� �����մϴ�." , ECONVERSATIONENTITY::NPC, 1},
		};

		FireCrackerTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCracker, FireCrackerTopic);

		NPCConversation.SetConversationEvent(EDIANTOPICTYPE::FireCracker, 19, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
				if (true == CrackerQuest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				CrackerQuest.lock()->QuestAccept();
			});

		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCracker, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
				if (true == CrackerQuest.expired())
				{
					MsgBoxAssert("���� �������� ���� ����Ʈ�Դϴ�.");
					return;
				}

				CrackerQuest.lock()->QuestAccept();

				NPCConversation.StartConversation(EDIANTOPICTYPE::FireCrackerAfter);
			});
	}

	{
		Topic FireCrackerAfterTopic;

		FireCrackerAfterTopic.Data.reserve(64);
		FireCrackerAfterTopic.Data =
		{
			{ L"��...�̷� ������ ������ ����ŷ�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"�ϴ� ���� �������� �� ���� �̸��̶� �����µ�...��������?." , ECONVERSATIONENTITY::Ellie, 5 },
			{ L"�켱 ������ �޼������� ���� ���� ������ ���鷯 ���ڰ�." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"�����ȴ�. ����." , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		};

		FireCrackerAfterTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCrackerAfter, FireCrackerAfterTopic);
	}

	{
		Topic FireCrackerRecipeTopic;
		FireCrackerRecipeTopic.EntitySpriteName = FireCrackerRecipeTopic.Expression_Dian_Sprite_Name;

		FireCrackerRecipeTopic.Data.reserve(64);
		FireCrackerRecipeTopic.Data =
		{
			{ L"�ȳ��ϼ���, ���� ���� ������ �����Ծ��." , ECONVERSATIONENTITY::Ellie , 1},
			{ L"�̹����� �׽�Ʈ�� �����ּż� ������, ����." , ECONVERSATIONENTITY::NPC , 1},
			{ L"���� �������� ���� �������Դϴ�." , ECONVERSATIONENTITY::NPC , 1},
			{ L"���õ� �̿����ּż� �����մϴ�." , ECONVERSATIONENTITY::NPC, 0},
		};
		FireCrackerRecipeTopic.Data.shrink_to_fit();
		NPCConversation.CreateTopic(EDIANTOPICTYPE::FireCrackerRecipe, FireCrackerRecipeTopic);


		NPCConversation.SetConversationEndEvent(EDIANTOPICTYPE::FireCrackerRecipe, [&]()
			{
				std::weak_ptr<ContentsEvent::QuestUnitBase> CrackerQuest = ContentsEvent::FindQuest("Dian_Cracker");
				if (true == CrackerQuest.expired())
				{
					MsgBoxAssert("�������� �ʴ� ����Ʈ�Դϴ�.");
					return;
				}

				CrackerQuest.lock()->QuestComplete();
			});
	}
}