#pragma once

// Ό³Έν :
class TemplateA : public GameEngineActor
{
public:
	// constrcuter destructer
	TemplateA();
	~TemplateA();

	// delete Function
	TemplateA(const TemplateA& _Other) = delete;
	TemplateA(TemplateA&& _Other) noexcept = delete;
	TemplateA& operator=(const TemplateA& _Other) = delete;
	TemplateA& operator=(TemplateA&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

