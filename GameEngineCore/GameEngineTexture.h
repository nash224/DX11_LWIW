#pragma once
#include "GameEngineResources.h"

#include "..\\GameEngineCore\\ThirdParty\\DirectXTex\\inc\\DirectXTex.h"

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

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path)
	{
		GameEnginePath Path = _Path;

		return Load(Path.GetStringPath(), Path.GetFileName());
	}

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes(_Name);
		NewRes->ResLoad(_Path);
		return NewRes;
	}

	inline ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	void CreateRenderTargetView();

	inline float4 GetScale()
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height) };
	}

	inline ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

protected:

private:
	D3D11_TEXTURE2D_DESC Desc; // 텍스처를 Create할때 정보인데. 그냥 load할때도 사용할것이다.

	ID3D11Texture2D* Texture2D = nullptr;

	ID3D11RenderTargetView* RTV = nullptr; // 이 텍스처를 수정대상으로 삼거나 수정할수 있는 권한.
	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더에 세팅해줄수 있는 권한다.

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	void ResLoad(std::string_view _Path);
};

