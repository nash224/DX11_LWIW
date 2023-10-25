#include "PreCompile.h"
#include "MapEditorLevel.h"


#include "CameraControler.h"

#include "RendererActor.h"


MapEditorLevel::MapEditorLevel() 
{
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
}

void MapEditorLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


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
}