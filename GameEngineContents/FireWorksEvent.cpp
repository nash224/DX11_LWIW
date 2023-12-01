#include "PreCompile.h"
#include "FireWorksEvent.h"

#include "AlertManager.h"
#include "BGMManager.h"
#include "CameraControler.h"
#include "TimeManager.h"
#include "UIManager.h"

#include "Ellie.h"
#include "FadeObject.h"
#include "FireWorks.h"
#include "ContentsEvent.h"


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
 
void FireWorksEvent::Release()
{
	SceneryInfo.Release();
	EventConversation.Release();
}

void FireWorksEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void FireWorksEvent::Init()
{
	PotionSetting();
	SceneryInfo.RendererSetting(this);
	ConversationSetting();
	StateSetting();
}

void FireWorksEvent::PotionSetting()
{
	CrackerPotion = GetLevel()->CreateActor<FireWorks>(EUPDATEORDER::Objects);
	CrackerPotion->Transform.SetLocalPosition(Transform.GetLocalPosition());
	CrackerPotion->Init();
}

void FireWorksEvent::FarsightedScenryStruct::RendererSetting(GameEngineActor* _Actor)
{
	const float SkyDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Scenery_Sky);
	const float GroundDepth = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Scenery_Ground);

	const float4 WinScale = GlobalValue::GetWindowScale();

	const float4 CurPositon = _Actor->Transform.GetLocalPosition();
	const float SkyYPos = 2000.0f + WinScale.hY();
	const float GroundYPos = 1600.0f + WinScale.hY();

	SkyRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	SkyRenderer->Transform.SetLocalPosition(float4(0.0f, SkyYPos, SkyDepth));
	SkyRenderer->SetSprite("Farsighted_0.png");
	SkyRenderer->AutoSpriteSizeOn();
	SkyRenderer->SetAutoScaleRatio(4.0f);
	SkyRenderer->SetPivotType(PivotType::Top);

	GroundRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
	GroundRenderer->Transform.SetLocalPosition(float4(0.0f, GroundYPos, GroundDepth));
	GroundRenderer->SetSprite("Farsighted_2.png");
	GroundRenderer->AutoSpriteSizeOn();
	GroundRenderer->SetAutoScaleRatio(4.0f);
	GroundRenderer->SetPivotType(PivotType::Top);

	GameEngineRandom RandomClass;

	const int StarCnt = 20;
	StarRenderers.reserve(StarCnt);
	for (int i = 0; i < StarCnt; i++)
	{
		RandomClass.SetSeed(GlobalValue::GetSeedValue());
		float4 StarPosition = RandomClass.RandomVectorBox2D(-WinScale.hX(), WinScale.hX(), -WinScale.hY(), WinScale.hY());
		StarPosition += float4(0.0f, 2000.0f, GroundDepth);
		const float StarRatio = RandomClass.RandomFloat(0.8f, 1.2f);
		const float StarInter = RandomClass.RandomFloat(0.09f, 0.12f);

		std::shared_ptr<GameEngineSpriteRenderer> StarRenderer = _Actor->CreateComponent<GameEngineSpriteRenderer>();
		StarRenderer->Transform.SetLocalPosition(StarPosition);
		StarRenderer->AutoSpriteSizeOn();
		StarRenderer->SetAutoScaleRatio(StarRatio);
		StarRenderer->CreateAnimation("TwinkledStar", "WitchLock_Twinkle.png", StarInter, 2, -1);
		StarRenderer->ChangeAnimation("TwinkledStar");
		StarRenderer->RenderBaseInfoValue.Target3 = 1;
	}
}

void FireWorksEvent::FarsightedScenryStruct::Release()
{
	SkyRenderer = nullptr;
	GroundRenderer = nullptr;
	StarRenderers.clear();
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
			PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr()->UseUIComponent();

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
			PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr()->UseUIComponent();

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

	CreateStateParameter LastConversationState;
	LastConversationState.Start = std::bind(&FireWorksEvent::StartLastConversation, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::LastConversation, LastConversationState);

	CreateStateParameter EndTrainingState;
	EndTrainingState.Start = std::bind(&FireWorksEvent::StartEndTraining, this, std::placeholders::_1);
	EndTrainingState.Stay = std::bind(&FireWorksEvent::UpdateEndTraining, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(EFIREWORKSSTATE::EndTraining, EndTrainingState);

	CreateStateParameter FadeOutState;
	FadeOutState.Start = std::bind(&FireWorksEvent::StartFadeOut, this, std::placeholders::_1);
	State.CreateState(EFIREWORKSSTATE::FadeOut, FadeOutState);

	State.ChangeState(EFIREWORKSSTATE::FadeIn);
}

void FireWorksEvent::StartFadeIn(GameEngineState* _Parent)
{
	SetElliePlacement();

	std::weak_ptr<FadeObject> Fade = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::Fade);
	Fade.lock()->CallFadeIn(LastFadeTime);


	if (false == CameraControler::MainCameraControler.expired())
	{
		CameraControler::MainCameraControler.lock()->SetCameraMode(ECAMERAMODE::Fix);
		CameraControler::MainCameraControler.lock()->SetCameraPos(Transform.GetLocalPosition());
	}

	PlayLevel::GetPlayLevelPtr()->GetUIManagerPtr()->UseUIComponent();

	if (nullptr != ContentsLevel::MainPlaySound)
	{
		ContentsLevel::MainPlaySound->AbsoluteNoneBGM();
	}

	if (nullptr != PlayLevel::s_TimeManager)
	{
		PlayLevel::s_TimeManager->SetTime(22, 0);
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


void FireWorksEvent::StartLastConversation(GameEngineState* _Parent)
{
	EventConversation.StartConversation(EFIREWORKSEVENTTOPIC::Last);
}

void FireWorksEvent::StartEndTraining(GameEngineState* _Parent)
{
	CheckEndtrainingEvent();
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



void FireWorksEvent::UpdateFireWorks(float _Delta, GameEngineState* _Parent)
{
	if (nullptr == CrackerPotion)
	{
		MsgBoxAssert("폭죽 포션이 없인 이벤트를 수행할 수 없습니다.");
		return;
	}

	if (true == CrackerPotion->IsEndFireWork())
	{
		static constexpr float WaitTime = 2.4f;
		StateTime += _Delta;
		if (StateTime > WaitTime)
		{
			State.ChangeState(EFIREWORKSSTATE::LastConversation);
			return;
		}
	}
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




// 앨리 위치 조정
void FireWorksEvent::SetElliePlacement() const
{
	const float4& VectorToEllie = float4(-70.0f, -20.0f);
	
	const std::shared_ptr<Ellie>& PlayerPtr = PlayLevel::GetPlayLevelPtr()->GetPlayerPtr();
	PlayerPtr->Transform.SetLocalPosition(VectorToEllie + Transform.GetLocalPosition());
	PlayerPtr->SetAnimationByDirection(EDIRECTION::RIGHT);
	PlayerPtr->ApplyDepth();
}

void FireWorksEvent::CheckEndtrainingEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("StartTraining");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	Quest.lock()->QuestComplete();
}