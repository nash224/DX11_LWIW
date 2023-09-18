#pragma once

// Ό³Έν :
class PixelMap : public GameEngineActor
{
public:
	static PixelMap* MainMap;

public:
	// constrcuter destructer
	PixelMap();
	~PixelMap();

	// delete Function
	PixelMap(const PixelMap& _Other) = delete;
	PixelMap(PixelMap&& _Other) noexcept = delete;
	PixelMap& operator=(const PixelMap& _Other) = delete;
	PixelMap& operator=(PixelMap&& _Other) noexcept = delete;


	void SetPixelSprite(std::string_view _FileName);

	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

	void EnableRenderer(bool _Value);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


public:
	void ActorRelease();

private:



	std::shared_ptr<GameEngineSpriteRenderer> m_PixelRenderer;

	std::string _PixelFileName = "";
};

