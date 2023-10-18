#pragma once
#include "BackDrop.h"

// Ό³Έν :
class BackDrop_Loading : public BackDrop
{
public:
	// constrcuter destructer
	BackDrop_Loading();
	~BackDrop_Loading();

	// delete Function
	BackDrop_Loading(const BackDrop_Loading& _Other) = delete;
	BackDrop_Loading(BackDrop_Loading&& _Other) noexcept = delete;
	BackDrop_Loading& operator=(const BackDrop_Loading& _Other) = delete;
	BackDrop_Loading& operator=(BackDrop_Loading&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	void Init();


private:
	void CreateProp(GameEngineLevel* _Level);


public:
	void ActorRelease();



};

