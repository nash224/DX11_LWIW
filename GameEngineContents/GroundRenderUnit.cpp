#include "PreCompile.h"
#include "GroundRenderUnit.h"

GroundRenderUnit::GroundRenderUnit() 
{
}

GroundRenderUnit::~GroundRenderUnit() 
{
}


void GroundRenderUnit::Release()
{
	RendererActor::Release();
}

void GroundRenderUnit::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}



void GroundRenderUnit::Serializer(GameEngineSerializer& _Data)
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
}

void GroundRenderUnit::DeSerializer(GameEngineSerializer& _Data)
{
	Init();

	TransformData TransData;

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

	float4 Position = Transform.GetLocalPosition();
	Position.Round();
	Transform.SetLocalPosition(Position);
}
