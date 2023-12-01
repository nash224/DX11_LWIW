#include "PreCompile.h"
#include "CometSpawner.h"
#include "Comet.h"

CometSpawner::CometSpawner() 
{
}

CometSpawner::~CometSpawner() 
{
}

void CometSpawner::Start()
{
	SetSpawnOrder(EUPDATEORDER::Objects);
}

void CometSpawner::Update(float _Delta)
{
	static constexpr float SpawnMinTime = 0.8f;
	static constexpr float SpawnMaxTime = 1.2f;

	SpawnTime -= _Delta;
	if (SpawnTime < 0.0f)
	{
		SpawnTime = RandomFunction::GetRandomfValue(SpawnMinTime, SpawnMaxTime);
		Spawn();
	}
}

void CometSpawner::LevelStart(class GameEngineLevel* _NextLevel)
{
	if (nullptr == GameEngineSprite::Find("Title_comet"))
	{
		GameEnginePath path;
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\Main\\Train\\Title_comet");
		GameEngineSprite::CreateFolder(path.GetStringPath());
	}
}


void CometSpawner::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();

	GameEngineSprite::Release("Title_comet");

	FileLoadFunction::ReleaseAllTextureInPath("Resources\\Main\\Train\\Title_comet");
}


void CometSpawner::Spawn()
{
	const float YCorrection = 40.0f;

	const float Depth = DepthFunction::CalculateFixDepth(ETITLERENDERDEPTH::Comet);
	const float SpawnXPos = RandomFunction::GetRandomfValue(0.0f, GlobalValue::GetWindowScale().X);

	std::shared_ptr<Comet> comet = GetLevel()->CreateActor<Comet>(GetSpawnOrder());
	comet->Transform.SetLocalPosition(float4(SpawnXPos + YCorrection, 0.0f, Depth));
}