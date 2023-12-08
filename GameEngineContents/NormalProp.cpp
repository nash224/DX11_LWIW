#include "PreCompile.h"
#include "NormalProp.h"

#include "PixelSetter.h"


NormalProp::NormalProp()
{
}

NormalProp::~NormalProp()
{
}

void NormalProp::Release()
{
	RendererActor::Release();

	DebugRenderer = nullptr;
}

void NormalProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void NormalProp::Init(int _Order /*= 0*/)
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
}

void NormalProp::SetPixelCollision(std::string_view _FileName)
{
	DebugRenderer = PixelSetter::SetPixelCollision(this, _FileName);
}

void NormalProp::ChangePixeldata(std::string_view _PixelName)
{
	if (nullptr == DebugRenderer)
	{
		SetPixelCollision(_PixelName);
		return;
	}

	DebugRenderer->SetSprite(_PixelName);
}

void NormalProp::Serializer(GameEngineSerializer& _Data)
{
	{
		const TransformData& TransData = Transform.GetConstTransformDataRef();
		_Data.Write(&TransData, sizeof(TransData));
	}

	{
		const TransformData& TransData = Renderer->Transform.GetConstTransformDataRef();
		_Data.Write(&TransData, sizeof(TransData));
	}

	{
		_Data << Renderer->GetSprite()->GetName();
	}

	{
		_Data << DebugRenderer->GetCurSprite().Texture->GetName();
	}
}

void NormalProp::DeSerializer(GameEngineSerializer& _Data)
{
	TransformData TransData;

	Init();

	{
		_Data.Read(&TransData, sizeof(TransData));
		Transform.SetTransformData(TransData);
	}

	{
		_Data.Read(&TransData, sizeof(TransData));
		Renderer->Transform.SetTransformData(TransData);
	}

	{
		std::string SpriteName;
		_Data >> SpriteName;
		Renderer->SetSprite(SpriteName);
	}

	{
		std::string PixelSpriteName;
		_Data >> PixelSpriteName;

		if (false == PixelSpriteName.empty())
		{
			SetPixelCollision(PixelSpriteName);
		}
	}

	float4 Position = Transform.GetLocalPosition();
	Position.Round();
	Transform.SetLocalPosition(Position);
}