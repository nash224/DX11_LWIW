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
		MsgBoxAssert("지정해둔 파일이 없습니다.");
		return GameEngineColor();
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return GameEngineColor();
	}

	float4 HalfTexturePos = Texture->GetScale().Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = _MyPosition + HalfTexturePos;

	float4 CheckPos = _CheckPosition - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}