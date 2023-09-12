#include "PreCompile.h"
#include "GameEngineTileMap.h"

GameEngineTileMap::GameEngineTileMap()
{
}

GameEngineTileMap::~GameEngineTileMap()
{
}

void GameEngineTileMap::CreateTileMap(const CreateTileParameter& _Parameter)
{
	Tiles.resize(_Parameter.TileCountY);

	for (size_t i = 0; i < _Parameter.TileCountY; i++)
	{
		Tiles[i].resize(_Parameter.TileCountX);
	}

	DefaultSprite = GameEngineSprite::Find(_Parameter.SpriteName);
}

void GameEngineTileMap::SetTile(const SetTileParameter& _Parameter)
{
	if (Tiles.size() <= _Parameter.Y)
	{
		MsgBoxAssert("타일 인덱스를 Y 오버했습니다.");
	}

	if (Tiles[_Parameter.Y].size() <= _Parameter.X)
	{
		MsgBoxAssert("타일 인덱스를 X 오버했습니다.");
	}

	Tile& CurTile = Tiles[_Parameter.Y][_Parameter.X];

	if (_Parameter.SpriteName.empty())
	{
		CurTile.Data = DefaultSprite->GetSpriteData(_Parameter._Index);
	}
	else
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(_Parameter.SpriteName);
		CurTile.Data = FindSprite->GetSpriteData(_Parameter._Index);
	}

	CurTile.Index = _Parameter._Index;
}

void GameEngineTileMap::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();

	TransformData Data;
	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			// 이게 100 x 100번 만큼
			//if (카메라에 나오지 않는다면)
			//{
			//	continue;
			//}


			//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex);

			//if (nullptr != Buffer)
			//{
			//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
			//	Buffer->ChangeData(Data);
			//	Buffer->Setting(0);
			////}

			//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);

			//if (nullptr != Buffer)
			//{
			//	Buffer->ChangeData(CurSprite.SpritePivot);
			//	Buffer->Setting(1);
			//}


			//CurSprite.Texture->PSSetting(0);


			Draw();
		}
	}
}