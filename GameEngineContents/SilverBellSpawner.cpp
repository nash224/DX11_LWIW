#include "PreCompile.h"
#include "SilverBellSpawner.h"

#include "SilverStarPollen.h"

SilverBellSpawner::SilverBellSpawner() 
{
}

SilverBellSpawner::~SilverBellSpawner() 
{
}


void SilverBellSpawner::Start()
{
}

void SilverBellSpawner::Update(float _Delta)
{
	UpdateSpawner(_Delta);
}

void SilverBellSpawner::Release()
{
}

void SilverBellSpawner::LevelStart(class GameEngineLevel* _NextLevel)
{
}

void SilverBellSpawner::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void SilverBellSpawner::UpdateSpawner(float _Delta)
{
	if (GetLiveTime() > Limit_CreatePollen_Time)
	{
		Death();
	}

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
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	float RandomAngle = RandomClass.RandomFloat(3.0f, 150.0f);
	float RandomDistance = RandomClass.RandomFloat(5.0f, 10.0f);

	const float4& DirectionVector = float4::GetUnitVectorFromDeg(RandomAngle);
	const float4& RandomVector = DirectionVector * RandomDistance;
	const float4& FlowerPosition = Transform.GetLocalPosition();
	const float4& PollenPosition = FlowerPosition + RandomVector + float4(0.0f, 16.0f);

	std::shared_ptr<SilverStarPollen> Pollen = GetLevel()->CreateActor<SilverStarPollen>(EUPDATEORDER::Objects);
	Pollen->Transform.SetLocalPosition(PollenPosition);
	Pollen->Init();
}