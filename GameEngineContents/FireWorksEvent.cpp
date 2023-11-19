#include "PreCompile.h"
#include "FireWorksEvent.h"

#include "BGMManager.h"

#include "Ellie.h"
#include "FadeObject.h"
#include "FireWorks.h"
#include "ContentsEvent.h"
#include "AlertManager.h"

#include "UIManager.h"

FireWorksEvent::FireWorksEvent() 
{
}

FireWorksEvent::~FireWorksEvent() 
{
}


void FireWorksEvent::Update(float _Delta)
{
	State.Update(_Delta);
	EventConversation.UpdateConversation(_Delta);
}
 
void FireWorksEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void FireWorksEvent::Init()
{
	PotionSetting();
	ConversationSetting();
	StateSetting();
}

void FireWorksEvent::PotionSetting()
{
	CrackerPotion = GetLevel()->CreateActor<FireWorks>(EUPDATEORDER::Objects);
	CrackerPotion->Transform.SetLocalPosition(Transform.GetLocalPosition());
	CrackerPotion->Init();
}

void FireWorksEvent::ConversationSetting()
{
	Topic CloserTopic;

	CloserTopic.Data.reserve(64);
	CloserTopic.Data =
	{
		{ L"이걸로 수습은 끝이네." , ECONVERSATIONENTITY::Ellie, 5 },
		{ L"별 문제 없이 끝나서 다행이야." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"이제 폭죽을 쏘아올리고 어서 끝내자고." , ECONVERSATIONENTITY::Virgil , 1, ConversationFont::VigilDefaultFont },
		{ L"간다! 회심의 폭죽 물약!" , ECONVERSATIONENTITY::Ellie, 8 },
	};

	CloserTopic.Data.shrink_to_fit();
	EventConversation.CreateTopic(EFIREWORKSEVENTTOPIC::Ready, CloserTopic);

	EventConversation.SetConversationEndEvent(EFIREWORKSEVENTTOPIC::Ready, [&]()
		{
			if (nullptr != UIManager::MainUIManager)
			{
				UIManager::MainUIManager->UseUIComponent();
			}

			State.ChangeState(EFIREWORKSSTATE::FireWorks);
		});


	Topic LastTopic;

	LastTopic.Data.reserve(64);
	LastTopic.Data =
	{
		{ L"준비한 부분은 여기까지입니다." , ECONVERSATIONENTITY::Ellie, 6 },
		{ L"지금까지 봐주셔서 감사합니다!" , ECONVERSATIONENTITY::Ellie, 8 },
	};

	CloserTopic.Data.shrink_to_fit();
	EventConversation.CreateTopic(EFIREWORKSEVENTTOPIC::Last, LastTopic);

	EventConversation.SetConversationEndEvent(EFIREWORKSEVENTTOPIC::Last, [&]()
		{
			if (nullptr != UIManager::MainUIManager)
			{
				UIManager::MainUIManager->UseUIComponent();
			}

			State.ChangeState(EFIREWORKSSTATE::EndTraining);
		});
}

void FireWorksEvent::StateSetting()
{
	CreateStateParameter FadeInState;
	FadeInState.Start = std::bind(&FireWorksEvent::StartFadeIn, this, std::placeholders::_1);
	FadeInState.Stay = std::bind(&FireWorksEvent::UpdateFadeIn, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::FadeIn, FadeInState);

	CreateStateParameter ReadyConversationState;
	ReadyConversationState.Start = std::bind(&FireWorksEvent::StartReadyConversation, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::ReadyConversation, ReadyConversationState);

	CreateStateParameter FireWorksState;
	FireWorksState.Start = std::bind(&FireWorksEvent::StartFireWorks, this, std::placeholders::_1);
	FireWorksState.Stay = std::bind(&FireWorksEvent::UpdateFireWorks, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::FireWorks, FireWorksState);

	CreateStateParameter EndTrainingState;
	EndTrainingState.Start = std::bind(&FireWorksEvent::StartEndTraining, this, std::placeholders::_1);
	EndTrainingState.Stay = std::bind(&FireWorksEvent::UpdateEndTraining, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::EndTraining, EndTrainingState);

	CreateStateParameter LastConversationState;
	LastConversationState.Start = std::bind(&FireWorksEvent::StartLastConversation, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::LastConversation, LastConversationState);

	CreateStateParameter FadeOutState;
	FadeOutState.Start = std::bind(&FireWorksEvent::StartFadeOut, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::FadeOut, FadeOutState);
}

void FireWorksEvent::StartFadeIn(GameEngineState* _Parent)
{
	std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade.lock()->CallFadeIn(LastFadeTime);
	
	EllieSetting();

	if (nullptr != UIManager::MainUIManager)
	{
		UIManager::MainUIManager->UseUIComponent();
	}

	if (nullptr != ContentsLevel::MainPlaySound)
	{
		ContentsLevel::MainPlaySound->AbsoluteNoneBGM();
	}
}

void FireWorksEvent::UpdateFadeIn(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > LastFadeTime + 2.0f)
	{
		State.ChangeState(EFIREWORKSSTATE::ReadyConversation);
		return;
	}
}


void FireWorksEvent::StartReadyConversation(GameEngineState* _Parent)
{
	EventConversation.StartConversation(EFIREWORKSEVENTTOPIC::Ready);
}


void FireWorksEvent::StartFireWorks(GameEngineState* _Parent)
{
	if (nullptr == CrackerPotion)
	{
		MsgBoxAssert("폭죽 포션이 없인 이벤트를 수행할 수 없습니다.");
		return;
	}

	CrackerPotion->Fire();

	StateTime = 0.0f;
}

void FireWorksEvent::UpdateFireWorks(float _Delta, GameEngineState* _Parent)
{
	if (nullptr == CrackerPotion)
	{
		MsgBoxAssert("폭죽 포션이 없인 이벤트를 수행할 수 없습니다.");
		return;
	}

	if (true == CrackerPotion->IsEndFireWork())
	{
		static constexpr float WaitTime = 1.0f;
		StateTime += _Delta;
		if (StateTime > WaitTime)
		{
			State.ChangeState(EFIREWORKSSTATE::LastConversation);
			return;
		}
	}
}


void FireWorksEvent::StartLastConversation(GameEngineState* _Parent)
{
	EventConversation.StartConversation(EFIREWORKSEVENTTOPIC::Last);
}


void FireWorksEvent::StartEndTraining(GameEngineState* _Parent)
{
	CheckEndtrainingEvent();
}

void FireWorksEvent::UpdateEndTraining(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != PlayLevel::s_AlertManager)
	{
		if (true == PlayLevel::s_AlertManager->IsAlertEnd())
		{
			State.ChangeState(EFIREWORKSSTATE::FadeOut);
		}
	}
}


void FireWorksEvent::StartFadeOut(GameEngineState* _Parent)
{
	std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (true == Fade.expired())
	{
		MsgBoxAssert("포인터가 존재하지 않습니다.");
		return;
	}

	Fade.lock()->CallFadeOut("EndingLevel", LastFadeTime);
}


void FireWorksEvent::EllieSetting()
{
	const float4& CurPos = Transform.GetLocalPosition();
	const float4& ElliePos = CurPos + float4(-50.0f, 0.0f);

	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("앨리가 존재하지 않습니다.");
		return;
	}
	
	Ellie::MainEllie->Transform.SetLocalPosition(ElliePos);
	Ellie::MainEllie->ApplyDepth();
}

void FireWorksEvent::CheckEndtrainingEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("StartTraining");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->CheckPrerequisiteQuest())
	{
		Quest.lock()->QuestComplete();
	}
}