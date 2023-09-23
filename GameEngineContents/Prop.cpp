#include "PreCompile.h"
#include "Prop.h"

Prop::Prop()
{
}

Prop::~Prop() 
{
}


void Prop::Start()
{

}

void Prop::Update(float _Delta)
{

}

void Prop::Release()
{

}

void Prop::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Prop::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Prop::CreateRenderer(int _Order)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�߸� ������� �������Դϴ�.");
		return;
	}
}

void Prop::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ��������Ʈ�� ������ �� �����ϴ�.");
		return;
	}

	m_Renderer->SetSprite(_SpriteName);
}

void Prop::SetPosition(const float4& _Position, PivotType _Direction/* = EDIRECTION::CENTER*/)
{
	Transform.SetLocalPosition(_Position);

	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->SetPivotType(_Direction);

	//float4 HScale = m_TextureScale.Half();
	//Transform.SetLocalPosition(HScale);
}

void Prop::SetRendererImageScale(const float4& _Scale)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->SetImageScale(_Scale);
}


void Prop::SetSpriteRenderer(std::string_view _FileName, const float4& _Position /*= float4::ZERO*/, PivotType _Type /*= PivotType::Center*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ��������Ʈ�� ������ �� �����ϴ�.");
		return;
	}

	m_Renderer->SetSprite(_FileName);
	Transform.SetLocalPosition(_Position);
	m_Renderer->SetPivotType(_Type);
}


void Prop::SetSpriteRenderer(const PropParameter& _Parameter)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ��������Ʈ�� ������ �� �����ϴ�.");
		return;
	}

	m_Renderer->SetSprite(_Parameter.FileName);
	Transform.SetLocalPosition(_Parameter.TransformLocalPosition);
	m_Renderer->SetPivotType(_Parameter.ImagePivotType);
}



#pragma region �ִϸ��̼� ����

void Prop::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	int _Start /*= -1*/,
	int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

 	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
}


void Prop::ChangeAnimation(std::string_view _AnimationName)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
}

// �ڵ����� AutoSize�� ��û�մϴ�.
void Prop::SetAutoSpriteSize(float _Ratio, bool _Value /*= true*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����� �� �����ϴ�.");
	}

	_Value ? m_Renderer->AutoSpriteSizeOn() : m_Renderer->AutoSpriteSizeOff();
	m_Renderer->SetAutoScaleRatio(_Ratio);
}

// �ִϸ��̼��� ����ϴ�.
void Prop::CreateAutomatedAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	int _Start /*= -1*/,
	int _End /*= -1*/,
	bool _Loop /*= true*/,
	float _Raito /*= 1.0f*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����� �� �����ϴ�.");
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
	m_Renderer->ChangeAnimation(_AnimationName);
	m_Renderer->AutoSpriteSizeOn();
	m_Renderer->SetAutoScaleRatio(_Raito);
}

#pragma endregion

#pragma region �ȼ��浹

// �ȼ� �浹 ���� ����ϴ�.
void Prop::CreatePixelCollisionRenderer()
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Back_);
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_DebugRenderer->Off();

	PixelRendererCheck = true;
}

void Prop::SetPixelSprite(std::string_view _FileName)
{
	if (nullptr == m_DebugRenderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ��������Ʈ�� �������� �� �����ϴ�.");
		return;
	}

	m_DebugRenderer->SetSprite(_FileName);

	m_PixelFileName = _FileName;

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_FileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_PixelTextureScale = Texture->GetScale();
}


// ������* ��ġ�� �ȼ� �����͸� ��ȯ���ݴϴ�.
// * : GameEngineTexture::GetColor�� �ؽ�ó���� ���� ���ϴ� ��ġ�� �ȼ� �����͸� �޶�� �䱸�մϴ�.
//		�̷��� Ư�� ������ �ؽ�ó�� ����ϴ� ��ü�� ��ġ�� �̵��ص� GetColor���� �ִ� ������ ��ġ�� �׻� �����ϴ�.
//		���� ��ü�� �̵��� �Ÿ���ŭ ���� �ʿ䰡 �ֽ��ϴ�.
GameEngineColor Prop::GetColor(const float4& _Position, GameEngineColor _DefaultColor /*= { 255, 255, 255, 255 }*/)
{
	GameEngineColor ReturnValue;

	if ("" == m_PixelFileName)
	{
		MsgBoxAssert("�����ص� ������ �����ϴ�.");
		return ReturnValue;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(m_PixelFileName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return ReturnValue;
	}

	// �ؽ�ó�� �»�� ������ NDC��ǥ�� ������ �Ÿ��� ���ؾ��մϴ�.
	// �׸��� ���� �Ÿ��� ������ ���� ��ġ�� ���ݴϴ�.
	float4 HalfTexturePos = m_PixelTextureScale.Half();
	HalfTexturePos.X *= -1.0f;

	float4 MoveCheckPos = Transform.GetWorldPosition() + HalfTexturePos;


	float4 CheckPos =  _Position - MoveCheckPos;
	CheckPos.Y *= -1.0f;

	return Texture->GetColor(CheckPos, _DefaultColor);
}

#pragma endregion

void Prop::EnableDebugMode(bool _Value)
{
	if (_Value)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->Off();
		}
		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->On();
		}
	}
	else
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->On();
		}
		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->Off();
		}
	}
}



void Prop::ActorRelease()
{
	m_Renderer = nullptr;
	m_DebugRenderer = nullptr;

	Death();
}