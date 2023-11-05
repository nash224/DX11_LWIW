#include "PreCompile.h"
#include "NormalProp.h"

#include "ContentsLevel.h"


NormalProp::NormalProp()
{
}

NormalProp::~NormalProp()
{
}

void NormalProp::Update(float _Delta)
{
	UpdateDebug();
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


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void NormalProp::UpdateDebug()
{
	if (true == IsRendererOn && true == ContentsLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->Off();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->On();
		}

		IsRendererOn = false;
	}

	if (false == IsRendererOn && false == ContentsLevel::PixelDebugMode)
	{
		if (nullptr != m_Renderer)
		{
			m_Renderer->On();
		}

		if (nullptr != m_DebugRenderer)
		{
			m_DebugRenderer->Off();
		}

		IsRendererOn = true;
	}
}



bool NormalProp::GetPixelCheck()
{
	return PixelRendererCheck;
}

void NormalProp::SetPixelCollision(std::string_view _FileName)
{
	m_DebugRenderer = CreateComponent<GameEngineSpriteRenderer>();
	m_DebugRenderer->Off();
	m_DebugRenderer->SetSprite(_FileName);
	PixelCol.SetPixelFileName(_FileName);

	PixelRendererCheck = true;
}


void NormalProp::ChangePixeldata(std::string_view _PixelName)
{
	if (nullptr == m_DebugRenderer)
	{
		SetPixelCollision(_PixelName);
		return;
	}

	m_DebugRenderer->SetSprite(_PixelName);

	PixelCol.SetPixelFileName(_PixelName);
}

GameEngineColor NormalProp::GetColor(const float4& _Position, GameEngineColor _DefaultColor/* = GameEngineColor::WHITE*/)
{
	return PixelCol.GetColor(_Position, Transform.GetLocalPosition(), _DefaultColor);
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
		_Data << PixelCol.GetPixelFileName();
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

		if ("" != PixelSpriteName)
		{
			SetPixelCollision(PixelSpriteName);
		}
	}

	float4 Position = Transform.GetLocalPosition();
	Position.Round();
	Transform.SetLocalPosition(Position);
}