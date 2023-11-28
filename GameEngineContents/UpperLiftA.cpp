#include "PreCompile.h"
#include "UpperLiftA.h"



void UpperLiftEvent::Init()
{
	const float FloorDepth = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Lift_Floor);
	const float WallDepth = DepthFunction::CalculateFixDepth(EHOUSEDEPTH::Lift_Wall);

	FloorRenderer = CreateComponent<GameEngineSpriteRenderer>();
	FloorRenderer->Transform.SetLocalPosition(float4(517.0f, -289.0f, FloorDepth));
	FloorRenderer->SetSprite("MakingRoom_Gate_Floor.png");

	WallRenderer= CreateComponent<GameEngineSpriteRenderer>();
	WallRenderer->Transform.SetLocalPosition(float4(515.0f, -262.0f, WallDepth));
	WallRenderer->SetSprite("MakingRoom_Gate_Wall.png");

	Off();
}

void UpperLiftEvent::Release()
{
	FloorRenderer = nullptr;
	WallRenderer = nullptr;
}

void UpperLiftEvent::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



UpperLiftA::UpperLiftA() 
{
	BaseLift::LiftArrivePoint = float4::ZERO;
	BaseLift::ChangeLevelName = "WitchHouse_DownFloor";
	BaseLift::EnterType = ELIFTDIR::Down;
	BaseLift::ArriveType = ELIFTDIR::Up;
}

UpperLiftA::~UpperLiftA() 
{
}

void UpperLiftA::Start()
{
	BaseLift::Start();
	InteractiveActor::SetGearName("작업실로 이동");
}

void UpperLiftA::Update(float _Delta)
{
	BaseLift::Update(_Delta);
}

void UpperLiftA::Release()
{
	BaseLift::Release();
}

void UpperLiftA::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void UpperLiftA::Init()
{
	BaseLift::Init();
}

void UpperLiftA::StartEnter(GameEngineState* _Parent)
{
	BaseLift::StartEnter(_Parent);

	AppearLift();
	HideFloor = GetLevel()->CreateActor<UpperLiftEvent>(EUPDATEORDER::Objects);
	HideFloor.lock()->Init();
	HideFloor.lock()->On();
}

void UpperLiftA::StartArrive(GameEngineState* _Parent)
{
	BaseLift::StartArrive(_Parent);

	AppearLift();
	HideFloor = GetLevel()->CreateActor<UpperLiftEvent>(EUPDATEORDER::Objects);
	HideFloor.lock()->Init();
	HideFloor.lock()->On();
}

void UpperLiftA::EndEnter(GameEngineState* _Parent)
{
	BaseLift::EndEnter(_Parent);
}

void UpperLiftA::EndArrive(GameEngineState* _Parent)
{
	BaseLift::EndArrive(_Parent);

	DisappearLift();
	if (true == HideFloor.expired())
	{
		MsgBoxAssert("객체가 존재하지 않습니다.");
		return;
	}

	HideFloor.lock()->Death();
}


