#pragma once
#include "InteractiveActor.h"

#include "PixelCollision.h"


// Ό³Έν :
class StaticEntity : public InteractiveActor
{
	friend class PlayLevel;

public:
	// constrcuter destructer
	StaticEntity();
	~StaticEntity();

	// delete Function
	StaticEntity(const StaticEntity& _Other) = delete;
	StaticEntity(StaticEntity&& _Other) noexcept = delete;
	StaticEntity& operator=(const StaticEntity& _Other) = delete;
	StaticEntity& operator=(StaticEntity&& _Other) noexcept = delete;

	bool GetPixelCheck();
	void SetPixelCollision(std::string_view _FileName);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = GameEngineColor::WHITE);


protected:
	void Start() override {}
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override{}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	std::shared_ptr<PixelCollision> PixelCol;
	std::shared_ptr<GameEngineSpriteRenderer> PixelRenderer;

	bool isPixelSet = false;

};

