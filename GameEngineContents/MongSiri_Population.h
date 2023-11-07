#pragma once

// 설명 :
class MongSiri_Population : public GameEngineActor
{
	friend class MongSiri;

public:
	// constrcuter destructer
	MongSiri_Population();
	~MongSiri_Population();

	// delete Function
	MongSiri_Population(const MongSiri_Population& _Other) = delete;
	MongSiri_Population(MongSiri_Population&& _Other) noexcept = delete;
	MongSiri_Population& operator=(const MongSiri_Population& _Other) = delete;
	MongSiri_Population& operator=(MongSiri_Population&& _Other) noexcept = delete;

	void Init(unsigned int _Population);
	void SetPopulationSpawnLocation(const float4& _Location);

	void EscapeHoleToOtherMonsiri();

	void ActorRelaese();

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void GetHoleScale();
	void ExploreSpawnLocation();
	void CheckInstallationHoleSpace();
	void SetUpChubHole(GameEngineLevel* _CurLevel);
	void CreateMongSiri(GameEngineLevel* _CurLevel, unsigned int _Population);
	void SetMongSiriSeed(std::shared_ptr<class MongSiri> _Actor, GameEngineRandom& _RandomClass);

private:
	void UpdateEntityMiddlePoint();

private:
	std::list<std::shared_ptr<class MongSiri>> MongSiriEntityList;
	std::shared_ptr<class ChubHole> m_ChubHole = nullptr;

	float4 m_MiddlePoint = float4::ZERO;
	float4 m_HoleScale = float4::ZERO;
	float4 m_PopulationLocation = float4::ZERO;

	const float MonSiriSpawnRangeSize = 80.0f;			// 몽시리 설치범위
	const float m_PopulationMinCircle = 60.0f;
	const float m_PopulationMaxCircle = 120.0f;

};

