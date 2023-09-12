#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSpriteRenderer.h"

class Tile
{
public:
	SpriteData Data;
	int Index = -1;
};

class CreateTileParameter
{
public:
	size_t TileCountX = 10;
	size_t TileCountY = 10;
	float4 TileScale = { 50, 50 };
	std::string_view SpriteName = "";
};


class SetTileParameter
{
public:
	int X;
	int Y;
	int _Index = 0;
	std::string_view SpriteName = "";
};


// Ό³Έν :
class GameEngineTileMap : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineTileMap();
	~GameEngineTileMap();

	// delete Function
	GameEngineTileMap(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap(GameEngineTileMap&& _Other) noexcept = delete;
	GameEngineTileMap& operator=(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap& operator=(GameEngineTileMap&& _Other) noexcept = delete;

	//                       100           100            50 50 
	void CreateTileMap(const CreateTileParameter& _Parameter);
	// void SetTile(size_t _TileCountX, size_t _TileCountY, float4 TileScale);

	void SetTile(const SetTileParameter& _Parameter);

protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	std::shared_ptr<GameEngineSprite> DefaultSprite;

	std::vector<std::vector<Tile>> Tiles;
};

