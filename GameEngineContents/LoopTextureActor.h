#pragma once


// Ό³Έν :
class LoopTextureActor : public GameEngineActor
{
public:
	// constrcuter destructer
	LoopTextureActor();
	~LoopTextureActor();

	// delete Function
	LoopTextureActor(const LoopTextureActor& _Other) = delete;
	LoopTextureActor(LoopTextureActor&& _Other) noexcept = delete;
	LoopTextureActor& operator=(const LoopTextureActor& _Other) = delete;
	LoopTextureActor& operator=(LoopTextureActor&& _Other) noexcept = delete;

	void Init();
	void SetSpeed(float _Speed);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

protected:
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	float Speed = 0.0f;

};

