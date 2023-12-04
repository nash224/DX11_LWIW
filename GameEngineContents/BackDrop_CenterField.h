#pragma once
#include "BackDrop_Field.h"


// Ό³Έν :
class BackDrop_CenterField : public BackDrop_Field
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


	void RenewMap();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void CreateCreatureWhenDayChange() override;
	void DisappearDayCreature() override;
	void AppearNightCreature() override;
	void ReleaseAllCreature() override;

protected:
	void CreateMap();
	void LoadSerBin();
	void CreatePortalActor();
	void NPCSetting();

	void CheckFireWorksEvent();
	void ShowFireWorksEvent();

};

