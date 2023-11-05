#include "PreCompile.h"
#include "ContentsRenderer.h"


void ContentsFrameAnimation::EventCall(int _Frame)
{
	if (true == FrameEventFunction.contains(Index[_Frame]))
	{
		FrameEventFunction[Index[_Frame]](Parent);
	}
}

void ContentsFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
	IsEnd = false;
	EventCheck = true;
}

SpriteData ContentsFrameAnimation::Update(float _DeltaTime)
{
	if (true == Parent->IsPause)
	{
		return Sprite->GetSpriteData(Index[CurIndex]);
	}

	if (true == Loop)
	{
		IsEnd = false;
	}

	if (true == EventCheck && false == IsEnd)
	{
		EventCall(CurIndex);
		EventCheck = false;
	}

	CurTime += _DeltaTime;

	if (Inter[CurIndex] <= CurTime)
	{
		CurTime -= Inter[CurIndex];
		++CurIndex;

		if (nullptr != FrameChangeFunction)
		{
			SpriteData Data = Sprite->GetSpriteData(Index[CurIndex]);
			FrameChangeFunction(Data, CurIndex);
		}

		EventCheck = true;

		if (CurIndex > InterIndex)
		{
			if (nullptr != EndEvent && false == IsEnd)
			{
				EndEvent(Parent);
			}

			IsEnd = true;

			if (true == Loop)
			{
				CurIndex = 0;
			}
			else
			{
				--CurIndex;
			}
		}
	}

	return Sprite->GetSpriteData(Index[CurIndex]);
}

ContentsRenderer::ContentsRenderer()
{
}

ContentsRenderer::~ContentsRenderer()
{
}

void ContentsRenderer::Start()
{
	GameEngineRenderer::Start();

	ImageTransform.SetParent(Transform);

	GameEngineRenderer::SetMesh("Rect");
	GameEngineRenderer::SetMaterial("2DTexture");
}

// Update Order�� ������ �޴´�.
void ContentsRenderer::Update(float _Delta)
{
	if (nullptr != CurFrameAnimations)
	{
		Sprite = CurFrameAnimations->Sprite;
		CurSprite = CurFrameAnimations->Update(_Delta);
	}

	if (true == IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		SetImageScale(Scale * AutoScaleRatio);
	}

	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();
	// 
}

void ContentsRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void ContentsRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}


void ContentsRenderer::Render(GameEngineCamera* _Camera, float _Delta)
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

void ContentsRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	CurFrameAnimations = nullptr;

	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

void ContentsRenderer::ChangeCurSprite(int _Index)
{
	CurFrameAnimations = nullptr;

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(_Index);
}

void ContentsRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	std::string SpriteName = GameEngineString::ToUpperReturn(_SpriteName);

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (true == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<ContentsFrameAnimation> NewAnimation = std::make_shared<ContentsFrameAnimation>();
	FrameAnimations[UpperName] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;

	NewAnimation->Parent = this;

	if (_Start != -1)
	{
		NewAnimation->Start = _Start;
	}
	else
	{
		NewAnimation->Start = 0;
	}

	if (_End != -1)
	{
		NewAnimation->End = _End;
	}
	else
	{
		NewAnimation->End = Sprite->GetSpriteCount() - 1;
	}

	int Plus = 1;

	if (NewAnimation->Start > NewAnimation->End)
	{
		for (
			int i = NewAnimation->Start;
			i >= NewAnimation->End;
			i--
			)
		{
			NewAnimation->Index.push_back(i);
		}

		NewAnimation->InterIndex = NewAnimation->Start - NewAnimation->End;
	}
	else
	{
		for (int i = NewAnimation->Start; i <= NewAnimation->End; i++)
		{
			NewAnimation->Index.push_back(i);
		}

		NewAnimation->InterIndex = NewAnimation->End - NewAnimation->Start;
	}

	NewAnimation->Inter.resize(NewAnimation->Index.size());
	for (size_t i = 0; i < NewAnimation->Index.size(); i++)
	{
		NewAnimation->Inter[i] = _Inter;
	}



	NewAnimation->CurIndex = 0;
}

void ContentsRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/, unsigned int _FrameIndex /*= 0*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>>::iterator FindIter
		= FrameAnimations.find(UpperName);

	if (FindIter == FrameAnimations.end())
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (_Force == false && FindIter->second == CurFrameAnimations)
	{
		return;
	}

	CurFrameAnimations = FrameAnimations[UpperName];
	CurFrameAnimations->Reset();
	CurFrameAnimations->CurIndex = _FrameIndex;
	Sprite = CurFrameAnimations->Sprite;
	CurSprite = CurFrameAnimations->Sprite->GetSpriteData(CurFrameAnimations->CurIndex);
}

void ContentsRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void ContentsRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

void ContentsRenderer::SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(ContentsRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<ContentsFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction[_Frame] = _Function;
}

void ContentsRenderer::SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(const SpriteData& CurSprite, int _SpriteIndex)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<ContentsFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameChangeFunction = _Function;
}

void ContentsRenderer::SetStartEvent(std::string_view _AnimationName, std::function<void(ContentsRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<ContentsFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction[Animation->Index[0]] = _Function;
}

void ContentsRenderer::SetEndEvent(std::string_view _AnimationName, std::function<void(ContentsRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<ContentsFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<ContentsFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->EndEvent = _Function;
}

void ContentsRenderer::AnimationPauseSwitch()
{
	IsPause = !IsPause;
}

void ContentsRenderer::AnimationPauseOn()
{
	IsPause = true;
}

void ContentsRenderer::AnimationPauseOff()
{
	IsPause = false;
}

void ContentsRenderer::SetPivotType(PivotType _Type)
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

void ContentsRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);
	GetShaderResHelper().SetConstantBufferLink("ColorData", ColorDataValue);
	SetSprite("NSet.png");
}


void ContentsRenderer::SetMaskTexture(std::string_view _Texture, MaskMode _Mask)
{
	RenderBaseInfoValue.IsMask = 1;
	RenderBaseInfoValue.MaskMode = static_cast<int>(_Mask);
	GetShaderResHelper().SetTexture("MaskTex", _Texture);
	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find(_Texture);
	RenderBaseInfoValue.MaskScreeneScale = Ptr->GetScale();
}

void ContentsRenderer::SetText(const std::string& _Font, const std::string& _Text, float _Scale /*= 20.0f*/, float4 Color /*= float4::RED*/, FW1_TEXT_FLAG Flag /*= FW1_LEFT*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->SetText(_Font, _Text, _Scale, Color, Flag);
}

void ContentsRenderer::SetTextColor(const float4& _Color /*= float4::RED*/, unsigned int _Index /*= 0*/)
{
	std::weak_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit.lock()->SetTextColor(_Color);
}

void ContentsRenderer::SetTextAlpha(float _AlphaValue /*= 1.0f*/, unsigned int _Index /*= 0*/)
{
	std::weak_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit.lock()->SetTextAlpha(_AlphaValue);
}

void ContentsRenderer::SetSampler(std::string_view _Name)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->ShaderResHelper.SetSampler("DiffuseTexSampler", _Name);
	IsUserSampler = false;
}