#pragma once
#include "BaseLift.h"

// Ό³Έν :
class LowerLiftA : public BaseLift
{
public:
	// constrcuter destructer
	LowerLiftA();
	~LowerLiftA();

	// delete Function
	LowerLiftA(const LowerLiftA& _Other) = delete;
	LowerLiftA(LowerLiftA&& _Other) noexcept = delete;
	LowerLiftA& operator=(const LowerLiftA& _Other) = delete;
	LowerLiftA& operator=(LowerLiftA&& _Other) noexcept = delete;

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
	void CheckFindWorkPlaceEvent();
	void ShowFindWorkPlaceEvent();

};