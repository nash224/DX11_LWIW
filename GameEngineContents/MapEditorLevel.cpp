#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "ContentsGUI.h"
#include "CameraControler.h"
#include "MouseManager.h"

#include "GroundRenderUnit.h"
#include "NormalProp.h"


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

	LevelCamera->SetCameraMode(ECAMERAMODE::Editor);


}

void MapEditorLevel::Update(float _Delta)
{
	ContentsLevel::Update(_Delta);

	UpdateMapEditor(_Delta);
}


void MapEditorLevel::LevelStart(class GameEngineLevel* _NextLevel)
{
	ContentsLevel::LevelStart(_NextLevel);

	LoadResouces();


	MapBaseActor = CreateActor<GameEngineActor>(EUPDATEORDER::Objects);
	MapBaseRenderer = MapBaseActor->CreateComponent<GameEngineSpriteRenderer>();
	MapBaseRenderer->Off();

	MouseManagerPtr = CreateActor<MouseManager>(EUPDATEORDER::Mouse);
}

void MapEditorLevel::LevelEnd(class GameEngineLevel* _NextLevel)
{
	MouseManagerPtr = nullptr;

	if (nullptr != MapBaseActor)
	{
		MapBaseActor->Death();
	}

	MapBaseActor = nullptr;
	MapBaseRenderer = nullptr;

	ReleaseResouces();
}


void MapEditorLevel::UpdateMapEditor(float _Delta)
{
	if (nullptr == SelectActor)
	{
		if (true == ClickCreateActor())
		{
			return;
		}

		if (true == ClickForSelectActor())
		{
			return;
		}
	}


	if (nullptr != SelectActor)
	{
		if (true == RotateSelectActor())
		{
			return;
		}

		if (true == MoveSelectActor())
		{
			return;
		}

		if (true == EraseSelectActor())
		{
			return;
		}

		if (true == GameEngineInput::IsDown('F', this))
		{
			PlaceThis();
			SelectActor = nullptr;
			return;
		}
	}
}




// 액터 생성
bool MapEditorLevel::ClickCreateActor()
{
	if (true == GameEngineInput::IsDown(VK_MBUTTON, this))
	{
		if (true == _SelcetSprite.empty())
		{
			return false;
		}

		if ("BASERENDERERITEMTAB" == MapEditorTab::MapEditorGui->GetCurItemTabName())
		{
			std::shared_ptr<GroundRenderUnit> Object = CreateActor<GroundRenderUnit>();
			float4 Position = GetMainCamera()->GetWorldMousePos2D();
			Position.Z = 0.0f;
			Object->Transform.SetLocalPosition(Position);
			Object->Init();
			Object->Renderer->SetSprite(_SelcetSprite);
			Object->Renderer->Transform.SetLocalPosition(float4(0.0f, _RendererHeight));
			SelectActor = Object.get();
		}

		if ("PROPITEMTAB" == MapEditorTab::MapEditorGui->GetCurItemTabName())
		{
			std::shared_ptr<NormalProp> Object = CreateActor<NormalProp>();
			float4 Position = GetMainCamera()->GetWorldMousePos2D();
			Position.Z = 0.0f;
			Object->Transform.SetLocalPosition(Position);
			Object->Init();
			Object->Renderer->SetSprite(_SelcetSprite);
			Object->Renderer->Transform.SetLocalPosition(float4(0.0f, _RendererHeight));

			if (false == _SelcetPixelSprite.empty())
			{
				Object->SetPixelCollision(_SelcetPixelSprite);
			}

			SelectActor = Object.get();
		}


		return true;
	}

	return false;
}


// 액터 선택
bool MapEditorLevel::ClickForSelectActor()
{
	if (true == GameEngineInput::IsDown(VK_RBUTTON, this))
	{

		float4 CurWorldMousePos = MouseManagerPtr->m_MouseInfo.CurPos;

		std::vector<std::shared_ptr<RendererActor>> Group = GetObjectGroupConvert<RendererActor>(0);

		bool SelectCheck = false;
		int NearestNumber = 0;
		float NearestDistance = 10000.0f;

		for (int i = 0; i < Group.size(); i++)
		{
			float4 IMGWorldPos = Group[i]->Renderer->Transform.GetWorldPosition();

			std::shared_ptr<GameEngineTexture> Texture = Group[i]->Renderer->GetSprite()->GetSpriteData(0).Texture;
			if (nullptr == Texture)
			{
				MsgBoxAssert("텍스처가 존재하지 않습니다.");
				return false;
			}


			// 이동보정
			float4 CheckBias = Texture->GetScale().Half();

			// 체크 위치
			float4 SelectPos = CurWorldMousePos - IMGWorldPos + CheckBias;

			// 알파가 0이면 투명한 텍스처임으로 넘긴다.
			GameEngineColor Color = Texture->GetColor(SelectPos, { 0, 0, 0, 0 });
			if (Color.A == 0)
			{
				continue;
			}

			if (NearestDistance > IMGWorldPos.Z)
			{
				SelectCheck = true;
				NearestNumber = i;
				NearestDistance = IMGWorldPos.Z;
			}
		}

		if (true == SelectCheck)
		{
			SelectActor = Group[NearestNumber].get();

			GroundRenderUnit* Check1 = dynamic_cast<GroundRenderUnit*>(SelectActor);
			NormalProp* Check2 = dynamic_cast<NormalProp*>(SelectActor);
			if (nullptr == Check1 && nullptr == Check2)
			{
				SelectActor = nullptr;
				return false;
			}

			return true;
		}
	}

	return false;
}



// 선택된 액터 회전
bool MapEditorLevel::RotateSelectActor()
{
	if (true == GameEngineInput::IsDown('Q', this))
	{
		SelectActor->Transform.AddLocalRotation(float4( 0.0f, 0.0f, OneQuater ));
		return true;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		SelectActor->Transform.AddLocalRotation(float4(0.0f, 0.0f, -OneQuater ));
		return true;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		IsFlip = !IsFlip;

		if (true == IsFlip)
		{
			SelectActor->Renderer->LeftFlip();
		}
		else
		{
			SelectActor->Renderer->RightFlip();
		}

		return true;
	}

	return false;
}

// 선택된 액터 이동
bool MapEditorLevel::MoveSelectActor()
{
	bool IsInput = false;

	float4 Position = SelectActor->Transform.GetLocalPosition();

	if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		Position += MouseManagerPtr->m_MouseInfo.MovePos;
		IsInput = true;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		Position += float4::LEFT;
		IsInput = true;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		Position += float4::UP;
		IsInput = true;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		Position += float4::DOWN;
		IsInput = true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		Position += float4::RIGHT;
		IsInput = true;
	}

	if (true == IsInput)
	{
		SelectActor->Transform.SetLocalPosition(Position);
		PlaceThis();
		return true;
	}

	return false;
}


bool MapEditorLevel::EraseSelectActor()
{
	if (true == GameEngineInput::IsDown('X', this))
	{
		SelectActor->Death();
		SelectActor = nullptr;
		return true;
	}

	return false;
}

bool MapEditorLevel::PlaceThis()
{
	float4 Position = SelectActor->Transform.GetLocalPosition();

	if (ERENDERDEPTH::DarkGrass == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::DarkGrass);
	}

	if (ERENDERDEPTH::DeepDarkGrass == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::DeepDarkGrass);
	}

	if (ERENDERDEPTH::Grass == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Grass);
	}

	if (ERENDERDEPTH::Object == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = DepthFunction::CalculateObjectDepth(m_BaseScale.Y, Position.Y);
	}

	if (ERENDERDEPTH::Hill_Object == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = DepthFunction::CalculateObjectDepth(m_BaseScale.Y, Position.Y, true);
	}

	SelectActor->Transform.SetLocalPosition(Position);
	return true;
}