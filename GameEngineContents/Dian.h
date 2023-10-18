#pragma once
#include "StaticEntity.h"

// Ό³Έν :
class Dian : public StaticEntity
{
public:
	// constrcuter destructer
	Dian();
	~Dian();

	// delete Function
	Dian(const Dian& _Other) = delete;
	Dian(Dian&& _Other) noexcept = delete;
	Dian& operator=(const Dian& _Other) = delete;
	Dian& operator=(Dian&& _Other) noexcept = delete;

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

	float m_RendererBias = 30.0f;

};

