#include "PreCompile.h"
#include "Scenery.h"



#include "GlobalValue.h"

#include "CameraControler.h"


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
}

void Scenery::Update(float _Delta)
{
	MoveSceneryLocation(_Delta);
}

void Scenery::Release()
{
	m_SpriteRenderer = nullptr;
}

void Scenery::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void Scenery::LevelEnd(class GameEngineLevel* _NextLevel)
{

}


#pragma region Setting

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
}

void Scenery::SetMoveDirection(const float4& _Direction)
{
	m_Direction = _Direction;
}

void Scenery::SetMoveRatio(float _Ratio)
{
	m_MoveRatio = _Ratio;
}

#pragma endregion 



void Scenery::MoveSceneryLocation(float _Delta)
{
	if (0.0f == m_MoveRatio)
	{
		return;
	}

	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (true == GlobalValue::g_CameraControler->IsCameraMove())
		{
			float4 CameraMoveDistance = GlobalValue::g_CameraControler->GetCameraMoveDistance();
			float4 CalMovePos = CameraMoveDistance * m_Direction * m_MoveRatio;
			CalMovePos.X *= -1.0f;
			Transform.AddLocalPosition(CalMovePos);
		}
	}
}


void Scenery::ActorRelease()
{
	m_SpriteRenderer = nullptr;

	Death();
}
