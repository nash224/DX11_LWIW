#pragma once

// Ό³Έν :
class ContentsLevel : public GameEngineLevel
{
protected:
	static std::unique_ptr<class BGMManager> MainPlaySound;
	std::shared_ptr<class CameraControler> LevelCamera = nullptr;

public:
	// constrcuter destructer
	ContentsLevel();
	~ContentsLevel();

	// delete Function
	ContentsLevel(const ContentsLevel& _Other) = delete;
	ContentsLevel(ContentsLevel&& _Other) noexcept = delete;
	ContentsLevel& operator=(const ContentsLevel& _Other) = delete;
	ContentsLevel& operator=(ContentsLevel&& _Other) noexcept = delete;

	std::shared_ptr<class CameraControler> GetLevelCameraPtr() const;
	static class BGMManager* GetBGMPlayerPtr();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


};

