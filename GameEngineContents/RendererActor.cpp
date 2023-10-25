#include "PreCompile.h"
#include "RendererActor.h"

RendererActor::RendererActor() 
{
}

RendererActor::~RendererActor() 
{
}


void RendererActor::Start()
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>();
}

void RendererActor::Update(float _Delta)
{
}

void RendererActor::Release()
{
	m_Renderer = nullptr;
}

void RendererActor::LevelStart(class GameEngineLevel* _NextLevel)
{

}

void RendererActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void RendererActor::Serializer(GameEngineSerializer& _Data)
{
	{
		const TransformData & Data = Transform.GetConstTransformDataRef();
		_Data.Write(&Data, sizeof(Data));
	}

	{
		const TransformData& Data = m_Renderer->Transform.GetConstTransformDataRef();
		_Data.Write(&Data, sizeof(Data));
	}
}

void RendererActor::DeSerializer(GameEngineSerializer& _Data)
{
	TransformData Data;

	{
		_Data.Read(&Data, sizeof(Data));
		Transform.SetTransformData(Data);
	}

	{
		_Data.Read(&Data, sizeof(Data));
		m_Renderer->Transform.SetTransformData(Data);
	}
}
