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

	m_DebugRenderer = nullptr;
}

void NormalProp::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}


void NormalProp::Init(int _Order /*= 0*/)
{
	m_Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
}

void NormalProp::SetPixelCollision(std::string_view _FileName)
{
	m_DebugRenderer = PixelSetter::SetPixelCollision(this, _FileName);
}

void NormalProp::ChangePixeldata(std::string_view _PixelName)
{
	if (nullptr == m_DebugRenderer)
	{
		SetPixelCollision(_PixelName);
		return;
	}

	m_DebugRenderer->SetSprite(_PixelName);
}

void NormalProp::Serializer(GameEngineSerializer& _Data)
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

	{
		_Data << m_DebugRenderer->GetCurSprite().Texture->GetName();
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
		m_Renderer->Transform.SetTransformData(TransData);
	}

	{
		std::string SpriteName;
		_Data >> SpriteName;
		m_Renderer->SetSprite(SpriteName);
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