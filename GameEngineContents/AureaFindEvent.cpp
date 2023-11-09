#include "PreCompile.h"
#include "AureaFindEvent.h"

#include "UIManager.h"
#include "CameraControler.h"
#include "Aurea.h"
#include "Ellie.h"

AureaFindEvent::AureaFindEvent() 
{
}

AureaFindEvent::~AureaFindEvent() 
{
}


void AureaFindEvent::Start()
{
}

void AureaFindEvent::Update(float _Delta)
{
	State.Update(_Delta);
	VirgilConveration.UpdateConversation(_Delta);
}

void AureaFindEvent::Release()
{
	AureaPtr = nullptr;
}

void AureaFindEvent::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void AureaFindEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void AureaFindEvent::Init()
{
	ConversationSetting();
	StateSetting();
}



void AureaFindEvent::StateSetting()
{
	CreateStateParameter FirstConversationState;
	FirstConversationState.Start = std::bind(&AureaFindEvent::StartFirstConversation, this, std::placeholders::_1);
	State.CreateState(ECURSEEVENTSTATE::FirstConversation, FirstConversationState);


	CreateStateParameter AureaFocusOnState;
	AureaFocusOnState.Start = std::bind(&AureaFindEvent::StartAureaFocusOn, this, std::placeholders::_1);
	AureaFocusOnState.Stay = std::bind(&AureaFindEvent::UpdateAureaFocusOn, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECURSEEVENTSTATE::AureaFocusOn, AureaFocusOnState);

	CreateStateParameter StayState;
	StayState.Stay = std::bind(&AureaFindEvent::UpdateStay, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECURSEEVENTSTATE::Stay, StayState);

	CreateStateParameter FocusOffState;
	FocusOffState.Stay = std::bind(&AureaFindEvent::UpdateAureaFocusOff, this, std::placeholders::_1, std::placeholders::_2);
	State.CreateState(ECURSEEVENTSTATE::AureaFocusOff, FocusOffState);

	CreateStateParameter SecondConversationState;
	SecondConversationState.Start = std::bind(&AureaFindEvent::StartSecondConversation, this, std::placeholders::_1);
	State.CreateState(ECURSEEVENTSTATE::SecondConversation, SecondConversationState);


	State.ChangeState(ECURSEEVENTSTATE::FirstConversation);
}


void AureaFindEvent::StartFirstConversation(GameEngineState* _Parent)
{
	ConverseWithEllie();
}

void AureaFindEvent::StartAureaFocusOn(GameEngineState* _Parent)
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		GlobalValue::g_CameraControler->SetCameraMode(ECAMERAMODE::Cinematic);
	}

	float4 MovePosition = AureaPtr->Transform.GetLocalPosition() - Ellie::MainEllie->Transform.GetLocalPosition();
	
	float4 ResultAngle = DirectX::XMVector2AngleBetweenVectors(MovePosition.DirectXVector, float4::RIGHT.DirectXVector);
	float CameraMoveAngle = ResultAngle.X* GameEngineMath::R2D;
	
	if (MovePosition.Y < 0.0f)
	{
		CameraMoveAngle = 360.0f - CameraMoveAngle;
	}
	
	CameraDirection = float4::GetUnitVectorFromDeg(CameraMoveAngle);
	CameraDirection.Z = 0.0;
}

void AureaFindEvent::StartSecondConversation(GameEngineState* _Parent)
{
	VirgilConveration.StartConversation(ECURSEEVENTTOPIC::Closer);
}


void AureaFindEvent::UpdateAureaFocusOn(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		std::weak_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();
		const float4& MoveCameraVector = CameraDirection* CameraMovePower* _Delta;
		GlobalValue::g_CameraControler->AddCameraPos(MoveCameraVector);

		float Distance = CalculateDistanceCamemeraToActor(AureaPtr->Transform.GetLocalPosition());
		if (Distance < 4.0f)
		{
			State.ChangeState(ECURSEEVENTSTATE::Stay);
		}
	}
}

void AureaFindEvent::UpdateStay(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 1.2f)
	{
		State.ChangeState(ECURSEEVENTSTATE::AureaFocusOff);
	}
}

void AureaFindEvent::UpdateAureaFocusOff(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		std::weak_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();

		float4 ReverseCameraDirection = -CameraDirection;
		ReverseCameraDirection.Z = 0.0f;
		const float4& MoveCameraVector = ReverseCameraDirection * CameraMovePower * _Delta;
		GlobalValue::g_CameraControler->AddCameraPos(MoveCameraVector);

		float Distance = CalculateDistanceCamemeraToActor(Ellie::MainEllie->Transform.GetLocalPosition());
		if (Distance < 4.0f)
		{
			State.ChangeState(ECURSEEVENTSTATE::SecondConversation);
		}
	}
}

float AureaFindEvent::CalculateDistanceCamemeraToActor(const float4& _Position)
{
	float4 Distance = GetLevel()->GetMainCamera()->Transform.GetLocalPosition() - _Position;
	Distance = DirectX::XMVector2Length(Distance.DirectXVector);

	return Distance.X;
}

void AureaFindEvent::ConversationSetting()
{
	Topic LookTopic;

	LookTopic.Data.reserve(64);
	LookTopic.Data =
	{
		{ L"응? 저기 누가 있는 것 같은데?" , ECONVERSATIONENTITY::Virgil , 1, LookTopic.Color_BLACK, GlobalValue::Font_JejuHanlasan},
	};

	LookTopic.Data.shrink_to_fit();
	VirgilConveration.CreateTopic(ECURSEEVENTTOPIC::Look, LookTopic);

	VirgilConveration.SetConversationEndEvent(ECURSEEVENTTOPIC::Look, [&]()
		{
			UIManager::MainUIManager->UseUIComponent();
			State.ChangeState(ECURSEEVENTSTATE::AureaFocusOn);
		});



	Topic CloserTopic;
	CloserTopic.Default_Npc_Sprite_Index = 0;
	CloserTopic.Data.reserve(64);
	CloserTopic.Data =
	{
		{ L"어? 정말이네. 이곳의 마을 주민인가봐." , ECONVERSATIONENTITY::Ellie, 1 },
		{ L"다가가서 말 걸어보자." , ECONVERSATIONENTITY::Ellie, 1 },
	};

	CloserTopic.Data.shrink_to_fit();
	VirgilConveration.CreateTopic(ECURSEEVENTTOPIC::Closer, CloserTopic);


	VirgilConveration.SetConversationEndEvent(ECURSEEVENTTOPIC::Closer, [&]()
		{
			if (nullptr != GlobalValue::g_CameraControler)
			{
				GlobalValue::g_CameraControler->SetCameraMode(ECAMERAMODE::Play);
			}
			Death();
		});
}

void AureaFindEvent::ConverseWithEllie()
{
	VirgilConveration.StartConversation(ECURSEEVENTTOPIC::Look);
}