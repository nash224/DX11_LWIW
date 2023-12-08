#include "PreCompile.h"
#include "BackDrop_Field.h"

#include "PlayLevel.h"
#include "TimeManager.h"


#include "MongSiri_Population.h"
#include "Bush.h"
#include "WitchFlower.h"
#include "SilverStarFlower.h"
#include "FlowerBird.h"
#include "BranchTree.h"
#include "Aurea.h"
#include "PumpkinTerrier.h"
#include "LootedItem.h"



BackDrop_Field::BackDrop_Field() 
{
}

BackDrop_Field::~BackDrop_Field() 
{
}

void BackDrop_Field::Start()
{
	BackDrop_PlayLevel::Start();

	StateSetting();
}


void BackDrop_Field::Update(float _Delta)
{
	FieldState.Update(_Delta);
}

void BackDrop_Field::LevelStart(class GameEngineLevel* _NextLevel)
{
	BackDrop_PlayLevel::LevelStart(_NextLevel);

	if (nullptr != PlayLevel::GetTimeManager())
	{
		int TimeDay = PlayLevel::GetTimeManager()->GetDayCount();
		bool UpdateDayisNotSame = (FieldDay != TimeDay);
		if (UpdateDayisNotSame)
		{
			FieldDay = TimeDay;
			isNight = false;

			FieldState.ChangeState(EDAYSTATE::DayChange);
		}
	}
}


#pragma region CreateCreture

void BackDrop_Field::CreateBush(const float4& _Position, EBUSHTYPE _Type)
{
	std::shared_ptr<Bush> BushObject = GetLevel()->CreateActor<Bush>(EUPDATEORDER::Entity);
	BushObject->Transform.SetLocalPosition(_Position);
	BushObject->SetBushType(_Type);
	BushObject->Init();
}

void BackDrop_Field::CreateWitchFlower(const float4& _Position)
{
	std::shared_ptr<WitchFlower> Object = GetLevel()->CreateActor<WitchFlower>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(_Position);
	Object->Init();
}

void BackDrop_Field::CreateSilverStarFlower(const float4& _Position)
{
	std::shared_ptr<SilverStarFlower> Object = GetLevel()->CreateActor<SilverStarFlower>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(_Position);
	Object->Init();
}

void BackDrop_Field::CreateBranchTree(const float4& _Position)
{
	std::shared_ptr<BranchTree> Object = GetLevel()->CreateActor<BranchTree>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(_Position);
	Object->Init();
}

void BackDrop_Field::CreateMongSiriPopulation(int _MongsiriCount, const float4& _HolePosition, const float4& _MongsiriPosition)
{
	std::shared_ptr<MongSiri_Population> MongSiri1 = GetLevel()->CreateActor<MongSiri_Population>(EUPDATEORDER::Objects);
	MongSiri1->Transform.SetLocalPosition(_HolePosition);
	MongSiri1->SetPopulationSpawnLocation(_MongsiriPosition);
	MongSiri1->Init(_MongsiriCount);
}

void BackDrop_Field::CreateFlowerBird(const float4& _Position)
{
	std::shared_ptr<FlowerBird> Object = GetLevel()->CreateActor<FlowerBird>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(_Position);
	Object->Init();
}

void BackDrop_Field::CreatePumpkinTerrier(const float4& _Position)
{
	std::shared_ptr<PumpkinTerrier> Object = GetLevel()->CreateActor<PumpkinTerrier>(EUPDATEORDER::Entity);
	Object->Transform.SetLocalPosition(_Position);
	Object->Init();
}

#pragma endregion

#pragma region LeaveCreature

void BackDrop_Field::LeavePopulation()
{
	const std::vector<std::shared_ptr<MongSiri_Population>>& GroupPopulation = GetLevel()->GetObjectGroupConvert<MongSiri_Population>(EUPDATEORDER::Objects);
	for (std::weak_ptr<MongSiri_Population> Population : GroupPopulation)
	{
		if (true == Population.expired())
		{
			MsgBoxAssert("아무것도 들어있지 않습니다");
			return;
		}

		Population.lock()->EscapeHoleToOtherMonsiri();
	}
}

void BackDrop_Field::LeaveFlowerBird()
{
	const std::vector<std::shared_ptr<FlowerBird>>& BirdGroup = GetLevel()->GetObjectGroupConvert<FlowerBird>(EUPDATEORDER::Entity);
	for (std::weak_ptr<FlowerBird> Bird : BirdGroup)
	{
		if (true == Bird.expired())
		{
			MsgBoxAssert("아무것도 들어있지 않습니다");
			return;
		}

		Bird.lock()->Leave();
	}
}

#pragma endregion

#pragma region Release

void BackDrop_Field::ReleaseMongSiriPopulation()
{
	const std::vector<std::shared_ptr<MongSiri_Population>>& GroupPopulation = GetLevel()->GetObjectGroupConvert<MongSiri_Population>(EUPDATEORDER::Objects);
	for (std::weak_ptr<MongSiri_Population> Population : GroupPopulation)
	{
		if (true == Population.expired())
		{
			MsgBoxAssert("아무것도 들어있지 않습니다");
			return;
		}

		Population.lock()->ActorRelaese();
	}
}

void BackDrop_Field::ReleaseItemDrop()
{
	std::vector<std::shared_ptr<LootedItem>> DropItems = GetLevel()->GetObjectGroupConvert<LootedItem>(EUPDATEORDER::Entity);
	for (std::weak_ptr<LootedItem> DropItem : DropItems)
	{
		if (true == DropItem.expired())
		{
			MsgBoxAssert("아무것도 들어있지 않습니다");
			return;
		}

		DropItem.lock()->Death();
	}
}

#pragma endregion






#pragma region FieldState

void BackDrop_Field::StateSetting()
{
	CreateStateParameter DayState;
	DayState.Start = std::bind(&BackDrop_Field::StartDay, this, std::placeholders::_1);
	DayState.Stay = std::bind(&BackDrop_Field::UpdateDay, this, std::placeholders::_1, std::placeholders::_2);
	DayState.End = std::bind(&BackDrop_Field::EndDay, this, std::placeholders::_1);
	FieldState.CreateState(EDAYSTATE::Day, DayState);

	CreateStateParameter NightState;
	NightState.Start = std::bind(&BackDrop_Field::StartNight, this, std::placeholders::_1);
	NightState.Stay = std::bind(&BackDrop_Field::UpdateNight, this, std::placeholders::_1, std::placeholders::_2);
	NightState.End = std::bind(&BackDrop_Field::EndNight, this, std::placeholders::_1);
	FieldState.CreateState(EDAYSTATE::Night, NightState);

	CreateStateParameter DayChangeState;
	DayChangeState.Start = std::bind(&BackDrop_Field::StartDayChange, this, std::placeholders::_1);
	FieldState.CreateState(EDAYSTATE::DayChange, DayChangeState);
}


void BackDrop_Field::StartDay(GameEngineState* _Parent)
{
	CreateCreatureWhenDayChange();
}

void BackDrop_Field::StartNight(GameEngineState* _Parent)
{
	AppearNightCreature();
}

void BackDrop_Field::StartDayChange(GameEngineState* _Parent)
{
	ReleaseAllCreature();
	FieldState.ChangeState(EDAYSTATE::Day);
}

void BackDrop_Field::UpdateDay(float _Delta, GameEngineState* _Parent)
{
	DetectNight();
}

void BackDrop_Field::UpdateNight(float _Delta, GameEngineState* _Parent)
{

}


void BackDrop_Field::EndDay(GameEngineState* _Parent)
{
	DisappearDayCreature();
}

void BackDrop_Field::EndNight(GameEngineState* _Parent)
{
	
}

void BackDrop_Field::DetectNight()
{
	if (nullptr != PlayLevel::GetTimeManager())
	{
		bool isChangeNight = (false == isNight && EDAYSTATE::Night == PlayLevel::GetTimeManager()->GetDayState());
		if (isChangeNight)
		{
			FieldState.ChangeState(EDAYSTATE::Night);
			isNight = true;
		}
	}
}
#pragma endregion
