#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class Aurea : public StaticEntity
{
public:
	// constrcuter destructer
	Aurea();
	~Aurea();

	// delete Function
	Aurea(const Aurea& _Other) = delete;
	Aurea(Aurea&& _Other) noexcept = delete;
	Aurea& operator=(const Aurea& _Other) = delete;
	Aurea& operator=(Aurea&& _Other) noexcept = delete;

	void Init();
	void RendererSetting();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_MerchantCreature = nullptr;

	float m_RendererBias = 30.0f;

};

