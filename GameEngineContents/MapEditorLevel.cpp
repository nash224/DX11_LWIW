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

	LoadResouces();


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

	ReleaseResouces();
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

	float Depth = (BackGroundScale.Y + _PositionY) / BackGroundScale.Y * 100.0f + 100.0f;
	return Depth;
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




// ���� ����
bool MapEditorLevel::ClickCreateActor()
{
	if (true == GameEngineInput::IsDown(VK_MBUTTON, this))
	{
		if ("" == _SelcetSprite)
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
			Object->m_Renderer->SetSprite(_SelcetSprite);
			Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, _RendererHeight));
			SelectActor = Object.get();
		}

		if ("PROPITEMTAB" == MapEditorTab::MapEditorGui->GetCurItemTabName())
		{
			std::shared_ptr<NormalProp> Object = CreateActor<NormalProp>();
			float4 Position = GetMainCamera()->GetWorldMousePos2D();
			Position.Z = 0.0f;
			Object->Transform.SetLocalPosition(Position);
			Object->Init();
			Object->m_Renderer->SetSprite(_SelcetSprite);
			Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, _RendererHeight));

			if ("" != _SelcetPixelSprite)
			{
				Object->SetPixelCollision(_SelcetPixelSprite);
			}

			SelectActor = Object.get();
		}


		return true;
	}

	return false;
}


// ���� ����
bool MapEditorLevel::ClickForSelectActor()
{
	if (true == GameEngineInput::IsDown(VK_RBUTTON, this))
	{
		float4 CurWorldMousePos = m_MouseManager->m_MouseInfo.CurPos;

		std::vector<std::shared_ptr<RendererActor>> Group = GetObjectGroupConvert<RendererActor>(0);

		bool SelectCheck = false;
		int NearestNumber = 0;
		float NearestDistance = 10000.0f;

		for (int i = 0; i < Group.size(); i++)
		{
			float4 IMGWorldPos = Group[i]->m_Renderer->Transform.GetWorldPosition();

			std::shared_ptr<GameEngineTexture> Texture = Group[i]->m_Renderer->GetSprite()->GetSpriteData(0).Texture;
			if (nullptr == Texture)
			{
				MsgBoxAssert("�ؽ�ó�� �������� �ʽ��ϴ�.");
				return false;
			}


			// �̵�����
			float4 CheckBias = Texture->GetScale().Half();

			// üũ ��ġ
			float4 SelectPos = CurWorldMousePos - IMGWorldPos + CheckBias;

			// ���İ� 0�̸� ������ �ؽ�ó������ �ѱ��.
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
			return true;
		}
	}

	return false;
}



// ���õ� ���� ȸ��
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
			SelectActor->m_Renderer->LeftFlip();
		}
		else
		{
			SelectActor->m_Renderer->RightFlip();
		}

		return true;
	}

	return false;
}

// ���õ� ���� �̵�
bool MapEditorLevel::MoveSelectActor()
{
	bool IsInput = false;

	float4 Position = SelectActor->Transform.GetLocalPosition();

	if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		Position += m_MouseManager->m_MouseInfo.MovePos;
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
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::DarkGrass);
	}

	if (ERENDERDEPTH::DeepDarkGrass == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::DeepDarkGrass);
	}

	if (ERENDERDEPTH::Grass == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = GlobalUtils::CalculateFixDepth(ERENDERDEPTH::Grass);
	}

	if (ERENDERDEPTH::Object == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = CalculateDepth(Position.Y);
	}

	if (ERENDERDEPTH::Hill_Object == static_cast<ERENDERDEPTH>(_SelectDepth))
	{
		Position.Z = GlobalUtils::CalculateObjectDepth(m_BaseScale.Y, Position.Y, true);
	}

	SelectActor->Transform.SetLocalPosition(Position);
	return true;
}