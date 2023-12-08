#include "PreCompile.h"
#include "ContentsSpriteRenderer.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>


ContentsSpriteRenderer::ContentsSpriteRenderer()
{
}

ContentsSpriteRenderer::~ContentsSpriteRenderer()
{
}

void ContentsSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	ImageTransform.SetParent(Transform);

	GameEngineRenderer::SetMesh("Rect");

}

// Update Order에 영향을 받는다.
void ContentsSpriteRenderer::Update(float _Delta)
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

void ContentsSpriteRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void ContentsSpriteRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}


void ContentsSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
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

void ContentsSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

void ContentsSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void ContentsSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

void ContentsSpriteRenderer::SetPivotType(PivotType _Type)
{
	switch (_Type)
	{
	case PivotType::Center:
		Pivot = { 0.5f, 0.5f };
		break;
	case PivotType::Top:
		Pivot = { 0.5f, 0.0f };
		break;
	case PivotType::RightUp:
		Pivot = { 0.0f, 0.0f };
		break;
	case PivotType::Right:
		Pivot = { 0.0f, 0.5f };
		break;
	case PivotType::RightBottom:
		Pivot = { 0.0f, 1.0f };
		break;
	case PivotType::Bottom:
		Pivot = { 0.5f, 1.0f };
		break;
	case PivotType::LeftBottom:
		Pivot = { 1.0f, 1.0f };
		break;
	case PivotType::Left:
		Pivot = { 1.0f, 0.5f };
		break;
	case PivotType::LeftTop:
		Pivot = { 1.0f, 0.0f };
		break;
	default:
		break;
	}
}

void ContentsSpriteRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);
	GetShaderResHelper().SetConstantBufferLink("ColorData", ColorDataValue);
	GetShaderResHelper().SetConstantBufferLink("TransparentInfo", TransparentData);
	SetSprite("NSet.png");
}


void ContentsSpriteRenderer::SetSampler(std::string_view _Name)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->ShaderResHelper.SetSampler("DiffuseTexSampler", _Name);
	IsUserSampler = false;
}