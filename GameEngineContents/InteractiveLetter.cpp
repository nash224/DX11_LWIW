#include "PreCompile.h"
#include "InteractiveLetter.h"

#include "PlayLevel.h"

#include "ContentsEvent.h"
#include "UIManager.h"
#include "AlertManager.h"

#include "DustFx.h"
#include "UI_Frame.h"


InteractiveLetter::InteractiveLetter()
{
}

InteractiveLetter::~InteractiveLetter()
{
}


void InteractiveLetter::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, float4(100.0f), float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gear, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Nothing);
}

void InteractiveLetter::Update(float _Delta)
{
	StaticEntity::Update(_Delta);

	LetterConversation.UpdateConversation(_Delta);
	State.Update(_Delta);
}

void InteractiveLetter::Release()
{
	StaticEntity::Release();

	CutsceneFrame = nullptr;
}

void InteractiveLetter::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void InteractiveLetter::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void InteractiveLetter::Init()
{
	ApplyDepth();
	RendererSetting();
	ConversationSetting();
	StateSetting();
}

void InteractiveLetter::RendererSetting()
{
	static constexpr const int RenderOrder = 0;

	InteractiveActor::BodyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder);
	InteractiveActor::BodyRenderer->SetSprite("Mail.png");
	InteractiveActor::BodyRenderer->Transform.AddLocalPosition(float4(0.0f, 0.0f, -5.0f));
}


void InteractiveLetter::ConversationSetting()
{
	{
		Topic StartTrainingTopic;

		StartTrainingTopic.Data.reserve(64);
		StartTrainingTopic.Data =
		{
			{ L"편지다!" , ECONVERSATIONENTITY::Ellie, 1},
			{ L"누가 이렇게 친절한 사람이 있지." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan} },
			{ L"어디보자, 마녀 수습에 대한 내용같아." , ECONVERSATIONENTITY::Ellie, 11},
			{ L"정식으로 마녀가 되는 조건은 폭죽 물약을 제조하는 것입니다." , ECONVERSATIONENTITY::NPC },
			{ L"마녀의 작업실에서 폭죽 물약을 제조하면 수습기간이 종료됩니다." , ECONVERSATIONENTITY::NPC },
			{ L"(스토리는 원작과 다릅니다.)" , ECONVERSATIONENTITY::NPC, 3, ConversationFont::Color_RED },
			{ L"폭죽 물약을 만들면 정식 마녀가 될 수 있대!" , ECONVERSATIONENTITY::Ellie, 8},
			{ L"마녀의 집을 한 번 청소하는 건 어때." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan} },
			{ L"수습기간은 그곳에서 지내야 할 것 같은데." , ECONVERSATIONENTITY::Virgil, 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan} },
			{ L"그래!" , ECONVERSATIONENTITY::Ellie, 8},
		};

		StartTrainingTopic.Data.shrink_to_fit();
		LetterConversation.CreateTopic(ELETTERTOPICTYPE::StartTraining, StartTrainingTopic);

		LetterConversation.SetConversationEvent(ELETTERTOPICTYPE::StartTraining, 3, [&]()
			{
				CutsceneFrame = GetLevel()->CreateActor<UI_Frame>(EUPDATEORDER::UIComponent);
				CutsceneFrame->Init(EFRAMETYPE::Mail);
			});

		LetterConversation.SetConversationEvent(ELETTERTOPICTYPE::StartTraining, 6, [&]()
			{
				if (nullptr != CutsceneFrame)
				{
					CutsceneFrame->Death();
					CutsceneFrame = nullptr;
				}
			});

		LetterConversation.SetConversationEndEvent(ELETTERTOPICTYPE::StartTraining, [&]()
			{
				if (nullptr != CutsceneFrame)
				{
					CutsceneFrame->Death();
					CutsceneFrame = nullptr;
				}


				std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("StartTraining");
				if (true == Quest.expired())
				{
					MsgBoxAssert("생성되지 않은 퀘스트입니다.");
					return;
				}

				Quest.lock()->QuestAccept();


				if (nullptr != UIManager::MainUIManager)
				{
					UIManager::MainUIManager->UseUIComponent();
				}


				State.ChangeState(ELETTERSTATE::Disappear);
			});
	}
}


void InteractiveLetter::StateSetting()
{
	CreateStateParameter IdleState;
	IdleState.Stay = std::bind(&InteractiveLetter::UpdateIdle, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ELETTERSTATE::Idle, IdleState);

	CreateStateParameter ReadState;
	ReadState.Start = std::bind(&InteractiveLetter::StartRead, this, std::placeholders::_1);
	State.CreateState(ELETTERSTATE::Read, ReadState);

	CreateStateParameter DisappearState;
	DisappearState.Start = std::bind(&InteractiveLetter::StartDisappear, this, std::placeholders::_1);
	State.CreateState(ELETTERSTATE::Disappear, DisappearState);

	State.ChangeState(ELETTERSTATE::Idle);
}


void InteractiveLetter::StartRead(GameEngineState* _Parent)
{
	LetterConversation.StartConversation(ELETTERTOPICTYPE::StartTraining);
}

void InteractiveLetter::StartDisappear(GameEngineState* _Parent)
{
	std::shared_ptr<DustFx> Dust = GetLevel()->CreateActor<DustFx>(EUPDATEORDER::Objects);
	Dust->Init(Transform.GetLocalPosition());

	if (nullptr != UIManager::MainUIManager)
	{
		UIManager::MainUIManager->DoneUIComponent();
	}

	Death();
}


void InteractiveLetter::UpdateIdle(float _DeltaTime, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		State.ChangeState(ELETTERSTATE::Read);
	}
}
