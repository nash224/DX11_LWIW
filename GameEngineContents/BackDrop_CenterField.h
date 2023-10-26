#pragma once
#include "BackDrop_PlayLevel.h"

// Ό³Έν :
class BackDrop_CenterField : public BackDrop_PlayLevel
{
public:
	// constrcuter destructer
	BackDrop_CenterField();
	~BackDrop_CenterField();

	// delete Function
	BackDrop_CenterField(const BackDrop_CenterField& _Other) = delete;
	BackDrop_CenterField(BackDrop_CenterField&& _Other) noexcept = delete;
	BackDrop_CenterField& operator=(const BackDrop_CenterField& _Other) = delete;
	BackDrop_CenterField& operator=(BackDrop_CenterField&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	void Init();
	void TestPorp();

	void CreateFlooring();
	void CreateProp(GameEngineLevel* _Level);
	void CreatePixelMap(GameEngineLevel* _Level);
	void CreatePortalActor(GameEngineLevel* _Level);
	void CreateAurea(GameEngineLevel* _Level);

	void CreateCreature(GameEngineLevel* _Level);
	void CreateDayNightTimeCreature(GameEngineLevel* _Level);
	void CreateDayTimeCreature(GameEngineLevel* _Level);
	void CreateNightCreature(GameEngineLevel* _Level);

	void CreateBush(GameEngineLevel* _Level);
	void CreateWitchFlower(GameEngineLevel* _Level);
	void CreateSilverStarFlower(GameEngineLevel* _Level);
	void CreateBranchTree(GameEngineLevel* _Level);
	void CreateMongSiriPopulation(GameEngineLevel* _Level);
	void CreateFlowerBird(GameEngineLevel* _Level);
	void CreatePumpkinTerrier(GameEngineLevel* _Level);


	void PopulationRelease();

private:
	std::vector<std::shared_ptr<class MongSiri_Population>> PopulationVec;


};

