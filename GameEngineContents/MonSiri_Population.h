#pragma once

// Ό³Έν :
class MonSiri_Population : public GameEngineActor
{
public:
	// constrcuter destructer
	MonSiri_Population();
	~MonSiri_Population();

	// delete Function
	MonSiri_Population(const MonSiri_Population& _Other) = delete;
	MonSiri_Population(MonSiri_Population&& _Other) noexcept = delete;
	MonSiri_Population& operator=(const MonSiri_Population& _Other) = delete;
	MonSiri_Population& operator=(MonSiri_Population&& _Other) noexcept = delete;

	void Init(unsigned int _Population);

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


private:
	void SetUpChubHole(GameEngineLevel* _CurLevel);
	void CreateMongSiri(GameEngineLevel* _CurLevel, unsigned int _Population);


private:
	std::list<std::shared_ptr<class MongSiri>> MongSiriEntityList;
	std::shared_ptr<class ChubHole> m_ChubHole = nullptr;

};

