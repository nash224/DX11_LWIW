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

// �̹����� 1�� �ִµ� �� �̹����� �߶� �������ϴ� 
void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	// �⺻�����ڰ� �ִ� �ڷ����� ���ο��� �����.
	// std::vector

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ��������Ʈ�� ������� �߽��ϴ�.");
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
		MsgBoxAssert("�ε����� �����ؼ� ��������Ʈ �����͸� ���������� �߽��ϴ�.");
		return SpriteData();
	}

	return SpriteDatas[_Index];
}