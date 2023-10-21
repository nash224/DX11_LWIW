#include "PreCompile.h"
#include "BushBug.h"

#include "BackDrop_PlayLevel.h"

BushBug::BushBug() 
{
}

BushBug::~BushBug() 
{
}


void BushBug::Start()
{
	CreateAndSetCollision(ECOLLISION::Entity, { 200.0f }, float4::ZERO, ColType::SPHERE2D);
	SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EINTERACTION_TYPE::Far, ECOLLECTION_METHOD::None, ETOOLTYPE::Dragonfly);
}

void BushBug::Update(float _Delta)
{
	DynamicEntity::Update(_Delta);

	MoveState.Update(_Delta);
}

void BushBug::Release()
{
	m_Body = nullptr;
	m_InteractiveCol = nullptr;
}

void BushBug::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void BushBug::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void BushBug::Init()
{
	AnimationSetting();
	StateSetting();

	SpawnPosition = Transform.GetLocalPosition();
	SpawnPosition.Z = 0.0f;
}

void BushBug::AnimationSetting()
{
	if (nullptr == GameEngineSprite::Find("Bushbug_Standing.png"))
	{
		GameEngineSprite::CreateCut("Bushbug_Standing.png", 4, 3);
	}

	m_Body = CreateComponent<GameEngineSpriteRenderer>();
	m_Body->AutoSpriteSizeOn();
	m_Body->Transform.SetLocalPosition(float4( 0.0f, 12.0f));
	m_Body->CreateAnimation("Idle", "Bushbug_Standing.png", 0.1f, 2, 9, true);
	m_Body->ChangeAnimation("Idle");

	m_Shadow = CreateComponent<GameEngineSpriteRenderer>();
	m_Shadow->SetSprite("Bushbug_Standing.png", 1);
	m_Shadow->Transform.SetLocalPosition(float4(0.0f , -7.0f, GlobalUtils::CalculateDepth(ERENDERDEPTH::ObjectShadow) ));
}

void BushBug::StateSetting()
{
	CreateStateParameter Para;
	Para.Start = std::bind(&BushBug::StartMove, this, std::placeholders::_1);
	Para.Stay = std::bind(&BushBug::UPdateMove, this, std::placeholders::_1, std::placeholders::_2);
	MoveState.CreateState(0, Para);
	MoveState.ChangeState(0);

}

void BushBug::StartMove(GameEngineState* _Parent)
{
	// 시작하기 전 이동 방향을 구함
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());
	float FlyAngle = RandomClass.RandomFloat(0.0f, BUSHBUG_MAX_YANGLE);
	if (0 == RandomClass.RandomFloat(0, 1))
	{
		FlyAngle *= -1.0f;
	}
	float4 UnitVector = float4::GetUnitVectorFromDeg(FlyAngle);
	m_MoveVector = UnitVector * BUSHBUG_SPEED;
}

void BushBug::UPdateMove(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		if (nullptr == BackDrop_PlayLevel::MainBackDrop)
		{
			MsgBoxAssert("배경매니저가 존재하지 않습니다.");
			return;
		}

		BackDrop_PlayLevel::MainBackDrop->CreateItem("BushBug_Collect");

		Death();
	}

	// 범위를 넘어가면
	float4 MyPosition = Transform.GetLocalPosition();
	float4 CheckDistance = SpawnPosition - MyPosition;
	CheckDistance.Z = 0.0f;
	float DistanceUntilSpawn = CheckDistance.Size();
	if (DistanceUntilSpawn > BUSHBUG_MOVE_RANGE)
	{
		// 이동할 방향을 찾음
		SearchFlyDirection();
	}

	ApplyMovement(_Delta);
}

void BushBug::SearchFlyDirection()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(reinterpret_cast<__int64>(this) + GlobalValue::GetSeedValue());

	float4 MyPosition = Transform.GetLocalPosition();
	float4 TargetVector = SpawnPosition - MyPosition;
	TargetVector.Z = 0.0f;
	TargetVector = TargetVector.NormalizeReturn();
	float Degree = TargetVector.Angle2DDeg();
	if (SpawnPosition.Y - MyPosition.Y < 0.0f)
	{
		Degree = 180.0f - Degree;
		Degree += 180.0f;
	}

	float DirChangeRatio = RandomClass.RandomFloat(0.0f, 1.0f);
	float FlyAngle = static_cast<float>(pow(DirChangeRatio, 2));
	FlyAngle *= BUSHBUG_MAX_YANGLE;
	int MultiValue = RandomClass.RandomInt(0, 1);
	if (1 == MultiValue)
	{
		FlyAngle *= -1.0f;
	}

	m_FlyAngle = Degree + FlyAngle;

	if (m_FlyAngle > 360.0f)
	{
		m_FlyAngle -= 360.0f;
	}

	if (m_FlyAngle < 0.0f)
	{
		m_FlyAngle += 360.0f;
	}

	float4 TargetUnitVector = float4::GetUnitVectorFromDeg(m_FlyAngle);

	m_MoveVector = TargetUnitVector * BUSHBUG_SPEED;
}