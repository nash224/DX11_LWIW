#include "PreCompile.h"
#include "MapEditorLevel.h"


#include "CameraControler.h"
#include "MouseManager.h"

#include "RendererActor.h"


MapEditorLevel::MapEditorLevel() 
{
	float4 Position = GlobalValue::GetWindowScale().Half();
	Position.Y *= -1.0f;
	GetMainCamera()->Transform.AddLocalPosition(Position);

}

MapEditorLevel::~MapEditorLevel() 
{
}


void MapEditorLevel::Start()
{
	ContentsLevel::Start();

	m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Editor);
}

void MapEditorLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	UpdateMapEditor(_Delta);
}


void MapEditorLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);


	m_MapBaseActor = CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
	m_MapBaseRenderer = m_MapBaseActor->CreateComponent<GameEngineSpriteRenderer>();
	m_MapBaseRenderer->Off();

	m_MouseManager = CreateActor<MouseManager>(EUPDATEORDER::Mouse);
}

void MapEditorLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	m_MouseManager = nullptr;

	if (nullptr != m_MapBaseActor)
	{
		m_MapBaseActor->Death();
	}

	m_MapBaseActor = nullptr;
	m_MapBaseRenderer = nullptr;
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


float MapEditorLevel::CalculateDepth(const float _PositionY) const
{
	float4 BackGroundScale = m_BaseScale;
	if (float4::ZERO == BackGroundScale)
	{
		BackGroundScale = GlobalValue::GetWindowScale();
	}

	float Depth = (BackGroundScale.Y + _PositionY);
	return Depth;
}



void MapEditorLevel::UpdateMapEditor(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		if ("" == _SelcetSprite)
		{
			return;
		}

		std::shared_ptr<RendererActor> Object = CreateActor<RendererActor>();
		float4 Position = GetMainCamera()->GetWorldMousePos2D();
		Position.Z = 0.0f;
		Object->Transform.SetLocalPosition(Position);
		Object->m_Renderer->SetSprite(_SelcetSprite);
		Object->m_Renderer->Transform.SetLocalPosition(float4( 0.0f , 0.0f, _RendererDepth));
	}


	float4 Position = float4::ZERO;
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		Position = float4::LEFT;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		Position = float4::UP;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		Position = float4::DOWN;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		Position = float4::RIGHT;
	}
}