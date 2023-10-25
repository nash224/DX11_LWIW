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
	ClickCreateActor();

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
				 return;
			 }


			 // �̵�����
			 float4 CheckBias = Texture->GetScale().Half();

			 // üũ ��ġ
			 float4 SelectPos = CurWorldMousePos - IMGWorldPos + CheckBias;
			 
			 // ���İ� 0�̸� ������ �ؽ�ó������ �ѱ��.
			 GameEngineColor Color = Texture->GetColor(SelectPos, { 0, 0, 0, 0});
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
		 }
		 else
		 {
			 SelectActor = nullptr;
		 }
	}

	if (nullptr == SelectActor)
	{
		return;
	}


	float4 Position = float4::ZERO;
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		Position = float4::LEFT;
		SelectActor->Transform.AddLocalPosition(Position);
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		Position = float4::UP;
		SelectActor->Transform.AddLocalPosition(Position);
	}

	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		Position = float4::DOWN;
		SelectActor->Transform.AddLocalPosition(Position);
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		Position = float4::RIGHT;
		SelectActor->Transform.AddLocalPosition(Position);
	}


}

void MapEditorLevel::ClickCreateActor()
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
		Object->m_Renderer->Transform.SetLocalPosition(float4(0.0f, 0.0f, _RendererDepth));
	}
}