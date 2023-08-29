#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	// 스프라이트는 기본적으로 
	void SetSprite(std::string_view _Name, unsigned int index = 0);

protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	int Index = 0;

private:
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
};

