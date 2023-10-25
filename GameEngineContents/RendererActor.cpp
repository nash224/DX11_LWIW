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

void RendererActor::DeSerializer(GameEngineSerializer& _Data)
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
