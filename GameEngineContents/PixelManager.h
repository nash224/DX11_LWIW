#pragma once

// Ό³Έν :
class PixelManager : public GameEngineActor
{
public:
	// constrcuter destructer
	PixelManager();
	~PixelManager();

	// delete Function
	PixelManager(const PixelManager& _Other) = delete;
	PixelManager(PixelManager&& _Other) noexcept = delete;
	PixelManager& operator=(const PixelManager& _Other) = delete;
	PixelManager& operator=(PixelManager&& _Other) noexcept = delete;

	void CreatePixelRenderTarget();
	void CopyRenderData();

	GameEngineColor Test(unsigned int  _X, unsigned int  _Y, GameEngineColor _DefaultColor);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = GameEngineColor::WHITE);

protected:
	void Update(float _Delta) override;

private:
	bool isFirstFrame = true;
	bool isCaptureTexture = false;
	std::shared_ptr<GameEngineRenderTarget> PixelRenderTarget;

};