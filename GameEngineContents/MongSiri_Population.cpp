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

// _Population : ��ü����ŭ ���ø��� �����մϴ�.
void MongSiri_Population::Init(unsigned int _Population)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	SetUpChubHole(CurLevel);
	GetHoleScale();
	ExploreSpawnLocation();
	CreateMongSiri(CurLevel, _Population);
}

// ������ ��ġ�մϴ�.
void MongSiri_Population::SetUpChubHole(GameEngineLevel* _CurLevel)
{
	m_ChubHole = _CurLevel->CreateActor<ChubHole>(EUPDATEORDER::Objects);
	if (nullptr == m_ChubHole)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
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

// ������ ũ�⸦ ���ɴϴ�.
void MongSiri_Population::GetHoleScale()
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("SquishychubHole.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ε����� ���߽��ϴ�.");
		return;
	}

	m_HoleScale = Texture->GetScale();
}

// ���ø��� ������ ��Ҹ� ã���ϴ�.
void MongSiri_Population::ExploreSpawnLocation()
{
	if (float4::ZERO == m_HoleScale)
	{
		MsgBoxAssert("������ 0�� �ؽ�ó�� ����� �� �����ϴ�.");
		return;
	}

	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("��� �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	CheckInstallationHoleSpace();
}

// ������ �°� ��ġ�Ǿ� �ִ��� �˻��մϴ�.
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
			MsgBoxAssert("���� �������� ��ġ�� �� �����ϴ�.");
			return;
		}
	}
}

// 1. �������κ��� �Ÿ�
// 2. �� �Ÿ����� ���� ���� �ȿ� ��ü�� Ȯ��
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
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
	// �õ弳�� 
	_RandomClass.SetSeed(reinterpret_cast<__int64>(_Actor.get()));

	float MongSiriSpawnDistance = _RandomClass.RandomFloat(0.0f, MonSiriSpawnRangeSize);		// ���� ���� �Ÿ� : 0 ~ 120.0f 
	float MongSiriSpawnAngle = _RandomClass.RandomFloat(0.0f, 360.0f);							// ���� ���� ����
	float4 MongSiriSpawnUnitVector = float4::GetUnitVectorFromDeg(MongSiriSpawnAngle);			// ���� ���� ����
	float4 MonSiriPosition = m_PopulationLocation + MongSiriSpawnUnitVector * MongSiriSpawnDistance;		// ���� ��ġ = ��ü�� ��ġ + �������� * ���� �Ÿ�

	// ����
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