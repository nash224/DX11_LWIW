#pragma once

// Ό³Έν :
class GameEngineRasterizer
{
public:
	// constrcuter destructer
	GameEngineRasterizer();
	~GameEngineRasterizer();

	// delete Function
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;

protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Desc);

	void Setting();

private:
	D3D11_RASTERIZER_DESC Desc = {};
	ID3D11RasterizerState* State = nullptr;

};

