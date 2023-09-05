#pragma once

// Ό³Έν :

class Scenery;
class BackDrop : public GameEngineActor
{
public:
	// constrcuter destructer
	BackDrop();
	~BackDrop();

	// delete Function
	BackDrop(const BackDrop& _Other) = delete;
	BackDrop(BackDrop&& _Other) noexcept = delete;
	BackDrop& operator=(const BackDrop& _Other) = delete;
	BackDrop& operator=(BackDrop&& _Other) noexcept = delete;


	template<typename LevelType>
	void SetLevelType(LevelType _LevelType)
	{
		SetLevelType(static_cast<int>(_LevelType));
		return;
	}

	void SetLevelType(int _LevelType);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void CreateBackDropPerLevel(class GameEngineLevel* _CurLevel);
	void CreateMainMenuBackDrop(class GameEngineLevel* _CurLevel);

private:
	int LevelCount;
	
	std::vector<std::shared_ptr<Scenery>> vecMainMenuScenery;


private:
	const float4 Layer10LeftTopPosition = float4{ 128.0f , 24.0f };

};

