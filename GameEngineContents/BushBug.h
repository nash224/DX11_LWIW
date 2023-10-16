#pragma once
#include "DynamicEntity.h"


enum class EBUSHBUGSTATE
{
	Idle,
	Move,
	None,
};


// Ό³Έν :
class BushBug : public DynamicEntity
{
public:
	// constrcuter destructer
	BushBug();
	~BushBug();

	// delete Function
	BushBug(const BushBug& _Other) = delete;
	BushBug(BushBug&& _Other) noexcept = delete;
	BushBug& operator=(const BushBug& _Other) = delete;
	BushBug& operator=(BushBug&& _Other) noexcept = delete;

	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void AnimationSetting();

private:
	void UpdateState(float _Delta);
	void ChangeState();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;
	
};

