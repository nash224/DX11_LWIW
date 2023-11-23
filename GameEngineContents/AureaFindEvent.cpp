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
	FocusOffState.Start = std::bind(&AureaFindEvent::StartAureaFocusOff, this, std::placeholders::_1);
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

	if (true == CameraControler::MainCameraControler.expired())
	{
		MsgBoxAssert("카메라가 존재하지 않는데 사용하려 했습니다.");
		return;
	}

	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
		return;
	}

	CameraControler::MainCameraControler.lock()->SetCameraMode(ECAMERAMODE::Cinematic);

	const float4& ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();
	const float4& CameraPos = CameraControler::MainCameraControler.lock()->AdjustCameraInitialPosition(ElliePos);
	const float4& NPCPos = AureaPtr->Transform.GetLocalPosition();
	TargetPos = CameraControler::MainCameraControler.lock()->AdjustCameraInitialPosition(NPCPos);
	const float4& TargetVector = TargetPos - CameraPos;
	const float Radian = std::atan2f(TargetVector.Y, TargetVector.X);
	CameraDirection = float4::GetUnitVectorFromRad(Radian);
}

void AureaFindEvent::StartAureaFocusOff(GameEngineState* _Parent)
{
	std::weak_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();
	if (true == Camera.expired())
	{
		MsgBoxAssert("존재하지 않는 카메라입니다.");
		return;
	}

	if (nullptr == Ellie::MainEllie)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
		return;
	}

	const float4& WinScale = GlobalValue::GetWindowScale();
	const float4& CameraPos = Camera.lock()->Transform.GetLocalPosition();
	const float4& ElliePos = Ellie::MainEllie->Transform.GetLocalPosition();

	TargetPos = ElliePos;

	if (ElliePos.Y >= -WinScale.hY())
	{
		TargetPos.Y = -WinScale.hY();
	}

	const float4& TargetVector = TargetPos - CameraPos;
	const float Radian = std::atan2f(TargetVector.Y, TargetVector.X);
	CameraDirection = float4::GetUnitVectorFromRad(Radian);
}

void AureaFindEvent::StartSecondConversation(GameEngineState* _Parent)
{
	VirgilConveration.StartConversation(ECURSEEVENTTOPIC::Closer);
}


void AureaFindEvent::UpdateAureaFocusOn(float _Delta, GameEngineState* _Parent)
{
	if (true == CameraControler::MainCameraControler.expired())
	{
		const float4& MoveCameraVector = CameraDirection* CameraMovePower* _Delta;
		CameraControler::MainCameraControler.lock()->AddCameraPos(MoveCameraVector);

		float Distance = CalculateDistanceCamemeraToActor(TargetPos);
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
	if (true == CameraControler::MainCameraControler.expired())
	{
		const float4& MoveCameraVector = CameraDirection * CameraMovePower * _Delta;
		CameraControler::MainCameraControler.lock()->AddCameraPos(MoveCameraVector);

		float Distance = CalculateDistanceCamemeraToActor(TargetPos);
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
		{ L"응? 저기 누가 있는 것 같은데?" , ECONVERSATIONENTITY::Virgil , 1, {ConversationFont::Color_BLACK, GlobalValue::Font_JejuHanlasan}},
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
			if (true == CameraControler::MainCameraControler.expired())
			{
				CameraControler::MainCameraControler.lock()->SetCameraMode(ECAMERAMODE::Play);
			}
			Death();
		});
}

void AureaFindEvent::ConverseWithEllie()
{
	VirgilConveration.StartConversation(ECURSEEVENTTOPIC::Look);
}