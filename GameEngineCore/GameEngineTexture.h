#pragma once
#include "GameEngineResources.h"

// 설명 :
class GameEngineTexture : public GameEngineResources<GameEngineTexture>
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineTexture> Create(ID3D11Texture2D* _Res)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes();
		NewRes->Texture2D = _Res;
		return NewRes;
	}

	inline ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	void CreateRenderTargetView();

protected:

private:
	ID3D11Texture2D* Texture2D = nullptr;
	ID3D11RenderTargetView* RTV = nullptr; // 이 텍스처를 수정대상으로 삼거나 수정할수 있는 권한.

};

