#pragma once


struct InterativeParameter
{
public:
	bool IsInteractive = true;					// 상호작용 가능한가?
	std::shared_ptr<GameEngineCollision> InteractiveCol = nullptr;
	float4 ColScale = float4::ZERO;
};


// 설명 :
class InteractiveActor : public GameEngineActor
{
public:
	// constrcuter destructer
	InteractiveActor();
	~InteractiveActor();

	// delete Function
	InteractiveActor(const InteractiveActor& _Other) = delete;
	InteractiveActor(InteractiveActor&& _Other) noexcept = delete;
	InteractiveActor& operator=(const InteractiveActor& _Other) = delete;
	InteractiveActor& operator=(InteractiveActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;


protected:
	InterativeParameter m_InteractiveParameter = {};


protected:


private:


};

