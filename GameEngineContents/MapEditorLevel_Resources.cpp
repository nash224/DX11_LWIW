#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "RendererActor.h"

void MapEditorLevel::LoadResouces()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
			GameEngineTexture::Load(pFile.GetFileName());
		}
	}

	if (nullptr == GameEngineTexture::Find("CenterMap.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
			GameEngineSprite::CreateSingle(pFile.GetFileName());
		}
	}
}

void MapEditorLevel::ReleaseResouces()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_Yard");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::Release(pFile.GetFileName());
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("CenterMap.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\FieldCenter");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSprite::Release(pFile.GetFileName());
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}



void MapEditorLevel::CenterFieldMapSetting()
{
	const std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("CenterMap.png");
	if (nullptr == Texture)
	{
		MsgBoxAssert("Not Find Map Sprite");
		return;
	}

	const float4 MapScale = Texture->GetScale();
	m_BaseScale = MapScale;


	{
		float4 MapPos = MapScale.Half();
		MapPos.Y *= -1.0f;
		MapPos.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Cliff);

		std::shared_ptr<RendererActor> CenterMap = CreateActor<RendererActor>();
		CenterMap->Transform.SetLocalPosition(MapPos);
		CenterMap->Init();
		CenterMap->Renderer->SetSprite("CenterMap.png");
	}

	{
		float4 BasePosition = MapScale.Half();
		BasePosition.Y *= -1.0f;
		BasePosition.Z = DepthFunction::CalculateFixDepth(ERENDERDEPTH::Back_Paint);

		std::shared_ptr<RendererActor> BaseGorund = CreateActor<RendererActor>();
		BaseGorund->Transform.SetLocalPosition(BasePosition);
		BaseGorund->Init();
		BaseGorund->Renderer->SetSprite("GroundBase.png");
		BaseGorund->Renderer->SetImageScale(MapScale);
	}
}