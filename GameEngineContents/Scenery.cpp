#include "PreCompile.h"
#include "Scenery.h"



#include "GlobalValue.h"


Scenery::Scenery() 
	:m_SpriteRenderer(nullptr)
	, m_Direction(float4::ZERO)
	, m_TextureSize(float4::ZERO)
	, m_MoveRatio(0.0f)
{
}

Scenery::~Scenery() 
{
}


void Scenery::Start()
{
	m_SpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
	if (nullptr == m_SpriteRenderer)
	{
		MsgBoxAssert("컴포넌트 생성에 실패했습니다.");
		return;
	}

	m_SpriteRenderer->On();
}

void Scenery::Update(float _Delta)
{
	MoveSceneryLocation(_Delta);
}

void Scenery::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Scenery::LevelEnd(class GameEngineLevel* _NextLevel)
{

}



void Scenery::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == m_SpriteRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았는데 사용하려고 했습니다.");
		return;
	}

	m_SpriteRenderer->SetSprite(_SpriteName);
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_SpriteName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("해당 텍스처는 존재하지 않습니다.");
		return;
	}

	m_TextureSize = Texture->GetScale();
}

void Scenery::SetRenderOrder(int _Order)
{
	if (nullptr == m_SpriteRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았는데 사용하려고 했습니다.");
		return;
	}

	m_SpriteRenderer->SetRenderOrder(_Order);
}

void Scenery::SetWorldPosition(const float4& _Position)
{
	Transform.SetLocalPosition(_Position);
	// 이게 맞나?
}

void Scenery::SetWorldPosition(const float4& _Position, ERENDER_PIVOT_LOCATION _Location)
{
	float4 RenderLocalPosition = float4::ZERO;
	float4 TextureSize = m_TextureSize;

	switch (_Location)
	{
	case ERENDER_PIVOT_LOCATION::LeftTop:
		TextureSize = TextureSize.Half();
		TextureSize.Y *= -1.0f;
		RenderLocalPosition = TextureSize + _Position;
		break;
	case ERENDER_PIVOT_LOCATION::Center:
		RenderLocalPosition = _Position;
		break;
	default:
		break;
	}

	m_SpriteRenderer->Transform.SetLocalPosition(RenderLocalPosition);
}

void Scenery::SetMoveDirection(const float4& _Direction)
{
	m_Direction = _Direction;
}

void Scenery::SetMoveRatio(float _Ratio)
{
	m_MoveRatio = _Ratio;
}



void Scenery::MoveSceneryLocation(float _Delta)
{
	if (0.0f == m_MoveRatio)
	{
		return;
	}

	
}