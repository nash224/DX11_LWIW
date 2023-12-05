#include "PreCompile.h"
#include "CrowEvent.h"

#include "PlayLevel.h"
#include "UIManager.h"

#include "OutLineEffect.h"



CrowEvent::CrowEvent() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_CrowCrying_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\Crow");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
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
		PlayLevel::GetCurLevel()->GetUIManagerPtr()->UseUIComponent();
	}

	State.Update(_Delta);
	CrowConveration.UpdateConversation(_Delta);
}

void CrowEvent::Release()
{
	CrowRenderer = nullptr;
	CrowConveration.Release();

	const std::shared_ptr<OutLineEffect>& OutLine = PlayLevel::GetCurLevel()->GetOutLinePtr();
	if (nullptr != OutLine)
	{
		OutLine->DefaultSetting();
	}

	if (nullptr != GameEngineSprite::Find("Crow.png"))
	{
		GameEngineSprite::Release("Crow.png");
	}
}

void CrowEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void CrowEvent::Init()
{
	if (nullptr == GameEngineSprite::Find("Crow.png"))
	{
		GameEngineSprite::CreateCut("Crow.png", 4, 4);
	}

	Transform.SetLocalPosition(float4(435.0f, -250.0f, DepthFunction::CalculateFixDepth(ERENDERDEPTH::FX)));

	const std::shared_ptr<OutLineEffect>& OutLine = PlayLevel::GetCurLevel()->GetOutLinePtr();
	if (nullptr != OutLine)
	{
		OutLine->SetOutLineColor(float4(0.85f, 0.67f, 0.89f, 0.9f));
		OutLine->SetOutLineThickness(2.4f);
	}

	RendererSetting();
	StateSetting();
	ConversationSetting();
}

void CrowEvent::RendererSetting()
{
	CrowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	CrowRenderer->AutoSpriteSizeOn();
	CrowRenderer->CreateAnimation("Idle", "Crow.png", 5.0f,1, 1, false);
	CrowRenderer->CreateAnimation("Caw", "Crow.png", Caw_Animation_Inter, 2, 4, false);
	CrowRenderer->FindAnimation("Caw")->Inter[2] = 0.3f;

	CrowRenderer->CreateAnimation("CawReverse", "Crow.png", Caw_Animation_Inter, 4, 2, false);
	CrowRenderer->CreateAnimation("Disappear", "Crow.png", Disappear_Animation_Inter, 5, 15, false);
	CrowRenderer->FindAnimation("Disappear")->Inter[10] = 1.0f;
	CrowRenderer->RenderBaseInfoValue.Target1 = 1;



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
			SFXFunction::PlaySFX("SFX_CrowDisappear_01.wav");
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
	const float Caw_WaitTime = 2.0f;
	if (_Parent->GetStateTime() > Caw_WaitTime)
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
			MsgBoxAssert("렌더러가 존재하지 않습니다.");
			return;
		}

		CrowRenderer->ChangeAnimation("Caw", true);

		SFXFunction::PlaySFX("SFX_CrowCrying_01.wav");
	}
}

void CrowEvent::UpdateDisappear(float _DeltaTime, GameEngineState* _Parent)
{

}


void CrowEvent::ConversationSetting()
{
	Topic CrowTopic;
	CrowTopic.EntitySpriteName = CrowTopic.Expression_Crow_Sprite_Name;
	CrowTopic.Npc_DefaultIndex = 0;

	CrowTopic.Data.reserve(64);
	CrowTopic.Data =
	{
		{ L"까악" , ECONVERSATIONENTITY::NPC , 1},
		{ L"까마귀?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"마녀! 까악" , ECONVERSATIONENTITY::NPC , 1},
		{ L"말을 했어?" , ECONVERSATIONENTITY::Ellie, 9 },
		{ L"마녀 까마귀잖아." , ECONVERSATIONENTITY::Virgil , 4, ConversationFont::VigilDefaultFont},
		{ L"아, 마녀 까마귀였구나." , ECONVERSATIONENTITY::Ellie , 3},
		{ L"마녀가 돌아왔다! 마녀가 돌아왔다!" , ECONVERSATIONENTITY::NPC , 1},
		{ L"나는 여기 처음왔는데." , ECONVERSATIONENTITY::Ellie , 1},
		{ L"마녀가 돌아왔다!" , ECONVERSATIONENTITY::NPC , 1, ConversationFont::Color_RED},
		{ L"말이 그렇게 잘 통하진 않네." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"서비스 제공! 까악 서비스 제공! 마녀 카탈로그." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"마녀 카탈로그!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"꼭 한 번 써보고 싶었어." , ECONVERSATIONENTITY::Ellie, 6 },
		{ L"지금 등록하면 선물을 드립니다. 까악" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"마녀 카탈로그를 이용하세요. 마녀 카탈로그를 이용하세요." , ECONVERSATIONENTITY::NPC, 1 },
		{ L"선물도 준대! 지금만 준대!" , ECONVERSATIONENTITY::Ellie, 8 },
		{ L"까악 선물" , ECONVERSATIONENTITY::NPC, 1, ConversationFont::Color_RED},
		{ L"다목적 접착제? 주방용품? 포크 숟가락?" , ECONVERSATIONENTITY::Virgil, 1 , {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"하여튼 마녀 카탈로그는 필요해." , ECONVERSATIONENTITY::Ellie, 2},
		{ L"잠깐 있을거라도 좋긴하지." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"재료나 물약 제조법 같은 것도 살 수 있어." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
		{ L"좋아 일단 등록하자." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"감사합니다. 까악 감사합니다. 직원 방문! 직원 방문!" , ECONVERSATIONENTITY::NPC, 1 },
		{ L"까악 직원 방문" , ECONVERSATIONENTITY::NPC, 1 , ConversationFont::Color_RED },
		{ L"언제?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"업무 끝! 업무 끝! 퇴근 시간" , ECONVERSATIONENTITY::NPC, 0 },
		{ L"정시 퇴근" , ECONVERSATIONENTITY::NPC, 1, ConversationFont::Color_RED },
	};

	CrowTopic.Data.shrink_to_fit();
	CrowConveration.CreateTopic(ECROWTOPIC::Crow, CrowTopic);

	CrowConveration.SetConversationEndEvent(ECROWTOPIC::Crow, [&]()
		{
			CrowRenderer->ChangeAnimation("Disappear");

			PlayLevel::GetCurLevel()->GetUIManagerPtr()->UseUIComponent();

			State.ChangeState(ECROWSTATE::Disappear);
		});



	Topic DisappearTopic;
	DisappearTopic.Npc_DefaultIndex = 0;
	DisappearTopic.Data.reserve(64);
	DisappearTopic.Data =
	{
		{ L"이렇게 갑자기?" , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"마녀 까마귀는 그렇게 말이 잘 통하는 편은 아니지." , ECONVERSATIONENTITY::Virgil, 1 , ConversationFont::VigilDefaultFont},
		{ L"음, 그럼 일단은 계속 주변을 탐색 해볼까?" , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"마녀 카탈로그는 언제 올지 모르니까 말야" , ECONVERSATIONENTITY::Virgil, 5, ConversationFont::VigilDefaultFont },
		{ L"우선 그렇게 하자." , ECONVERSATIONENTITY::Virgil, 5, ConversationFont::VigilDefaultFont },
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