#include "PreCompile.h"
#include "GroundRenderUnit.h"

GroundRenderUnit::GroundRenderUnit() 
{
}

GroundRenderUnit::~GroundRenderUnit() 
{
}


void GroundRenderUnit::Start()
{

}

void GroundRenderUnit::Update(float _Delta)
{
}

void GroundRenderUnit::Release()
{
	RendererActor::Release();
}

void GroundRenderUnit::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void GroundRenderUnit::LevelEnd(class GameEngineLevel* _NextLevel)
{
	RendererActor::LevelEnd(_NextLevel);
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void GroundRenderUnit::Serializer(GameEngineSerializer& _Data)
{
	{
		const TransformData& TransData = Transform.GetConstTransformDataRef();
		_Data.Write(&TransData, sizeof(TransData));
	}

	{
		const TransformData& TransData = m_Renderer->Transform.GetConstTransformDataRef();
		_Data.Write(&TransData, sizeof(TransData));
	}

	{
		_Data << m_Renderer->GetSprite()->GetName();
	}
}

void GroundRenderUnit::DeSerializer(GameEngineSerializer& _Data)
{
	TransformData TransData;

	{
		_Data.Read(&TransData, sizeof(TransData));
		Transform.SetTransformData(TransData);
	}

	{
		_Data.Read(&TransData, sizeof(TransData));
		m_Renderer->Transform.SetTransformData(TransData);
	}

	{
		std::string SpriteName;
		_Data >> SpriteName;
		m_Renderer->SetSprite(SpriteName);
	}
}
