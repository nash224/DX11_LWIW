#pragma once


struct InterativeParameter
{
public:
	bool IsInteractive = true;					// ��ȣ�ۿ� �����Ѱ�?
	std::shared_ptr<GameEngineCollision> InteractiveCol = nullptr;
	float4 ColScale = float4::ZERO;
};


// ���� :
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

