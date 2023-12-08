#include "PreCompile.h"
#include "Scenery.h"



#include "GlobalValue.h"

#include "CameraControler.h"


Scenery::Scenery() 
	:SpriteRenderer(nullptr)
	, Direction(float4::ZERO)
	, TextureSize(float4::ZERO)
	, MoveRatio(0.0f)
{
}

Scenery::~Scenery() 
{
}


void Scenery::Start()
{
	SpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
}

void Scenery::Update(float _Delta)
{
	MoveSceneryLocation(_Delta);
}

void Scenery::Release()
{
	SpriteRenderer = nullptr;
}

void Scenery::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

#pragma region Setting

void Scenery::SetSprite(std::string_view _SpriteName)
{
	if (nullptr == SpriteRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았는데 사용하려고 했습니다.");
		return;
	}

	SpriteRenderer->SetSprite(_SpriteName);
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_SpriteName);
	if (nullptr == Texture)
	{
		MsgBoxAssert("해당 텍스처는 존재하지 않습니다.");
		return;
	}

	TextureSize = Texture->GetScale();
}

void Scenery::SetRenderOrder(int _Order)
{
	if (nullptr == SpriteRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 않았는데 사용하려고 했습니다.");
		return;
	}

	SpriteRenderer->SetRenderOrder(_Order);
}

void Scenery::SetWorldPosition(const float4& _Position)
{
	Transform.SetLocalPosition(_Position);
}

void Scenery::SetMoveDirection(const float4& _Direction)
{
	Direction = _Direction;
}

void Scenery::SetMoveRatio(float _Ratio)
{
	MoveRatio = _Ratio;
}

#pragma endregion 



void Scenery::MoveSceneryLocation(float _Delta)
{
	if (0.0f == MoveRatio)
	{
		return;
	}

	const std::shared_ptr<CameraControler>& LevelCameraPtr = PlayLevel::GetCurLevel()->GetLevelCameraPtr();
	
	if (true == LevelCameraPtr->IsCameraMove())
	{
		float4 CameraMoveDistance = LevelCameraPtr->GetCameraMoveDistance();
		float4 CalMovePos = CameraMoveDistance * Direction * MoveRatio;
		CalMovePos.X *= -1.0f;
		Transform.AddLocalPosition(CalMovePos);
	}
}