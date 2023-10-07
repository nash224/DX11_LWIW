#pragma once
#include "DynamicEntity.h"

// Ό³Έν :
class MongSiri : public DynamicEntity
{
	friend class MongSiri_Population;

private:
	class MonSiri_Population* MongSiriParant = nullptr;

public:
	// constrcuter destructer
	MongSiri();
	~MongSiri();

	// delete Function
	MongSiri(const MongSiri& _Other) = delete;
	MongSiri(MongSiri&& _Other) noexcept = delete;
	MongSiri& operator=(const MongSiri& _Other) = delete;
	MongSiri& operator=(MongSiri&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateAndSetRenderer();

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Body = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> m_Shadow = nullptr;

};

