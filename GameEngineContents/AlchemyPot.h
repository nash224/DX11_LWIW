#pragma once
#include "StaticEntity.h"

enum class EPOTSTATE
{
	None,
	Idle,
	Boil,
	Fail,
	Success
};

// Ό³Έν :
class AlchemyPot : public StaticEntity
{
public:
	// constrcuter destructer
	AlchemyPot();
	~AlchemyPot();

	// delete Function
	AlchemyPot(const AlchemyPot& _Other) = delete;
	AlchemyPot(AlchemyPot&& _Other) noexcept = delete;
	AlchemyPot& operator=(const AlchemyPot& _Other) = delete;
	AlchemyPot& operator=(AlchemyPot&& _Other) noexcept = delete;

	void StartAlchemyPot();

	void CreateRendererAndAnimation();
	void CreateInteractiveCollision();



protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_PotRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_WaterRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_FireRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> m_PotFxSteam;


private:
	EPOTSTATE m_State = EPOTSTATE::None;
};

