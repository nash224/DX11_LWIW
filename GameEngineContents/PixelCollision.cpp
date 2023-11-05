#include "PreCompile.h"
#include "PixelCollision.h"

PixelCollision::PixelCollision() 
{
}

PixelCollision::~PixelCollision() 
{
}


void PixelCollision::SetPixelFileName(std::string_view _FileName)
{
	PixelFileName = _FileName;
}

std::string PixelCollision::GetPixelFileName() const
{
	return PixelFileName;
}

GameEngineColor PixelCollision::GetColor(const float4& _CheckPosition, const float4& _MyPosition, GameEngineColor _DefaultColor /*= GameEngineColor::WHITE*/)
{
	if ("" == PixelFileName)
	{
		MsgBoxAssert("�����ص� ������ �����ϴ�.");
		return GameEngineColor();
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return GameEngineColor();
	}

	float4 HalfTexturePos = Texture->GetScale().Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = _MyPosition + HalfTexturePos;

	float4 CheckPos = _CheckPosition - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}