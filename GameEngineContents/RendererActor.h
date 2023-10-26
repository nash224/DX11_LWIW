#pragma once

// Ό³Έν :
class RendererActor : public GameEngineActor
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


	template<typename OrderType>
	void Init(OrderType _Order)
	{
		Init(static_cast<int>(_Order));
	}

	void Init(int _Order = 0);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

public:
	std::shared_ptr<GameEngineSpriteRenderer> m_Renderer = nullptr;

	
};

