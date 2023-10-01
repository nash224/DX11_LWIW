#pragma once
#include "BackDrop.h"

// Ό³Έν :
class BackDrop_CenterField : public BackDrop
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


public:
	void Init();

	void CreateProp(GameEngineLevel* _Level);
	void CreatePixelMap(GameEngineLevel* _Level);
	void CreatePortalActor(GameEngineLevel* _Level);

public:
	void ActorRelease();

private:

};

