#pragma once

class MouseInfo
{
public:
	float4 PrevPos = float4::ZERO;
	float4 CurPos = float4::ZERO;
	float4 MovePos = float4::ZERO;
};


// Ό³Έν :
class MouseManager : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseManager();
	~MouseManager();

	// delete Function
	MouseManager(const MouseManager& _Other) = delete;
	MouseManager(MouseManager&& _Other) noexcept = delete;
	MouseManager& operator=(const MouseManager& _Other) = delete;
	MouseManager& operator=(MouseManager&& _Other) noexcept = delete;


	float4 MousePosition = float4::ZERO;

	MouseInfo m_MouseInfo;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void RenewMousePos();
	

};

