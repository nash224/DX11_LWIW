#include "PreCompile.h"
#include "SilverBellSpawner.h"

#include "SilverStarPollen.h"

SilverBellSpawner::SilverBellSpawner() 
{
}

SilverBellSpawner::~SilverBellSpawner() 
{
}


void SilverBellSpawner::Update(float _Delta)
{
	UpdateSpawner(_Delta);
}


void SilverBellSpawner::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void SilverBellSpawner::UpdateSpawner(float _Delta)
{
	if (GetLiveTime() > 2.0f)
	{
		Death();
	}

	const float Create_Pollen_Time = 0.2f;

	CreatePollenCoolTime += _Delta;
	if (CreatePollenCoolTime > Create_Pollen_Time)
	{
		CreatePollenCoolTime = 0.0f;
		CreatePollen();
	}
}

void SilverBellSpawner::CreatePollen()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());

	float RandomDistance = RandomClass.RandomFloat(5.0f, 10.0f);

	const float4 DirectionVector = float4::GetUnitVectorFromDeg(RandomClass.RandomFloat(3.0f, 150.0f));
	const float4 RandomVector = DirectionVector * RandomDistance;
	const float4 FlowerPosition = Transform.GetLocalPosition();
	const float4 PollenPosition = FlowerPosition + RandomVector + float4(0.0f, 16.0f, -0.2f);

	std::shared_ptr<SilverStarPollen> Pollen = GetLevel()->CreateActor<SilverStarPollen>(EUPDATEORDER::Objects);
	Pollen->Transform.SetLocalPosition(PollenPosition);
	Pollen->Init();
}