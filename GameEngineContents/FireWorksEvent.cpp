#include "PreCompile.h"
#include "FireWorksEvent.h"

#include "FadeObject.h"

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
		{ L"갑니다! 회심의 폭죽 물약!" , ECONVERSATIONENTITY::Ellie, 8 },
	};

	CloserTopic.Data.shrink_to_fit();
	EventConversation.CreateTopic(EFIREWORKSEVENTTOPIC::Ready, CloserTopic);

	EventConversation.SetConversationEndEvent(EFIREWORKSEVENTTOPIC::Ready, [&]()
		{
			State.ChangeState(EFIREWORKSSTATE::PotionSetting);
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
			State.ChangeState(EFIREWORKSSTATE::FadeOut);
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

	CreateStateParameter PotionSettingState;
	PotionSettingState.Start = std::bind(&FireWorksEvent::StartPotionSetting, this, std::placeholders::_1);
	PotionSettingState.Stay = std::bind(&FireWorksEvent::UpdatePotionSetting, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::PotionSetting, PotionSettingState);

	CreateStateParameter FireState;
	FireState.Start = std::bind(&FireWorksEvent::StartFire, this, std::placeholders::_1);
	FireState.Stay = std::bind(&FireWorksEvent::UpdateFire, this, std::placeholders::_1, std::placeholders::_2);
	FireState.End = std::bind(&FireWorksEvent::EndFire, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::Fire, FireState);

	CreateStateParameter FireWorksState;
	FireWorksState.Stay = std::bind(&FireWorksEvent::UpdateFireWorks, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::FireWorks, FireWorksState);

	CreateStateParameter LastConversationState;
	LastConversationState.Start = std::bind(&FireWorksEvent::StartLastConversation, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::LastConversation, LastConversationState);
}

void FireWorksEvent::StartFadeIn(GameEngineState* _Parent)
{
	std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	if (true == Fade.expired())
	{
		MsgBoxAssert("포인터가 존재하지 않습니다.");
		return;
	}

	Fade.lock()->CallFadeIn(LastFadeTime);
	
	// BgmOff
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


void FireWorksEvent::StartPotionSetting(GameEngineState* _Parent)
{
	// alight
}

void FireWorksEvent::UpdatePotionSetting(float _Delta, GameEngineState* _Parent)
{
	// alightdone

	State.ChangeState(EFIREWORKSSTATE::Fire);
}


void FireWorksEvent::StartFire(GameEngineState* _Parent)
{
	// Camera
	// Effect
	// Line
}

void FireWorksEvent::UpdateFire(float _Delta, GameEngineState* _Parent)
{
	// CameraLerp
	State.ChangeState(EFIREWORKSSTATE::FireWorks);
}

void FireWorksEvent::EndFire(GameEngineState* _Parent)
{
	// Camera
}


void FireWorksEvent::UpdateFireWorks(float _Delta, GameEngineState* _Parent)
{
	 // 파파파팡
	State.ChangeState(EFIREWORKSSTATE::LastConversation);
}


void FireWorksEvent::StartLastConversation(GameEngineState* _Parent)
{
	EventConversation.StartConversation(EFIREWORKSEVENTTOPIC::Last);
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