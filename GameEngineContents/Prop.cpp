#include "PreCompile.h"
#include "Prop.h"

#include "BackDrop_PlayLevel.h"

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
	m_Renderer = nullptr;
	m_DebugRenderer = nullptr;
}

void Prop::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Prop::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void Prop::CreateRenderer(int _Order /*= 0*/)
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

void Prop::SetRendererPivotType(PivotType _Direction/* = EDIRECTION::CENTER*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->SetPivotType(_Direction);
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

// �÷��� �������� ZSort
void Prop::SetPositionAndDepth(const float4& _Position)
{
	if (nullptr == BackDrop_PlayLevel::MainBackDrop)
	{
		MsgBoxAssert("��� �Ŵ����� �������� �ʽ��ϴ�.");
		return;
	}

	float Depth = BackDrop_PlayLevel::MainBackDrop->ZSort(_Position.Y);
	Transform.SetLocalPosition({ _Position.X, _Position.Y, Depth });
}


#pragma region �ִϸ��̼� ����

void Prop::CreateAndSetAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter);
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

#pragma endregion

#pragma region �ȼ��浹

// �ȼ� �浹 ���� ����ϴ�.
void Prop::CreatePixelCollisionRenderer()
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>();
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


	float4 CheckPos = _Position - MoveCheckPos;
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


