#include "PreCompile.h"
#include "MongSiri_Population.h"

#include "MongSiri.h"
#include "ChubHole.h"
#include "BackDrop_PlayLevel.h"

MongSiri_Population::MongSiri_Population() 
{
}

MongSiri_Population::~MongSiri_Population() 
{
}

void MongSiri_Population::Update(float _Delta)
{
	UpdateEntityMiddlePoint();
}

void MongSiri_Population::Release()
{

	MongSiriEntityList.clear();
	Hole = nullptr;
}

// _Population : ��ü����ŭ ���ø��� �����մϴ�.
void MongSiri_Population::Init(unsigned int _Population)
{
	SetUpChubHole();
	GetHoleScale();
	ExploreSpawnLocation();
	CreateMongSiri(_Population);
}

// ������ ��ġ�մϴ�.
void MongSiri_Population::SetUpChubHole()
{
	float4 CurrentPosition = Transform.GetLocalPosition();
	CurrentPosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Hole);

	Hole = GetLevel()->CreateActor<ChubHole>(EUPDATEORDER::Objects);
	Hole->Transform.SetLocalPosition(CurrentPosition);
	Hole->Init();
}

// ������ ũ�⸦ ���ɴϴ�.
void MongSiri_Population::GetHoleScale()
{
	const std::shared_ptr<GameEngineTexture>& Texture = GameEngineTexture::Find("SquishychubHole.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ε����� ���߽��ϴ�.");
		return;
	}

	HoleScale = Texture->GetScale();
}

// ���ø��� ������ ��Ҹ� ã���ϴ�.
void MongSiri_Population::ExploreSpawnLocation()
{
	if (float4::ZERO == HoleScale)
	{
		MsgBoxAssert("������ 0�� �ؽ�ó�� ����� �� �����ϴ�.");
		return;
	}

	CheckInstallationHoleSpace();
}

// ������ �°� ��ġ�Ǿ� �ִ��� �˻��մϴ�.
void MongSiri_Population::CheckInstallationHoleSpace()
{
	const float4 CurrentPosition = Transform.GetWorldPosition();
	const float4 HalfHoleScale = HoleScale.Half();

	for (int i = 0; i < 4; i++)
	{
		float4 CheckPoint;
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

		const std::shared_ptr<BackDrop_PlayLevel>& BackDropPtr = PlayLevel::GetCurLevel()->GetBackDropPtr();
		if (nullptr != BackDropPtr)
		{
			if (GameEngineColor::RED == BackDropPtr->GetColor(CheckPoint))
			{
				MsgBoxAssert("���� �������� ��ġ�� �� �����ϴ�.");
				return;
			}
		}
	}
}

// 1. �������κ��� �Ÿ�
// 2. �� �Ÿ����� ���� ���� �ȿ� ��ü�� Ȯ��
void MongSiri_Population::SetPopulationSpawnLocation(const float4& _Location)
{
	PopulationLocation = _Location;
}

void MongSiri_Population::CreateMongSiri(unsigned int _Population)
{
	GameEngineRandom RandomClass;

	for (unsigned int i = 0; i < _Population; i++)
	{
		std::shared_ptr<MongSiri> Object = GetLevel()->CreateActor<MongSiri>(EUPDATEORDER::Entity);
		SetMongSiriSeed(Object, RandomClass);
		Object->Init();
		Object->MongSiriParant = this;
		MongSiriEntityList.push_back(Object);
	}
}

void MongSiri_Population::SetMongSiriSeed(std::shared_ptr<MongSiri> _Actor, GameEngineRandom& _RandomClass)
{
	_RandomClass.SetSeed(GlobalValue::GetSeedValue());

	float MongSiriSpawnDistance = _RandomClass.RandomFloat(0.0f, MonSiriSpawnRangeSize);		// ���� ���� �Ÿ� : 0 ~ 120.0f 
	float MongSiriSpawnAngle = _RandomClass.RandomFloat(0.0f, 360.0f);							// ���� ���� ����
	float4 MongSiriSpawnUnitVector = float4::GetUnitVectorFromDeg(MongSiriSpawnAngle);			// ���� ���� ����
	float4 MonSiriPosition = PopulationLocation + MongSiriSpawnUnitVector * MongSiriSpawnDistance;		// ���� ��ġ = ��ü�� ��ġ + �������� * ���� �Ÿ�

	_Actor->Transform.SetLocalPosition(MonSiriPosition);
	_Actor->ApplyDepth();
}


void MongSiri_Population::UpdateEntityMiddlePoint()
{
	float4 MiddlePoint = float4::ZERO;

	for (std::shared_ptr<MongSiri> Entity : MongSiriEntityList)
	{
		MiddlePoint += Entity->Transform.GetLocalPosition();
	}

	MiddlePoint /= static_cast<float>(MongSiriEntityList.size());
	MiddlePoint = MiddlePoint;
}

void MongSiri_Population::EscapeHoleToOtherMonsiri()
{
	std::list<std::shared_ptr<MongSiri>>::iterator StarIter = MongSiriEntityList.begin();
	std::list<std::shared_ptr<MongSiri>>::iterator EndIter = MongSiriEntityList.end();

	for (;StarIter != EndIter; ++StarIter)
	{
		const std::shared_ptr<MongSiri>& Other = (*StarIter);
		if (nullptr == Other)
		{
			MsgBoxAssert("�������� �ʴ� ���ø��� �ֽ��ϴ�.");
			return;
		}

		if (Other->Status != EMONGSIRISTATUS::Escape)
		{
			Other->ShowEscapeEmotion();
		}

		Other->Status = EMONGSIRISTATUS::Escape;
	}
}


void MongSiri_Population::ActorRelaese()
{
	for (std::weak_ptr<MongSiri> Object : MongSiriEntityList)
	{
		Object.lock()->Death();
	}

	Hole->Death();
	Death();
}