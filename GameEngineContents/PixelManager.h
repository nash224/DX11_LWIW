#pragma once

// Ό³Έν : 
class PixelManager : public GameEngineActor
{
public:
	static bool PixelDebugMode;

public:
	// constrcuter destructer
	PixelManager();
	~PixelManager();

	// delete Function
	PixelManager(const PixelManager& _Other) = delete;
	PixelManager(PixelManager&& _Other) noexcept = delete;
	PixelManager& operator=(const PixelManager& _Other) = delete;
	PixelManager& operator=(PixelManager&& _Other) noexcept = delete;

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = GameEngineColor::WHITE);

protected:
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;

	void ChangeDebugMode();

	void SetCameraBeforeCaptureTexture();
	void CreatePixelTexture();

private:
	bool isSetCamera = true;
	bool isCaptureTexture = false;
	bool PixelDebugValue = false;

	float ZoomRatio = 0.0f;

	std::shared_ptr<GameEngineTexture> PixelTexture;

};