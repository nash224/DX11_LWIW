#include "PreCompile.h"
#include "LowerLiftA.h"

#include "ContentsEvent.h"
#include "WorkplaceFindEvent.h"

LowerLiftA::LowerLiftA() 
{
	BaseLift::LiftArrivePoint = float4::ZERO;
	BaseLift::ChangeLevelName = "WitchHouse_UpFloor";
	BaseLift::EnterType = ELIFTDIR::Up;
	BaseLift::ArriveType = ELIFTDIR::Down;
}

LowerLiftA::~LowerLiftA() 
{
}


void LowerLiftA::Start()
{
	BaseLift::Start();
	InteractiveActor::SetGearName("작업실로 이동");
}

void LowerLiftA::Update(float _Delta)
{
	BaseLift::Update(_Delta);
}

void LowerLiftA::Release()
{
	BaseLift::Release();
}

void LowerLiftA::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void LowerLiftA::Init()
{
	BaseLift::Init();
}

void LowerLiftA::StartEnter(GameEngineState* _Parent)
{
	BaseLift::StartEnter(_Parent);

	AppearLift();
}

void LowerLiftA::StartArrive(GameEngineState* _Parent)
{
	BaseLift::StartArrive(_Parent);

	AppearLift();
}

void LowerLiftA::EndEnter(GameEngineState* _Parent)
{
	BaseLift::EndEnter(_Parent);
}

void LowerLiftA::EndArrive(GameEngineState* _Parent)
{
	BaseLift::EndArrive(_Parent);

	CheckFindWorkPlaceEvent();
}


void LowerLiftA::CheckFindWorkPlaceEvent()
{
	std::weak_ptr<ContentsEvent::QuestUnitBase> Quest = ContentsEvent::FindQuest("FindWorkPlace");
	if (true == Quest.expired())
	{
		MsgBoxAssert("생성되지 않은 퀘스트입니다.");
		return;
	}

	if (false == Quest.lock()->isQuestComplete())
	{
		ShowFindWorkPlaceEvent();
		Quest.lock()->QuestComplete();
	}
}

void LowerLiftA::ShowFindWorkPlaceEvent()
{
	std::weak_ptr<WorkplaceFindEvent> Event = GetLevel()->CreateActor<WorkplaceFindEvent>(EUPDATEORDER::Entity);
	Event.lock()->Init();
}