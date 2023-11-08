#pragma once
#include "DynamicEntity.h"

// Ό³Έν :
class SilverStarPollen : public DynamicEntity
{
public:
	// constrcuter destructer
	SilverStarPollen();
	~SilverStarPollen();

	// delete Function
	SilverStarPollen(const SilverStarPollen& _Other) = delete;
	SilverStarPollen(SilverStarPollen&& _Other) noexcept = delete;
	SilverStarPollen& operator=(const SilverStarPollen& _Other) = delete;
	SilverStarPollen& operator=(SilverStarPollen&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void RendererSetting();

	void UpdateState(float _Delta);
	void UpdateMovement(float _Delta);

private:
	

	static constexpr const float RenderYCorrection = 30.0f;
	static constexpr const float MovementRadius = 80.0f;

};

