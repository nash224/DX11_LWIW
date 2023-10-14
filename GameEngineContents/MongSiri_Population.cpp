#include "PreCompile.h"
#include "MongSiri_Population.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "MongSiri.h"
#include "ChubHole.h"
#include "BackDrop_PlayLevel.h"

MongSiri_Population::MongSiri_Population() 
{
}

MongSiri_Population::~MongSiri_Population() 
{
}



void MongSiri_Population::Start()
{

}

void MongSiri_Population::Update(float _Delta)
{
	UpdateEntityMiddlePoint();
}

void MongSiri_Population::Release()
{
	
}

void MongSiri_Population::LevelStart(class GameEngineLevel* _NextLevel)
{
	
}

void MongSiri_Population::LevelEnd(class GameEngineLevel* _NextLevel)
{
	
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// _Population : 개체수만큼 몽시리를 생성합니다.
void MongSiri_Population::Init(unsigned int _Population)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	SetUpChubHole(CurLevel);
	GetHoleScale();
	ExploreSpawnLocation();
	CreateMongSiri(CurLevel, _Population);
}

// 구멍을 설치합니다.
void MongSiri_Population::SetUpChubHole(GameEngineLevel* _CurLevel)
{
	m_ChubHole = _CurLevel->CreateActor<ChubHole>(EUPDATEORDER::Objects);
	if (nullptr == m_ChubHole)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("nullptr == BackDrop_PlayLevel::MainBackDrop");
		return;
	}


	float4 CurrentPosition = Transform.GetLocalPosition();
	float ZSort = BackDrop_PlayLevel::MainBackDrop->ZSort(CurrentPosition.Y);
	m_ChubHole->Transform.SetLocalPosition({ CurrentPosition.X , CurrentPosition.Y, ZSort });
	m_ChubHole->Init();
}

// 구멍의 크기를 얻어옵니다.
void MongSiri_Population::GetHoleScale()
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("SquishychubHole.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 로드하지 못했습니다.");
		return;
	}

	m_HoleScale = Texture->GetScale();
}

// 몽시리가 스폰할 장소를 찾습니다.
void MongSiri_Population::ExploreSpawnLocation()
{
	if (float4::ZERO == m_HoleScale)
	{
		MsgBoxAssert("범위가 0인 텍스처는 사용할 수 없습니다.");
		return;
	}

	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("배경 매니저가 존재하지 않습니다.");
		return;
	}

	CheckInstallationHoleSpace();
}

// 구멍이 맞게 설치되어 있는지 검사합니다.
void MongSiri_Population::CheckInstallationHoleSpace()
{
	float4 CurrentPosition = Transform.GetWorldPosition();

	float4 HalfHoleScale = m_HoleScale.Half();

	for (size_t i = 0; i < 4; i++)
	{
		float4 CheckPoint = float4::ZERO;
		switch (i)
		{
		case 0:
			CheckPoint += CurrentPosition + float4{ -HalfHoleScale.X, HalfHoleScale.Y };
			break;
		case 1:
			CheckPoint += CurrentPosition + float4{ HalfHoleScale.X, HalfHoleScale.Y };
			break;
		case 2:
			CheckPoint += CurrentPosition + float4{ HalfHoleScale.X, -HalfHoleScale.Y };
			break;
		case 3:
			CheckPoint += CurrentPosition + float4{ -HalfHoleScale.X, -HalfHoleScale.Y };
			break;
		default:
			break;
		}

		if (true == BackDrop_PlayLevel::MainBackDrop->IsColorAtPosition(CheckPoint, GameEngineColor::RED))
		{
			MsgBoxAssert("현재 지역에는 설치할 수 없습니다.");
			return;
		}
	}
}

// 1. 구멍으로부터 거리
// 2. 위 거리에서 일정 범위 안에 개체군 확인
void MongSiri_Population::SetPopulationSpawnLocation(const float4& _Location)
{
	m_PopulationLocation = _Location;
}

void MongSiri_Population::CreateMongSiri(GameEngineLevel* _CurLevel, unsigned int _Population)
{
	GameEngineRandom RandomClass;

	for (size_t i = 0; i < _Population; i++)
	{
		std::shared_ptr<MongSiri> Object = _CurLevel->CreateActor<MongSiri>(EUPDATEORDER::Entity);
		if (nullptr == Object)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		Object->MongSiriParant = this;
		SetMongSiriSeed(Object, RandomClass);
		Object->Init();
		MongSiriEntityList.push_back(Object);
	}
}

void MongSiri_Population::SetMongSiriSeed(std::shared_ptr<MongSiri> _Actor, GameEngineRandom& _RandomClass)
{
	// 시드설정 
	_RandomClass.SetSeed(reinterpret_cast<__int64>(_Actor.get()));

	float MongSiriSpawnDistance = _RandomClass.RandomFloat(0.0f, MonSiriSpawnRangeSize);		// 스폰 랜덤 거리 : 0 ~ 120.0f 
	float MongSiriSpawnAngle = _RandomClass.RandomFloat(0.0f, 360.0f);							// 스폰 랜덤 각도
	float4 MongSiriSpawnUnitVector = float4::GetUnitVectorFromDeg(MongSiriSpawnAngle);			// 각도 단위 백터
	float4 MonSiriPosition = m_PopulationLocation + MongSiriSpawnUnitVector * MongSiriSpawnDistance;		// 스폰 위치 = 개체군 위치 + 스폰각도 * 랜덤 거리

	// 적용
	_Actor->ApplyDepth(MonSiriPosition);
}


void MongSiri_Population::UpdateEntityMiddlePoint()
{
	m_MiddlePoint = float4::ZERO;

	float4 MiddlePoint = float4::ZERO;

	for (std::shared_ptr<MongSiri> Entity : MongSiriEntityList)
	{
		MiddlePoint += Entity->Transform.GetLocalPosition();
	}

	MiddlePoint /= static_cast<float>(MongSiriEntityList.size());

	m_MiddlePoint = MiddlePoint;
}

void MongSiri_Population::EscapeHole()
{
	std::list<std::shared_ptr<MongSiri>>::iterator StarIter = MongSiriEntityList.begin();
	std::list<std::shared_ptr<MongSiri>>::iterator EndIter = MongSiriEntityList.end();

	for (;StarIter != EndIter; ++StarIter)
	{
		(*StarIter)->m_Status = EMONGSIRISTATUS::Escape;
	}
}


void MongSiri_Population::ActorRelaese()
{
	for (std::shared_ptr<MongSiri> Object : MongSiriEntityList)
	{
		Object->Death();
	}

	MongSiriEntityList.clear();

	m_ChubHole->Death();
}