#pragma once
#include "DynamicEntity.h"


enum class EPUMPKINTERRIERSTATE
{
	Clear_Idle,
	Clear_Charm,
	Clear_DustOff,
	Vine_Idle,
	Vine_Paw,
	Vine_Run,
	Vine_Gasp,
	Vine_Disappear,
	None,
};


// Ό³Έν :
class PumpkinTerrier : public DynamicEntity
{
public:
	// constrcuter destructer
	PumpkinTerrier();
	~PumpkinTerrier();

	// delete Function
	PumpkinTerrier(const PumpkinTerrier& _Other) = delete;
	PumpkinTerrier(PumpkinTerrier&& _Other) noexcept = delete;
	PumpkinTerrier& operator=(const PumpkinTerrier& _Other) = delete;
	PumpkinTerrier& operator=(PumpkinTerrier&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShadowRenderer = nullptr;

	
	const float RendererBias = 60.0f;

};

