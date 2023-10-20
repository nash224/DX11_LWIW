#pragma once

// Ό³Έν :
class Props : public GameEngineActor
{
public:
	// constrcuter destructer
	Props();
	~Props();

	// delete Function
	Props(const Props& _Other) = delete;
	Props(Props&& _Other) noexcept = delete;
	Props& operator=(const Props& _Other) = delete;
	Props& operator=(Props&& _Other) noexcept = delete;


	void SetPixelCollision(std::string_view _FileName);
	bool GetPixelCheck();
	GameEngineColor GetColor(const float4& _Position, GameEngineColor _DefaultColor = GameEngineColor::WHITE);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	void UpdateDebug();

public:
	std::shared_ptr<GameEngineSpriteRenderer> m_Renderer = nullptr;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> m_DebugRenderer = nullptr;

	bool IsRendererOn = true;
	bool PixelRendererCheck = false;
	std::string m_PixelFileName = "";

};

