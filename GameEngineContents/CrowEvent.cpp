#include "PreCompile.h"
#include "CrowEvent.h"

#include "UIManager.h"



CrowEvent::CrowEvent() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_CrowCrying_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Crow");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile pFile : Files)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}
}

CrowEvent::~CrowEvent() 
{
}


void CrowEvent::Update(float _Delta)
{
	static bool EventStart = false;
	if (false == EventStart)
	{
		EventStart = true;
		if (nullptr != UIManager::MainUIManager)
		{
			UIManager::MainUIManager->UseUIComponent();
		}
	}

	State.Update(_Delta);
	CrowConveration.UpdateConversation(_Delta);
}

void CrowEvent::Release()
{
	CrowRenderer = nullptr;


	if (nullptr != GameEngineSprite::Find("Crow.png"))
	{
		GameEngineSprite::Release("Crow.png");
	}
}

void CrowEvent::LevelStart(class GameEngineLevel* _NextLevel)
{

}


void CrowEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void CrowEvent::Init()
{
	if (nullptr == GameEngineSprite::Find("Crow.png"))
	{
		GameEngineSprite::CreateCut("Crow.png", 4, 4);
	}

	const float4 CrowPosition = float4(435.0f, -250.0f, GlobalUtils::CalculateFixDepth(ERENDERDEPTH::FX));
	Transform.SetLocalPosition(CrowPosition);

	RendererSetting();
	StateSetting();
	ConversationSetting();
}

void CrowEvent::RendererSetting()
{
	const std::uint32_t RendererGroup = 0;
	CrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RendererGroup);
	CrowRenderer->AutoSpriteSizeOn();
	CrowRenderer->CreateAnimation("Idle", "Crow.png", 5.0f,1, 1, false);
	CrowRenderer->CreateAnimation("Caw", "Crow.png", Caw_Animation_Inter, 2, 4, false);
	CrowRenderer->FindAnimation("Caw")->Inter[2] = 0.3f;

	CrowRenderer->CreateAnimation("CawReverse", "Crow.png", Caw_Animation_Inter, 4, 2, false);
	CrowRenderer->CreateAnimation("Disappear", "Crow.png", Disappear_Animation_Inter, 5, 15, false);
	CrowRenderer->FindAnimation("Disappear")->Inter[10] = 1.0f;



	CrowRenderer->SetEndEvent("Caw", [&](GameEngineSpriteRenderer* _Parent)
		{
			CrowRenderer->ChangeAnimation("CawReverse");
		});

	CrowRenderer->SetEndEvent("CawReverse", [&](GameEngineSpriteRenderer* _Parent)
		{
			CrowRenderer->ChangeAnimation("Idle");
		});

	CrowRenderer->SetStartEvent("Disappear", [&](GameEngineSpriteRenderer* _Parent)
		{
			GameEngineSoundPlayer CrowDisappear = GameEngineSound::SoundPlay("SFX_CrowDisappear_01.wav");
			CrowDisappear.SetVolume(GlobalValue::GetSFXVolume());
		});

	CrowRenderer->SetEndEvent("Disappear", [&](GameEngineSpriteRenderer* _Parent)
		{
			CrowRenderer->Off();

			CrowConveration.StartConversation(ECROWTOPIC::Disappear);
		});

	CrowRenderer->ChangeAnimation("Idle");
}

void CrowEvent::StateSetting()
{
	CreateStateParameter EventStartState;
	EventStartState.Stay = std::bind(&CrowEvent::UpdateEventStart, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECROWSTATE::EventStart, EventStartState);


	CreateStateParameter IdleState;
	IdleState.Stay = std::bind(&CrowEvent::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECROWSTATE::Idle, IdleState);

	CreateStateParameter DisappearState;
	DisappearState.Stay = std::bind(&CrowEvent::UpdateDisappear, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECROWSTATE::Disappear, DisappearState);

	State.ChangeState(ECROWSTATE::EventStart);
}

void CrowEvent::UpdateEventStart(float _DeltaTime, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > Caw_Wait_Time)
	{
		State.ChangeState(ECROWSTATE::Idle);
		ConverseWithEllie();
		return;
	}
}

void CrowEvent::UpdateIdle(float _DeltaTime, GameEngineState* _Parent)
{
	StateTime += _DeltaTime;
	if (StateTime > Caw_CoolTime)
	{
		StateTime = 0.0f;

		if (nullptr == CrowRenderer)
		{
			MsgBoxAssert("�������� �������� �ʽ��ϴ�.");
			return;
		}

		CrowRenderer->ChangeAnimation("Caw", true);


		GameEngineSoundPlayer Caw = GameEngineSound::SoundPlay("SFX_CrowCrying_01.wav");
		Caw.SetVolume(GlobalValue::GetSFXVolume());
	}
}

void CrowEvent::UpdateDisappear(float _DeltaTime, GameEngineState* _Parent)
{

}


void CrowEvent::ConversationSetting()
{
	Topic CrowTopic;
	CrowTopic.EntitySpriteName = CrowTopic.Expression_Crow_Sprite_Name;
	CrowTopic.Default_Npc_Sprite_Index = 0;

	CrowTopic.Data.reserve(64);
	CrowTopic.Data =
	{
		{ L"���" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"����! ���" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���� �߾�?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"���� ����ݾ�." , ECONVERSATIONENTITY::Virgil , 4, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��, ���� ��Ϳ�����." , ECONVERSATIONENTITY::Ellie , 3},
		{ L"���డ ���ƿԴ�! ���డ ���ƿԴ�!" , ECONVERSATIONENTITY::NPC , 1},
		{ L"���� ���� ó���Դµ�." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"���డ ���ƿԴ�!" , ECONVERSATIONENTITY::NPC , 1, ConversationFont::Color_RED},
		{ L"���� �׷��� �� ������ �ʳ�." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"���� ����! ��� ���� ����! ���� īŻ�α�." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"���� īŻ�α�!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"�� �� �� �Ẹ�� �;���." , ECONVERSATIONENTITY::Ellie, 6 },
		{ L"���� ����ϸ� ������ �帳�ϴ�. ���" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"���� īŻ�α׸� �̿��ϼ���. ���� īŻ�α׸� �̿��ϼ���." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"������ �ش�! ���ݸ� �ش�!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"��� ����" , ECONVERSATIONENTITY::NPC, 1, ConversationFont::Color_RED},
		{ L"�ٸ��� ������? �ֹ��ǰ? ��ũ ������?" , ECONVERSATIONENTITY::Virgil, 1 , {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"�Ͽ�ư ���� īŻ�α״� �ʿ���." , ECONVERSATIONENTITY::Ellie, 2},
		{ L"��� �����Ŷ� ��������." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��ᳪ ���� ������ ���� �͵� �� �� �־�." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"���� �ϴ� �������." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"�����մϴ�. ��� �����մϴ�. ���� �湮! ���� �湮!" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"��� ���� �湮" , ECONVERSATIONENTITY::NPC, 1 , ConversationFont::Color_RED },
		{ L"����?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"���� ��! ���� ��! ��� �ð�" , ECONVERSATIONENTITY::NPC, 0 },
		{ L"���� ���" , ECONVERSATIONENTITY::NPC, 1, ConversationFont::Color_RED },
	};

	CrowTopic.Data.shrink_to_fit();
	CrowConveration.CreateTopic(ECROWTOPIC::Crow, CrowTopic);

	CrowConveration.SetConversationEndEvent(ECROWTOPIC::Crow, [&]()
		{
			CrowRenderer->ChangeAnimation("Disappear");


			if (nullptr == UIManager::MainUIManager)
			{
				MsgBoxAssert("UI�Ŵ����� �������� �ʽ��ϴ�.");
				return;
			}

			UIManager::MainUIManager->UseUIComponent();

			State.ChangeState(ECROWSTATE::Disappear);
		});



	Topic DisappearTopic;
	DisappearTopic.Default_Npc_Sprite_Index = 0;
	DisappearTopic.Data.reserve(64);
	DisappearTopic.Data =
	{
		{ L"�̷��� ���ڱ�?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"���� ��ʹ� �׷��� ���� �� ���ϴ� ���� �ƴ���." , ECONVERSATIONENTITY::Virgil, 1 ,{ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"��, �׷� �ϴ��� ��� �ֺ��� Ž�� �غ���?" , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"���� īŻ�α״� ���� ���� �𸣴ϱ� ����" , ECONVERSATIONENTITY::Virgil, 5,{ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan} },
		{ L"�켱 �׷��� ����." , ECONVERSATIONENTITY::Virgil, 5,{ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan} },
	};

	DisappearTopic.Data.shrink_to_fit();
	CrowConveration.CreateTopic(ECROWTOPIC::Disappear, DisappearTopic);


	CrowConveration.SetConversationEndEvent(ECROWTOPIC::Disappear, [&]()
		{
			Death();
		});
}

void CrowEvent::ConverseWithEllie()
{
	CrowConveration.StartConversation(ECROWTOPIC::Crow);
}