#pragma once

// Ό³Έν :
class Tunnel : public GameEngineActor
{
public:
	// constrcuter destructer
	Tunnel();
	~Tunnel();

	// delete Function
	Tunnel(const Tunnel& _Other) = delete;
	Tunnel(Tunnel&& _Other) noexcept = delete;
	Tunnel& operator=(const Tunnel& _Other) = delete;
	Tunnel& operator=(Tunnel&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void UpdateTunnel(float _Delta);

private:
	std::shared_ptr<GameEngineSpriteRenderer> m_Renderer = nullptr;


	float TunnelSpeed = 2800.0f;
};

