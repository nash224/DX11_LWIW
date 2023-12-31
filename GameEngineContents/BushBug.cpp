#include "PreCompile.h"
#include "BushBug.h"

#include "BackDrop_PlayLevel.h"
#include "UI_Inventory.h"


static constexpr float Max_YAngle = 5.0f;
static constexpr float Move_Range = 50.0f;
static constexpr float MoveSpeed = 16.0f;

BushBug::BushBug() 
{
	if (nullptr == GameEngineSound::FindSound("SFX_BushBug_Fly.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Sound\\Actor\\BushBug");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pfile : Files)
		{
			GameEngineSound::SoundLoad(pfile.GetStringPath());
		}
	}
}

BushBug::~BushBug() 
{
}


void BushBug::Start()
{
	InteractiveActor::CreateAndSetCollision(ECOLLISION::Entity, { 200.0f }, float4::ZERO, ColType::SPHERE2D);
	InteractiveActor::SetInteractionOption(EINTERACTION_BUTTONTYPE::Gathering, EAPPROACH_TYPE::None, EINTERACTIONTYPE::None, ETOOLTYPE::Dragonfly);
}

void BushBug::Update(float _Delta)
{
	InteractiveActor::Update(_Delta);

	MainState.Update(_Delta);
	Alight.UpdateLightLerp();
	InteractiveActor::UpdateSoundVolumeByDistance();
}

void BushBug::Release()
{
	InteractiveActor::Release();

	Alight.Release();
}

void BushBug::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void BushBug::Init()
{
	AnimationSetting();
	StateSetting();
	ALightSetting();

	SpawnPosition = Transform.GetLocalPosition();
}

void BushBug::AnimationSetting()
{
	if (nullptr == GameEngineSprite::Find("Bushbug_Standing.png"))
	{
		GameEngineSprite::CreateCut("Bushbug_Standing.png", 4, 3);
	}

	InteractiveActor::BodyRenderer = CreateComponent<GameEngineSpriteRenderer>();
	InteractiveActor::BodyRenderer->AutoSpriteSizeOn();
	InteractiveActor::BodyRenderer->CreateAnimation("Idle", "Bushbug_Standing.png", 0.1f, 2, 9, true);
	InteractiveActor::BodyRenderer->ChangeAnimation("Idle");

	ShadowRenderer = CreateComponent<GameEngineSpriteRenderer>();
	ShadowRenderer->SetSprite("Bushbug_Standing.png", 1);
	ShadowRenderer->Transform.SetLocalPosition(float4(0.0f , 0.0f, DepthFunction::CalculateFixDepth(ERENDERDEPTH::ObjectShadow) ));
}

void BushBug::ALightSetting()
{
	Alight.Init(this, { float4(0.1f, 0.1f, 0.0f, 0.8f) , "Default_Particle.png" , float4(100.0f, 100.0f)});

	const std::shared_ptr<GameEngineFrameAnimation>& Animation = BodyRenderer->FindAnimation("Idle");
	if (nullptr == Animation)
	{
		MsgBoxAssert("애니메이션을 찾지 못했습니다.");
		return;
	}

	BodyRenderer->SetFrameEvent("Idle",2,[&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 19.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 3, [&](GameEngineSpriteRenderer* _Renderer)
		{
			SoundPlayer = SFXFunction::PlaySFX("SFX_BushBug_Fly.wav");
			Alight.SetPosition(float4(-3.0f, 17.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 4, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 17.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 5, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 19.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 6, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 23.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 7, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 25.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 25.0f, -0.01f));
		});
	BodyRenderer->SetFrameEvent("Idle", 9, [&](GameEngineSpriteRenderer* _Renderer)
		{
			Alight.SetPosition(float4(-3.0f, 21.0f, -0.01f));
		});
}

void BushBug::StateSetting()
{
	CreateStateParameter Para;
	Para.Start = std::bind(&BushBug::StartMove, this, std::placeholders::_1);
	Para.Stay = std::bind(&BushBug::UpdateMove, this, std::placeholders::_1, std::placeholders::_2);
	MainState.CreateState(0, Para);
	MainState.ChangeState(0);

}

void BushBug::StartMove(GameEngineState* _Parent)
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());
	float FlyAngle = RandomClass.RandomFloat(0.0f, Max_YAngle);
	if (0 == RandomClass.RandomInt(0, 1))
	{
		FlyAngle *= -1.0f;
	}
	float4 UnitVector = float4::GetUnitVectorFromDeg(FlyAngle);
	SetMoveVector(UnitVector * MoveSpeed);
}

void BushBug::UpdateMove(float _Delta, GameEngineState* _Parent)
{
	if (true == IsEnalbeActive)
	{
		UI_Inventory::PushItem("BushBug_Collect");

		Death();
	}

	const float4 CheckDistance = SpawnPosition - Transform.GetLocalPosition();
	const float4 DistanceToSpawn = DirectX::XMVector2Length(CheckDistance.DirectXVector);
	if (DistanceToSpawn.X > Move_Range)
	{
		SearchFlyDirection();
	}

	ApplyMovement(_Delta);
}

void BushBug::SearchFlyDirection()
{
	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GlobalValue::GetSeedValue());

	const float4 TargetVector = SpawnPosition - Transform.GetLocalPosition();
	const float DegreeToTarget = DirectX::XMConvertToDegrees(atan2f(TargetVector.Y, TargetVector.X));

	float FlyAngle = static_cast<float>(pow(RandomClass.RandomFloat(0.0f, 1.0f), 2));
	FlyAngle *= Max_YAngle;

	if (1 == RandomClass.RandomInt(0, 1))
	{
		FlyAngle *= -1.0f;
	}

	FlyAngle = DegreeToTarget + FlyAngle;

	const float4 TargetUnitVector = float4::GetUnitVectorFromDeg(FlyAngle);
	SetMoveVector(TargetUnitVector * MoveSpeed);
}