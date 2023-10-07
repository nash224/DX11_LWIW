#pragma once

// Ό³Έν :
class ChubHole : public GameEngineActor
{
public:
	// constrcuter destructer
	ChubHole();
	~ChubHole();

	// delete Function
	ChubHole(const ChubHole& _Other) = delete;
	ChubHole(ChubHole&& _Other) noexcept = delete;
	ChubHole& operator=(const ChubHole& _Other) = delete;
	ChubHole& operator=(ChubHole&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_HoleRenderer = nullptr;

};

