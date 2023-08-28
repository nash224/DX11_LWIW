#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
	return Texture->GetScale();
}

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

// 이미지가 1장 있는데 그 이미지를 잘라서 랜더링하는 
void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	// 기본생성자가 있는 자료형은 내부에서 만든다.
	// std::vector

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 스프라이트를 만들려고 했습니다.");
		return;
	}

	SpriteDatas.resize(_X * _Y);

	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{
			unsigned int index = (y * _X) + x;
			SpriteDatas[index].Texture = Texture;
			// GameEngineSpriteData[index].SpriteData = 
		}
	}


	// GameEngineTexture::Find(_Name);


}

const SpriteData& GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		MsgBoxAssert("인덱스를 오버해서 스프라이트 데이터를 가져오려고 했습니다.");
		return SpriteData();
	}

	return SpriteDatas[_Index];
}