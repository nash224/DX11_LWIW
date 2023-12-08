#include "PreCompile.h"
#include "GaugeRenderer.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>


GaugeRenderer::GaugeRenderer()
{
}

GaugeRenderer::~GaugeRenderer()
{
}

void GaugeRenderer::Start()
{
	GameEngineRenderer::Start();

	ImageTransform.SetParent(Transform);

	GameEngineRenderer::SetMesh("Rect");

}

void GaugeRenderer::Update(float _Delta)
{
	if (true == IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		SetImageScale(Scale * AutoScaleRatio);
	}

	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();
}

void GaugeRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void GaugeRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}


void GaugeRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	float4 ParentScale = Transform.GetLocalScale();
	float4 Scale = ImageTransform.GetLocalScale();

	float4 CalPivot = Pivot;
	CalPivot.X -= 0.5f;
	CalPivot.Y -= 0.5f;

	float4 PivotPos;
	PivotPos.X = Scale.X * CalPivot.X;
	PivotPos.Y = Scale.Y * CalPivot.Y;

	ImageTransform.SetLocalPosition(PivotPos);

	ImageTransform.TransformUpdate();
	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture, IsUserSampler);

	GameEngineRenderer::Render(_Camera, _Delta);

}

void GaugeRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

void GaugeRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GaugeRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

void GaugeRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	GetShaderResHelper().SetConstantBufferLink("GaugeInfo", GaugeInfoValue);
	SetSprite("NSet.png");
}