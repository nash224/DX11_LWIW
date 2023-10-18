#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class SilverStarFlower : public StaticEntity
{
public:
	// constrcuter destructer
	SilverStarFlower();
	~SilverStarFlower();

	// delete Function
	SilverStarFlower(const SilverStarFlower& _Other) = delete;
	SilverStarFlower(SilverStarFlower&& _Other) noexcept = delete;
	SilverStarFlower& operator=(const SilverStarFlower& _Other) = delete;
	SilverStarFlower& operator=(SilverStarFlower&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Plant = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;


	float m_RendererBias = 36.0f;
};

