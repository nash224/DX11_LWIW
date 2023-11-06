#pragma once

// Ό³Έν :
class Tunnel : public GameEngineActor
{
private:
	enum class ETUNNELSTATE
	{
		EnterTunnel,
		Wait,
		None,
	};

public:
	// constrcuter destructer
	Tunnel();
	~Tunnel();

	// delete Function
	Tunnel(const Tunnel& _Other) = delete;
	Tunnel(Tunnel&& _Other) noexcept = delete;
	Tunnel& operator=(const Tunnel& _Other) = delete;
	Tunnel& operator=(Tunnel&& _Other) noexcept = delete;

	void Init(std::string_view _NextLevelName);

protected:
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void StateSetting();

	void StartEnterTunnel(GameEngineState* _Parent);

	void UpdateEnterTunnel(float _Delta, GameEngineState* _Parent);
	void UpdateWait(float _Delta, GameEngineState* _Parent);



private:
	std::shared_ptr<GameEngineUIRenderer> m_Renderer = nullptr;
	std::string NextLevelName = "";

	GameEngineState TunnelState;

	static constexpr const float TunnelSpeed = 2800.0f;
};

