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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};