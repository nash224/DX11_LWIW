#include "PreCompile.h"
#include "PixelCollision.h"

PixelCollision::PixelCollision() 
{
}

PixelCollision::~PixelCollision() 
{
}


GameEngineColor PixelCollision::GetColor(const float4& _CheckPosition, const float4& _MyPosition, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	if (true == PixelFileName.empty())
	{
		MsgBoxAssert("�����ص� ������ �����ϴ�.");
		return GameEngineColor();
	}

	const std::shared_ptr<GameEngineTexture>& Texture = GameEngineTexture::Find(PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return GameEngineColor();
	}

	float4 HalfTexturePos = Texture->GetScale().Half();
	HalfTexturePos.X *= -1.0f;

	const float4 MoveCheckPos = _MyPosition + HalfTexturePos;

	float4 CheckPos = _CheckPosition - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}