#pragma once
#include "BaseLift.h"

class UpperLiftEvent : public GameEngineActor
{
public:
	// constrcuter destructer
	UpperLiftEvent() {}
	~UpperLiftEvent() {}

	// delete Function
	UpperLiftEvent(const UpperLiftEvent& _Other) = delete;
	UpperLiftEvent(UpperLiftEvent&& _Other) noexcept = delete;
	UpperLiftEvent& operator=(const UpperLiftEvent& _Other) = delete;
	UpperLiftEvent& operator=(UpperLiftEvent&& _Other) noexcept = delete;

	void Init();
	
protected:
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> FloorRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> WallRenderer;


};

// Ό³Έν :
class UpperLiftA : public BaseLift
{
public:
	// constrcuter destructer
	UpperLiftA();
	~UpperLiftA();

	// delete Function
	UpperLiftA(const UpperLiftA& _Other) = delete;
	UpperLiftA(UpperLiftA&& _Other) noexcept = delete;
	UpperLiftA& operator=(const UpperLiftA& _Other) = delete;
	UpperLiftA& operator=(UpperLiftA&& _Other) noexcept = delete;

	void Init() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	virtual void StartEnter(GameEngineState* _Parent);
	virtual void StartArrive(GameEngineState* _Parent);
	virtual void EndEnter(GameEngineState* _Parent);
	virtual void EndArrive(GameEngineState* _Parent);

private:
	std::weak_ptr<UpperLiftEvent> HideFloor;

};

