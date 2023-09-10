#include "PreCompile.h"
#include "Prop.h"

Prop::Prop()
	:
	m_Renderer(nullptr),
	m_Position(float4::ZERO),
	m_TextureScale(float4::ZERO)
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

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_SpriteName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_TextureScale = Texture->GetScale();
}

void Prop::SetLocalPosition(const float4& _Position, PivotType _Direction/* = EDIRECTION::CENTER*/)
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

void Prop::SetAutoSpriteSize(float _Ratio, bool _Value /*= true*/)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����� �� �����ϴ�.");
	}

	_Value ? m_Renderer->AutoSpriteSizeOn() : m_Renderer->AutoSpriteSizeOff();
	m_Renderer->SetAutoScaleRatio(_Ratio);
}


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


std::shared_ptr<class GameEngineSpriteRenderer>& Prop::GetSpriteRenderer()
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʾҽ��ϴ�.");
	}

	return m_Renderer;
}



void Prop::ActorRelease()
{
	m_Renderer = nullptr;

	Death();
}