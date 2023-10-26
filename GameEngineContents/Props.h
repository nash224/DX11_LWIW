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



protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;



public:
	std::shared_ptr<GameEngineSpriteRenderer> m_Renderer = nullptr;

};

