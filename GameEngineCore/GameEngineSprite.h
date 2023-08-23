#pragma once
#include "GameEngineTexture.h"


// 이미지를 자른다는 개념을 가지거나 할수 있는 녀석이다.

// 자르는 기능은 만들지 않겠다.
class SpriteData
{
	std::shared_ptr<GameEngineTexture> Texture;
};

// 설명 :
class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	// 폴더 위치 알려주면
	// 폴더 위치내부의 텍스처를 전부다 로드해서 스프라이트로 만든다.
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

protected:

private:
	std::vector<SpriteData> GameEngineSpriteData;
};

