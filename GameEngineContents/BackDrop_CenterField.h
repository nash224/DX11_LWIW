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


	void Init();

protected:
	void Start() override {}
	void Update(float _Delta) override {}
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

protected:
	void SpriteFileLoad();

	void CreateMap();
	void LoadSerBin();
	void CreatePortalActor();
	void CreateAurea();

	void CreateCreature();
	void CreateDayNightTimeCreature();
	void CreateDayTimeCreature();

	void CreateBush();
	void CreateWitchFlower();
	void CreateSilverStarFlower();
	void CreateBranchTree();
	void CreateMongSiriPopulation();
	void CreateFlowerBird();
	void CreatePumpkinTerrier();


	void PopulationRelease();

private:

};

