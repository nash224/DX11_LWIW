#pragma once

// Ό³Έν :
class RendererActor : public GameEngineActor, public GameEngineSerializerObject
{
public:
	// constrcuter destructer
	RendererActor();
	~RendererActor();

	// delete Function
	RendererActor(const RendererActor& _Other) = delete;
	RendererActor(RendererActor&& _Other) noexcept = delete;
	RendererActor& operator=(const RendererActor& _Other) = delete;
	RendererActor& operator=(RendererActor&& _Other) noexcept = delete;


	std::shared_ptr<GameEngineSpriteRenderer> m_Renderer = nullptr;


	void Serializer(GameEngineSerializer& _Data) override;
	void DeSerializer(GameEngineSerializer& _Data) override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

};

