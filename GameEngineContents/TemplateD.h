#pragma once

// Ό³Έν :
class TemplateD : public GameEngineActor
{
public:
	// constrcuter destructer
	TemplateD();
	~TemplateD();

	// delete Function
	TemplateD(const TemplateD& _Other) = delete;
	TemplateD(TemplateD&& _Other) noexcept = delete;
	TemplateD& operator=(const TemplateD& _Other) = delete;
	TemplateD& operator=(TemplateD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:


};

