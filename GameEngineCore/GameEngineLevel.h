#pragma once
#include "GameEngineObject.h"

// 설명 :
// class GameEngineActor; 이래도되고
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:
	// LevelChange가 벌어질때
	// 내가 다음 레벨이면 LevelStart
	// 내가 그럼 End
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	// 액터관련 기능들
	void AllUpdate(float _Delta) override;

	void Render(float _Delta);

	void ActorRelease();

	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;

	//// 그냥 
	// std::map<int, std::list<std::shared_ptr<class GameEngineActor>>> AllActors;
};

