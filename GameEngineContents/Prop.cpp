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

void Prop::SetLocalPosition(const float4& _Position, EDIRECTION _Direction/* = EDIRECTION::CENTER*/)
{
	Transform.SetLocalPosition(_Position);

	float4 HScale = m_TextureScale.Half();

	switch (_Direction)
	{
	case EDIRECTION::CENTER:
		break;
	case EDIRECTION::TOP:
		break;
	case EDIRECTION::LEFTTOP:
		HScale.Y *= -1.0f;
		break;
	case EDIRECTION::LEFT:
		break;
	case EDIRECTION::LEFTBOT:
		break;
	case EDIRECTION::BOT:
		break;
	case EDIRECTION::RIGHTBOT:
		break;
	case EDIRECTION::RIGHT:
		break;
	case EDIRECTION::RIGHTTOP:
		break;
	default:
		break;
	}

	Transform.SetLocalPosition(HScale);
}

void Prop::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
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

void Prop::AutoSpriteSize(bool _Value, float _Ratio)
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
	float _Raito /*= 1.0f*/,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	if (nullptr == m_Renderer)
	{
		MsgBoxAssert("�������� �������� �ʰ� ����� �� �����ϴ�.");
	}

	m_Renderer->CreateAnimation(_AnimationName, _SpriteName, _Inter, _Start, _End, _Loop);
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
	if (nullptr != m_Renderer)
	{
		m_Renderer->Death();
		m_Renderer = nullptr;
	}

	Death();
}