#pragma once
#include "StaticEntity.h"

enum class BushType
{
	Bush,
	BushBug,
	BushApple,
	None,
};



// Ό³Έν :
class Bush : public StaticEntity
{
public:
	// constrcuter destructer
	Bush();
	~Bush();

	// delete Function
	Bush(const Bush& _Other) = delete;
	Bush(Bush&& _Other) noexcept = delete;
	Bush& operator=(const Bush& _Other) = delete;
	Bush& operator=(Bush&& _Other) noexcept = delete;


	void SetBushType(BushType _Type);
	void Init();


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateBushAnimation();


private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Bush = nullptr;

private:
	BushType m_BushType = BushType::None;

	float DepthBias = 0.0f;
};

